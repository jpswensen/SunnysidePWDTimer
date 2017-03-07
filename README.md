# SunnysidePWDTimer

This is an early prototype of a simple 4-lane pinewood derby timer created using the popular Internet of Things (IOT) device ESP8266, 
some cheap IR line detectors sensors, and a limit switch for the starting gate.

Parts List
================
* 1) Wemos D1 Mini - $7.49 (https://www.amazon.com/HiLetgo-NodeMcu-Development-ESP8266-Compatiable/dp/B01IXBWH9Y)
* 2) OSOYOO 10PCS IR Infrared Obstacle Avoidance Sensor Module for Arduino Smart Car Robot - $9.99 for a 10 pack (https://www.amazon.com/gp/product/B01I57HIJ0)
* 3) Limit switch for gate sensor (must have normally closed terminals) - $8.89 for a 20 pack (https://www.amazon.com/Gikfun-Micro-Switch-Arduino-EK1713/dp/B015W8S8NA)
* 4) Some 3D printed parts for mounting the sensor to the lanes and the limit switch

Details
================
The project contains both a cross-platform QT5 project for the PC side and Arduino code forht Wemos D1 Mini. They communicate through the
serial port built into the Wemos D1 Mini carrier board for the ESP8266 IOT mainboard. Here is a list of pin configurations:

 * D7 - Start gate limit switch
 * D1 - Lane A
 * D2 - Lane B
 * D5 - Lane C
 * D6 - Lane D

I plan on uploading the Solidworks and STL files for our particular track so that it would be easy for others to modify for their track.
This software is clearly not as fully functional as the Grand Prix Race Manager (TM) software, but it is free and the timer costs about $20-25
if you can get a bit of donated 3D printing from a parent or friend of the pack. I would welcome collaborators to make the software really fully
functional (e.g. support dens/groups/subgroups, printing certificates, etc.) I was actually really surprised when our pack was buying a new track
that was around $1,000 and even a cheap timer was over $219. The timer sold by the track manufacturer was really nice, but cost another $600
beyond the cost of the track.

Let me know if you have any questions and would like to collaborate.
