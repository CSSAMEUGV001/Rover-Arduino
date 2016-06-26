# Rover-Arduino

## How to control rover over serial
1. Open CarControlSerial.ino in Arduino IDE
2. Decide whether you want debug output or not
  * If yes, continue to next step
  * Else, open Define.h and comment out the define
3. Upload to the Uno
2. Turn on the car
3. Enter your commands. The format is: "\<Steering Value>\<White Space>\<Throttle Value>"
  * Enter a negative value on either side to set the car to neutral
  * Leaving off throttle value will cause it to be read as 0
