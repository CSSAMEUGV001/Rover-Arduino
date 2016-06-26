#include "Car.h"

Car car;

void setup()
{
  car.InitCar(10, 11, 90);
  car.goNeutral();
  
  //Enable serial data transfer
  Serial.begin(9600);
  Serial.write(("Steering range: " 
                + String(car.MIN_STEER) + "-" + car.MAX_STEER
                + "\tThrottle range: "
                + car.MIN_THROTTLE + "-" + car.MAX_THROTTLE
                + "\nUse 0 to set both steering and throttle to neutral\n"
                  "Use any negative number to switch between steering and throttle mode\n\n").c_str());
}

void loop()
{
  int input;

  if (Serial.available() > 0)
  {
    // read the incoming data and parse it as an int
    input = Serial.parseInt();

    if (input == 0)
    {
      car.goNeutral();
      Serial.write("Car set to neutral\n");
    }

    else if (input < 0)
    {
      car.switchMode();
      Serial.write(("Switching to " + String(car.getMode() ? "Steer" : "Throttle") + "\n").c_str());
    }

    else if (car.getMode())
    {
      car.setSteering(input);
      Serial.write(("Steering: " + String(input) + "\n").c_str());
    }

    else
    {
      car.setThrottle(input);
      Serial.write(("Throttle: " + String(input) + "\n").c_str());
    }
  }
}

