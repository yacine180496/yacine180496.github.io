#include <rn2xx3.h>
#include <SoftwareSerial.h>
#include <MiCS6814-I2C.h>

MiCS6814 sensor;
bool sensorConnected;

#define DEBUG
#define LEDPIN 13
//Sur le shield => // TX = 10 // RX = 11 // RST = 12
#define TX  10
#define RX  11
#define RST  12
SoftwareSerial mySerial(TX, RX); // RX, TX

const char *devAddr = "260B7A60";
const char *nwkSKey = "01F0AB151259E2AB81FD5F89F56A16EC";
const char *appSKey = "C45F67ECFF17414A86DA06C499CCE19F";

rn2xx3 myLora(mySerial);

void led_on() {digitalWrite(LEDPIN, HIGH);}
void led_off() {digitalWrite(LEDPIN, LOW);}

void setup() {
  pinMode(LEDPIN, OUTPUT);
  led_on();

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Startup");

  // Reset rn2483
  pinMode(RST, OUTPUT);
  digitalWrite(RST, HIGH);
  digitalWrite(RST, LOW);
  delay(500);
  digitalWrite(RST, HIGH);

  // Initialize gas sensor
  
  init_gas_sensor();

  // Buzzer

  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);

  // Initialise the rn2483 module
  myLora.autobaud();

  Serial.println("When using OTAA, register this DevEUI: ");
  Serial.println(myLora.hweui());
  Serial.print("RN2483 version number: ");
  Serial.println(myLora.sysver());

  myLora.initABP(devAddr, appSKey, nwkSKey);

  led_off();
  delay(200);
}

void init_gas_sensor(){
  sensorConnected = sensor.begin();

    if (sensorConnected == true) {
    // Print status message
    Serial.println("Connected to MiCS-6814 sensor");
    // Turn heater element on
    sensor.powerOn();

    sensor.begin(0X04);

  } else {
    // Print error message on failed connection
    Serial.println("Couldn't connect to MiCS-6814 sensor");
  }
  
}

void monitor_COValue(int CO2){
  
  if(CO2 > 50){
  
    digitalWrite(6, HIGH);
    delay(1000);
    digitalWrite(6, LOW);
    delay(1000);
  }
  else if(CO2 > 20){

    digitalWrite(6, HIGH);
    delay(100);
    digitalWrite(6, LOW);
    delay(100);    
  }
  else{

        digitalWrite(6, LOW);
  } 
}

void loop() {
  //led_on();
  #ifdef DEBUG
    Serial.println("TXing");
 #endif
 
   //CO2
  int COValue;

  COValue = sensor.measureCO();

  Serial.println("CO value : " + String(COValue));

  monitor_COValue(COValue);

  myLora.tx(String(COValue));  //Payload a envoyer sur TTN

  delay(2000);
}
