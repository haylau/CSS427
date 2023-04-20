#include <stdbool.h>
#define INPUTPIN 2
#define WHEEL_DIAMETER_MM 445
#define PI ((float) 3.1415925)

volatile long time_ms;
volatile long interval_ms;
volatile bool measure;
volatile static int counter;

void setup() {
  Serial.begin(115200); //serial monitor

  pinMode(INPUTPIN, INPUT);
  attachInterrupt (digitalPinToInterrupt(2), cyclometer, HIGH); 
  measure = false;
  counter = 0;
}

void loop() {

  if (measure) {
    
    noInterrupts();
    measure = false;
    long curInterval_ms = interval_ms;
    counter = 0;
    interrupts();

    // Serial.print(circumference_km);
    float speed_kph = ((float)WHEEL_DIAMETER_MM / 1000.0) / (curInterval_ms / 60.0 / 60.0); 

    Serial.print("Interval: ");
    Serial.print(curInterval_ms);
    Serial.println(" ms");

    Serial.print("Speed: ");
    Serial.print(speed_kph);
    Serial.println(" kph\n");
    
  }
  if (counter >= 10) {
    Serial.println("Interval: >=10 sec");
    Serial.print("Speed: 0 kph\n\n");
  }
  counter++;
  delay(1000);
}

void cyclometer() {
  noInterrupts();
  counter = 0;
  long curTime = millis();

  if(curTime - time_ms > 100) {
    interval_ms = curTime - time_ms;
    time_ms = curTime;
    measure = true;
  }
  
  interrupts();
}
