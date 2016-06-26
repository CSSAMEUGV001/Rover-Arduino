#include <Servo.h>

class Car
{
  public:
    //Constructor
    Car(): ABS_MAX_THROTTLE(140), ABS_MIN_THROTTLE(40),
           ABS_MAX_STEER(140), ABS_MIN_STEER(53),
           MAX_THROTTLE(105), MIN_THROTTLE(75),
           MAX_STEER(ABS_MAX_STEER), MIN_STEER(ABS_MIN_STEER)
    {}

    //Arduino has issues with placing code in the constructor so we use this 
    //  to initialize instead
    void InitCar(const int& steeringPin, const int& throttlePin, const int& neutralValue)
    {
      steer.attach(steeringPin);
      throttle.attach(throttlePin);

      steeringOn = true;

      this->neutralValue = neutralValue;
    }

    //Sets throttle and steering to neutral
    void goNeutral()
    {
      this->setSteering(neutralValue);
      this->setThrottle(neutralValue);
    }

    //Switches between steering and throttle mode
    void switchMode()
    {
      steeringOn = !steeringOn;
    }

    //Sets the throttle over time instead of right away
    void setThrottle(int value)
    {
      if (value < MIN_THROTTLE)
      {
        outputError(value, MIN_THROTTLE);
        value = MIN_THROTTLE;
      }
      else if (value > MAX_THROTTLE)
      {
        outputError(value, MAX_THROTTLE);
        value = MAX_THROTTLE;
      }

      int currentVal = throttle.read();

      if (value > currentVal)
        for (currentVal; currentVal <= value; currentVal++)
        {
          wait(WAIT_TIME);
          throttle.write(currentVal);
        }
      else
        for (currentVal; currentVal >= value; currentVal--)
        {
          wait(WAIT_TIME);
          throttle.write(currentVal);
        }
    }

    //Sets steering value
    void setSteering(int value)
    {
      if (value > MAX_STEER)
      {
        outputError(value, MAX_STEER);
        value = MAX_STEER;
      }

      else if (value < MIN_STEER)
      {
        outputError(value, MIN_STEER);
        value = MIN_STEER;
      }

      steer.write(value);
    }

    //True means steering is on
    //False means throttle is on
    bool getMode() const
    {
      return steeringOn;
    }

    //Used to tell user input is out of range
    void outputError(const int& badValue, const int& newValue) const
    {
      Serial.write((String(badValue) + " is not within range. Setting to " + newValue + ".\n").c_str());
    }

    //Loops until passed in amount of milliseconds have passed
    void wait(const unsigned long& timeToWait)
    {
      unsigned long currentTime = millis();

      while( millis() - currentTime < timeToWait) {}
    }

    //Absoulte limits imposed by the hardware on the throttle and steering
    const int ABS_MAX_THROTTLE;  //Forward
    const int ABS_MIN_THROTTLE;  //Reverse
    const int ABS_MAX_STEER;     //Left
    const int ABS_MIN_STEER;     //Right

    //Limits imposed by the user on the throttle and steering
    const int MAX_THROTTLE;
    const int MIN_THROTTLE;
    const int MAX_STEER;
    const int MIN_STEER;

  private:
    int neutralValue;
    bool steeringOn;
    Servo steer;
    Servo throttle;

    //Amount of milliseconds to wait for
    const unsigned long WAIT_TIME = 15UL;
};

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

