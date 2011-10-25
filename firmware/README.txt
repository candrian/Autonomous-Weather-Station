The code was written just to test the hardware. So it is as simple as it could. 
It takes an analogue measurement and sends it to a web server over gprs. There isn't 
a good communication between the gsm and the pic because the pic checks only if 
an answer is received and not the content of the answer. The data send with GET requests which also isn't a good idea but it make it easier and understandable.

Hardware used: PIC16F877A & SIM300/900 GSM Module
More info: http://www.candrian.gr