
//inter hvilke pinner som skal bli brukt til sensor og dioder som lyser på ulike kondisjoner
int shockSensorPin = 2;
int greenLedPin = 3;
int redLedPin = 4;

//setter en bolsk variabel
bool shockSensorSate = 0;

void setup() {
pinMode(shockSensorPin,INPUT);
pinMode(greenLedPin,OUTPUT);
pinMode(redLedPin,OUTPUT);

//den bolske variablen er sensor ingang
shockSensorSate = digitalRead(shockSensorPin);
}

void loop() {
  
  if (shockSensorSate == 1){
      digitalWrite(greenLedPin,LOW);  
      for ( int i=0; i < 10;i++){      
      digitalWrite(redLedPin,HIGH);
      delay(150);
      digitalWrite(redLedPin,LOW);
      delay(150);
      if ( i == 9){
        shockSensorSate = 0;
      }
      }
    }
    else {
      shockSensorSate = digitalRead(shockSensorPin);
      digitalWrite(greenLedPin,HIGH);
    }
}