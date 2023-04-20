
const int photocellPin = A0;
const int tempPin = A1;

void setup() {
  // mega io
  Serial.begin(9600);
  // pinmodes
  pinMode(photocellPin, INPUT);
  pinMode(tempPin, INPUT);
}

void loop() {
  
  if(Serial.available()) {
    //Serial.write(Serial.available());
    char input = Serial.read();
    switch(input) {
      case 't' : {
        //Serial.println("temp");
        uint16_t tempReading = analogRead(tempPin); // 153 @ 25C
        byte bytes[2]{};
        *bytes = tempReading;
        Serial.write(bytes, 2);
        
        //Serial.println(bytes[1]);
        break;
      }
      case 'b' : {
        //Serial.println("brightness");
        int photocellReading = analogRead(photocellPin);
        byte bytes[2]{};
        *bytes = photocellReading;
        Serial.write(bytes, 2);
        //Serial.println(bytes[1]);
        break;
      }
      default : {
        //Serial.print(input);
        //Serial.println(" : Invalid request.");
        break;
      }
      Serial.flush();
    }
  }
  delay(100);
}
