import socket
import time
import serial

class PWDTimerCommMode:
    UNDEFINED   = 0
    SERIAL      = 1
    NETWORK     = 2

class PWDTimerState:
    UNDEFINED   = 0
    RESET       = 1
    SET         = 2
    IN_RACE     = 3
    FINISHED    = 4

class PWDTimerMessage:

    state = PWDTimerState.UNDEFINED

    def __init__(self,msg_bytes):
        try:
            msg_str = msg_bytes.decode('utf-8')
        except:
            print("Error parsing message")
            return
        
        idx = msg_str.find('*')
        fields = msg_str[1:idx].split(',')

        self.state = int(fields[0])
        self.start_time = int(fields[1])
        self.curr_time = int(fields[2])
        self.num_lanes = int(fields[3])
        self.end_times = []
        for I in range(self.num_lanes):
            self.end_times.append(int(fields[4+I]))
        
    def get_state(self):
        return self.state

    def get_lane_times(self):
        end_times_seconds = []
        for I in range(self.num_lanes):
            etsec = 0
            if self.end_times[I] == 0:
                etsec = (self.curr_time - self.start_time)/1E6    
            else:
                etsec = (self.end_times[I] - self.start_time)/1E6
            end_times_seconds.append(etsec)
        return end_times_seconds

    def print_lane_times(self):
        ets = self.get_lane_times()
        print(ets)

    def get_timer_state(self):
        if self.state == PWDTimerState.UNDEFINED:
            return "UNDEFINED"
        elif self.state == PWDTimerState.RESET:
            return "RESET"
        elif self.state == PWDTimerState.SET:
            return "SET"
        elif self.state == PWDTimerState.IN_RACE:
            return "IN RACE"
        elif self.state == PWDTimerState.FINISHED:
            return "FINISHED"

class PWDTimerClient:
    DEFAULT_HOST = '192.168.4.1'
    DEFAULT_TCP_PORT = 8080
    DEFAULT_SERIAL_PORT = 'COM1'

    ser_port = DEFAULT_SERIAL_PORT

    comm_mode = PWDTimerCommMode.UNDEFINED

    def __init__(self):
        self.sock = None
        self.ser = None
        
    def is_connected(self):
        return self.ser is not None  or self.sock is not None 

    def comm_mode_str(self):
        if self.comm_mode == PWDTimerCommMode.UNDEFINED:
            return "No comm mode selected"
        elif self.comm_mode == PWDTimerCommMode.SERIAL:
            return "Serial"
        elif self.comm_mode == PWDTimerCommMode.NETWORK:
            return "Network"

    def connect_serial(self, ser_port=None):
        if self.comm_mode != PWDTimerCommMode.UNDEFINED:
            print("ERROR: The communications has already been initialized")

        if ser_port == None:
            ser_port = self.DEFAULT_SERIAL_PORT

        try:
            self.ser_port = ser_port
            self.ser = serial.Serial(ser_port, 115200)
            if not self.ser.isOpen():
                print("ERROR OPENING SERIAL PORT")
                return
            self.comm_mode = PWDTimerCommMode.SERIAL
        except:
            print("Error opening serial port")

    def disconnect_serial(self):
        self.ser.close()     
        self.ser = None
        self.comm_mode = PWDTimerCommMode.UNDEFINED   

    def connect_wifi(self, host=None, tcp_port=None):
        if self.comm_mode != PWDTimerCommMode.UNDEFINED:
            print("ERROR: The communications has already been initialized")

        if host == None:
            host = self.DEFAULT_HOST

        if tcp_port == None:
            tcp_port = self.DEFAULT_TCP_PORT

        # Create the connection
        self.sock.connect((host, tcp_port))
        self.comm_mode = PWDTimerCommMode.NETWORK
        
    def disconnect_wifi(self):
        self.sock.close()
        self.sock = None
        self.comm_mode = PWDTimerCommMode.UNDEFINED

    def send_message(self, msg):
        msg_bytes = bytes(msg+'\r\n','utf-8')
        if self.comm_mode == PWDTimerCommMode.NETWORK:            
            sent = self.sock.send(msg_bytes)
            if sent == 0:
                raise RuntimeError("socket connection broken")
        elif self.comm_mode == PWDTimerCommMode.SERIAL:
            # TODO: Implement a serial send
            sent = self.ser.write(msg_bytes)
            if sent == 0:
                raise RuntimeError("couldn't send over serial")

    def recv_flush(self):
        if self.comm_mode == PWDTimerCommMode.NETWORK:
            chunk = self.sock.recv(10000)
        elif self.comm_mode == PWDTimerCommMode.SERIAL:
            # Implement a serial flush
            self.ser.reset_input_buffer()

    def recv_message(self):
        if self.comm_mode == PWDTimerCommMode.NETWORK:
            chunks = []
            bytes_recd = 0
            MSGLEN = 2048
            while bytes_recd < MSGLEN:
                chunk = self.sock.recv(1)
                if chunk == b'':
                    raise RuntimeError("socket connection broken")
                elif chunk == b'$':
                    chunks = []
                elif chunk == b'\n':
                    break
                chunks.append(chunk)
                bytes_recd = bytes_recd + len(chunk)
            retval = b''.join(chunks)        
            if retval[0:1] != b'$':
                return b''
            else:             
                return retval
        elif self.comm_mode == PWDTimerCommMode.SERIAL:
            # Implement a serial receive
            chunks = []
            bytes_recd = 0
            MSGLEN = 2048
            while bytes_recd < MSGLEN:
                chunk = self.ser.read()
                if chunk == b'':
                    raise RuntimeError("socket connection broken")
                elif chunk == b'$':
                    chunks = []
                elif chunk == b'\n':
                    break
                chunks.append(chunk)
                bytes_recd = bytes_recd + len(chunk)
            retval = b''.join(chunks)        
            if retval[0:1] != b'$':
                return b''
            else:             
                return retval

    def reset_race(self):
        self.send_message("RESET")

    def set_lane_count(self,lanes):
        if lanes < 1 or lanes > 8:
            print("ERROR: You can't have less than one lane or more than 8 lanes")
            return
        
        msg = f'LANES,{lanes}*'
        self.send_message(msg)


if __name__ == "__main__":
    client = PWDTimerClient()
    #client.connect_wifi('pwdtimer.local',8080) # this works because of the MDNS software running on the device
    client.connect_serial('/dev/cu.usbserial-0001')
    client.recv_flush()

    client.set_lane_count(4)

    while True:

        mstr = client.recv_message()
        if mstr == None or len(mstr) < 3:
            continue
        timestamp = time.time()
        msg = PWDTimerMessage(mstr)

        if msg.get_state() == PWDTimerState.RESET:
            print(f"Waiting for race to start: {timestamp}")
        elif msg.get_state() == PWDTimerState.SET:
            print(f"Gate armed and waiting for race to start: {timestamp}")
        elif msg.get_state() == PWDTimerState.IN_RACE:
            print(f'Timer time: {msg.get_lane_times()}    Timestamp: : {timestamp}')
        elif msg.get_state() == PWDTimerState.FINISHED:
            print(f'Race done, resetting in 5 seconds: {timestamp}')
            time.sleep(2)
            client.recv_flush()
            client.reset_race()
            
            

        time.sleep(0.010)
