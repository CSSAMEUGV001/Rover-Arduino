# Rover-Arduino

## How to control rover over serial
1. Wait for 3 line message to output
2. Turn on the car
3. Enter your commands
  * 0 will set the steering and throttle to neutral
  * Any negative number will switch between steering and throttle mode
  * A number within the displayed range will change the value of the steering or throttle depening on the respective mode
  * A non-negative/zero number that is out of range will get an error output and be corrected to the nearest valid number in range
