
#include<stdbool.h>

const float zero_c_volts = 0.5;
const float fifty_c_volts = 1.0;
const int raw_temp_offset = 102;
constexpr float c_per_count = 50.0/103.0;

bool fahrenheitMode = false;

void setup() {
  // usb io
  Serial.begin(9600);
  // uno io
  Serial1.begin(9600); 
}

void loop() {

  // serial monitor input 
  if (Serial.available() == 1) {
    char input = Serial.read();
    switch(input) {
      case 'c' : {
        fahrenheitMode = false;
        break;
      }
      case 'f' : {
        fahrenheitMode = true;
        break;
      }
      case 't' : {
        /* 
          tempReading is not in volts or millivolts.
          It is a number between 0 and 1023.
          1023 corresponds to 5.0V on an AVR Arduino or to 3.3V on an ARM or to AREF.
          The TMP 36 nominally produces 1.0V at 50C and 0.5V at 0C
        */
        // request temp
        Serial1.write('t');
        delay(100);
        // tempReading in buffer
        //Serial.println(Serial1.read(), HEX);
        if (Serial1.available() == 2) {
          uint16_t tempReading = Serial1.read() + (Serial1.read() << 8); // 153 @ 25C
          float temp = (tempReading - raw_temp_offset) * c_per_count;
          if(fahrenheitMode) {
            temp *= 9.0/5.0;
            temp += 32.0;
          } 
          Serial.print("Temperature: ");
          Serial.print(temp);
          if(fahrenheitMode) {
            Serial.println(" F");
          } else { 
            Serial.println(" C");
          }
        }
        else {
          Serial.println("Improper temp data");
          Serial.print("Number of bytes received: ");
          Serial.println(Serial1.available());
        }
        break;
      }
      case 'b' : {
        // request brightness
        Serial1.write('b');
        delay(100);
        // brightness in buffer
        if (Serial1.available() == 2) {
          uint16_t photocellReading = Serial1.read() + (Serial1.read() << 8); // 153 @ 25C
          Serial.print("Brightness: ");
          Serial.println(photocellReading);
        }
        else {
          Serial.println("Improper brightness data");
          Serial.print("Number of bytes received: ");
          Serial.println(Serial1.available());
        }
        break;
      }
      default : {
        Serial.println("Invalid request.");
        break;
      }
      Serial1.flush();
    }
  }
  
    delay(100);
}
