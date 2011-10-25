Autonomous live tracking weather station. It takes (analog/digital) measurements and sends them to a web server over GPRS. Adding a battery and a solar station you can make it fully autonomous. It supports up to 3 inputs Analog or Digital. The main brain is the PIC 16F877A which also drives the SIM900/300 GSM module which is placed in the back of the PCB.
The main purpose of this project is to take wind flow measurements of different locations and store them in a database remotely. By this you know if the locations are appropriate for future installation of wind generators.

The data send from GSM to Web server with GET requests which isn’t the safest and best way but its an easy way to make it work. The example code you can find at the github is a very simple example and has no security responsibility.

Here you can find the firmware, data sheets, scheme and PCB design and also the web site of data storing.

Hardware used: PIC16F877A & SIM300/900 GSM Module
More info: http://www.candrian.gr