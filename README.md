# Rover-Arduino

## How to control rover over serial
1. Wire the rover properly
  * Get help if you don't know how
  * *DO NOT* take this step lightly. A misplaced cable can be very dangerous
2. Open CarControlSerial.ino in Arduino IDE
3. Decide whether you want debug output or not
  * If yes, continue to the next step
  * If no, open Define.h and comment out the define
  * If you don't know, continue to the next step
4. Upload to the Uno
  * If this is giving you problems, go to Tools>Ports and select the port that shows your Uno on it
5. Turn on the car and wait for it stop beeping
  * If it does not stop beeping within a few seconds, you did something wrong. Most likely step 1
  * The car will beep every once in a while. This is normal behavior
6. Click the magnifying glass icon in the top right to open the Serial Monitor
7. Enter your commands. The format is: "\<Steering Value>\<White Space>\<Throttle Value>"
  * Enter a negative value on either side to set the car to neutral
  * Leaving off throttle value will cause the value to be read as 0 due to how Serial.ParseInt() works
