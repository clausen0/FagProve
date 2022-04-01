#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
 
 //tilt pin input and output
int tiltPin = 3;
int tiltState = 0;

//shock sensor
int shockSensorPin = 4;
int greenLedPin = 13;
int redLedPin = 12;

bool shockSensorState = 0;

// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 


void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();

  //setting input for tilt
  pinMode(tiltPin, INPUT);

  //shock sensor
  pinMode(shockSensorPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  shockSensorState = digitalRead(shockSensorPin);
}
 
 
void loop(void)
{
  //for loop , count uppwards to 60 to get a tempratur mesurment every 60 seconds
  for (int i = 0; i <= 60;  i++)
  {
    //activates when the counter hits 60
    if(i == 60){
      // call sensors.requestTemperatures() to issue a global temperature
      // request to all devices on the bus
      Serial.print(" Requesting temperatures...");
      sensors.requestTemperatures(); // Send the command to get temperatures
      Serial.println("DONE");

      Serial.print("Temperature is: ");
      Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"? 
        // You can have more than one IC on the same bus. 
        // 0 refers to the first IC on the wire
    }
    delay(1000);
    //Serial.print(i);

    //Getting tilt switch state
    tiltState = digitalRead(tiltPin);

    if(tiltState == HIGH){
      Serial.print("Tilt");
    }

    if(shockSensorState == 1){
      digitalWrite(greenLedPin, LOW);
      for (int k = 0; k < 10; k++)
      {
        digitalWrite(redLedPin, HIGH);
        delay(150);
        digitalWrite(redLedPin, LOW);
        delay(150);
        if(k == 9){
          shockSensorState = 0;
        }
      }
      
    }
    else{
      shockSensorState = digitalRead(shockSensorPin);
      digitalWrite(greenLedPin, HIGH);
    }
  }
}