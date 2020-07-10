#include <WaziDev.h>
#include <DHT.h>

int fanRelayPin = 4;
int tempSensorPin = 3;
int peltierRelayPin = 5;

//Constants
#define DHTPIN 2    
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

WaziDev wazidev("IncubatorOne", 8);

void setup() {
  wazidev.setup();
  
  Serial.begin(38400); 
  Serial.println("INCUBATOR");
  
  // put your setup code here, to run once:
  pinMode(fanRelayPin, OUTPUT);
  pinMode(peltierRelayPin, OUTPUT);

  pinMode(tempSensorPin, OUTPUT); 
  digitalWrite(tempSensorPin, HIGH);

  fanOff();
  peltierOff();
  
  dht.begin();
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    h = dht.readHumidity();
    t = dht.readTemperature();
    delay(2000);
  } else {
    Serial.println("Sending value to gateway");
    Serial.println(t);
    wazidev.sendSensorValue("TC", t);  
  }

  if(t < 36.00){
    peltierOn();
    fanOff();
    delay(5000);
  } else {
    peltierOff();
    fanOn();
  }

  //fanOff();
  delay(2500);
}


void fanOn(){
  //turns the relay off
  digitalWrite(fanRelayPin, LOW);
}

void fanOff(){
  //turns the relay off
  digitalWrite(fanRelayPin, HIGH);
}

void peltierOn(){
  //turns the relay off
  digitalWrite(peltierRelayPin, LOW);
}

void peltierOff(){
  //turns the relay off
  digitalWrite(peltierRelayPin, HIGH);
}
