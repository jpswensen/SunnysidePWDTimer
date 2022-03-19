import socket
import time

class PWDTimerState:
    UNDEFINED   = 0
    RESET       = 1
    SET         = 2
    IN_RACE     = 3
    FINISHED    = 4

class PWDTimerMessage:
    def __init__(self,msg_bytes) -> None:
        msg_str = msg_bytes.decode('utf-8')
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
    DEFAULT_PORT = 8080

    def __init__(self, sock=None):
        if sock is None:
            self.sock = socket.socket(
                            socket.AF_INET, socket.SOCK_STREAM)
        else:
            self.sock = sock

    def connect(self, host=None, port=None):

        if host == None:
            host = self.DEFAULT_HOST

        if port == None:
            port = self.DEFAULT_PORT

        # Create the connection
        self.sock.connect((host, port))
        #self.sock.setblocking(0)

    def send_message(self, msg):
        msg_bytes = bytes(msg+'\r\n','utf-8')
        sent = self.sock.send(msg_bytes)
        if sent == 0:
            raise RuntimeError("socket connection broken")

    def recv_flush(self):
        chunk = self.sock.recv(10000)

    def recv_message(self):
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

    def reset_race(self):
        self.send_message("RESET")


client = PWDTimerClient()
client.connect('pwdtimer.local',8080)
client.recv_flush()

while True:

    mstr = client.recv_message()
    if len(mstr) < 3:
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
