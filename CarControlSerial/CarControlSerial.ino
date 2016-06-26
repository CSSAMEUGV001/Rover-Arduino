#include "Car.h"

Car car;

void setup()
{
  car.InitCar(10, 11, 90);
  car.goNeutral();
  
  //Enable serial data transfer
  Serial.begin(9600);

  #ifdef DEBUG
  Serial.write(("Steering range: " 
                + String(car.MIN_STEER) + "-" + car.MAX_STEER
                + "\tThrottle range: "
                + car.MIN_THROTTLE + "-" + car.MAX_THROTTLE
                + "\nUse 0 to set both steering and throttle to neutral\n"
                  "Use any negative number to switch between steering and throttle mode\n\n").c_str());
  #endif
}

void loop()
{
  int steerValue;
  int throttleValue;

  if (Serial.available() > 0)
  {
    // read the incoming data and parse it as an int
    steerValue = Serial.parseInt();
    throttleValue = Serial.parseInt();

    if (steerValue < 0 || throttleValue < 0)
    {
      car.goNeutral();
      
      #ifdef DEBUG
      Serial.write("Car set to neutral\n");
      #endif
    }
    else
    {
      car.setSteering(steerValue);
      car.setThrottle(throttleValue);

      #ifdef DEBUG
      Serial.write(("Steering: " + String(steerValue)
                    + "\nThrottle: " +  String(throttleValue) + "\n").c_str());
      #endif
    }
  }
}

