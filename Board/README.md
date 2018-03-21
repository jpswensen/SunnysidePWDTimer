# SunnysidePWDTimer

This is an initial schematic and board design for an 8-lane pinewood
derby timer.

THIS HAS NOT BEEN TESTED YET. THE CODE AND GUI INCLUDED IN THIS
PROJECT WERE BASED ON A 4-LANE HAND SOLDERED BOARD I MADE. THIS BOARD
IS BASED ON THAT AND SHOULD WORK FOR UP TO 8 LANES, BUT THE ARDUINO
CODE AND GUI CODE HAVE NOT BEEN UPDATED TO WORK WITH THIS DESIGN YET.

Parts List
================
* 1) Wemos D1 Mini - $7.49 (https://www.amazon.com/HiLetgo-NodeMcu-Development-ESP8266-Compatiable/dp/B01IXBWH9Y)
* 2) OSOYOO 10PCS IR Infrared Obstacle Avoidance Sensor Module for Arduino Smart Car Robot - $9.99 for a 10 pack (https://www.amazon.com/gp/product/B01I57HIJ0)
* 3) Limit switch for gate sensor (must have normally closed terminals) - $8.89 for a 20 pack (https://www.amazon.com/Gikfun-Micro-Switch-Arduino-EK1713/dp/B015W8S8NA)
* 4) Some 3D printed parts for mounting the sensor to the lanes and
the limit switch
* 5) See the file SunnysideTimersDigikey.csv for the rest of the
connector, pins, etc from Digikey

In total, I think this time would cost you about $80 to make an 8-lane
timer. If multiple people went together, and it was made in bulk, that
cost could probably be half that much (circuit boards are more
expensive in lower quantity and the cabling is expensive in short lengths). I also chose nice Molex Minifit Jr
connectors which end up being kindof pricy.

Details
================
Here is a description of the files

* SunnysideTimerV1.pro - The project file for Eagle PCB
* SunnysideTimerV1.sch - The schematic file for Eagle PCB
* SunnysideTimerV1.brd - The board file for Eagle PCB

The easiest way to get these made is to go to https://oshpark.com/ and
just upload the .brd file. They do all the processing and the price
comes out at around $30 for 3 boards. Not a bad price for a 14 day turnaround.
