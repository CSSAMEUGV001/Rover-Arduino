#include <Wire.h>

#include "Car.h"

Car car;

void setup() {
  Wire.begin(0x2a);             
  Wire.onReceive(receiveEvent);
  //Serial.begin(9600);

    /* Inits the car using:
   *  Pin 10 for steering
   *  Pin 11 for throttle
   *  90 for the neutral value
   */
  car.InitCar(10, 11, 90);

  //Sets steering and throttle to neutral
  car.goNeutral();
}

void loop() {}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) 
  {
    int steering = Wire.read();
    int throttle = Wire.read();

    if(car.getSteering() != steering)
      car.setSteering(steering);
    
    if(car.getThrottle() != throttle)
      car.setThrottle(throttle);
    //Serial.println("Steering: " + String(steering) + "\tThrottle: " + throttle);      // print the character
  }
}
