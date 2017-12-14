#include <Wire.h>

#include "Car.h"

const int POT_PIN = 0;
const int NEUTRAL_VALUE = 90;
const int SAMPLES = 10;
int steeringSamples[SAMPLES];
int throttleSamples[SAMPLES];
int potSamples[SAMPLES];
int wireIndex;
int potIndex;
Car car;

int average(int ar[SAMPLES]){
  int sum = 0;
  for(int i = 0; i < SAMPLES; i++){
    sum += ar[i];
  }
  return sum/SAMPLES;
}

void setup() {
  wireIndex = 0;
  potIndex = 0;
  for(int i = 0; i < SAMPLES; i++){
    steeringSamples[i] = 0;
    throttleSamples[i] = 0;
    potSamples[i] = 0;
  }
  Wire.begin(0x2a);             
  Wire.onReceive(receiveEvent);
  //Serial.begin(9600);

    /* Inits the car using:
   *  Pin 10 for steering
   *  Pin 11 for throttle
   *  90 for the neutral value
   */
  car.InitCar(10, 11, NEUTRAL_VALUE);

  //Sets steering and throttle to neutral
  car.goNeutral();
}

void loop() {}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  int value = analogRead(POT_PIN);
  
  potSamples[potIndex] = value;
  value = average(potSamples);
  potIndex++;
  potIndex %= SAMPLES;

  int maxT = NEUTRAL_VALUE + (value/1023.0 * 50);
  int minT = NEUTRAL_VALUE - (value/1023.0 * 50);
  //Serial.println(String(maxT) + "\t" + minT);

  if(car.getMaxThrottle() != maxT)
    car.setMaxThrottle(maxT);
    
  if(car.getMinThrottle() != minT)
    car.setMinThrottle(minT);
  
  while (Wire.available()) 
  {
    int steering = Wire.read();
    int throttle = Wire.read();
    
    steeringSamples[wireIndex] = steering;
    throttleSamples[wireIndex] = throttle;
    wireIndex++;
    wireIndex %= SAMPLES;
    
    steering = average(steeringSamples);
    throttle = average(throttleSamples);

    if(car.getSteering() != steering)
      car.setSteering(steering);
    
    if(car.getThrottle() != throttle)
      car.setThrottle(throttle);
    //Serial.println("Steering: " + String(steering) + "\tThrottle: " + throttle);      // print the character
  }
}
