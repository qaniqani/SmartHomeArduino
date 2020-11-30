#include <AFMotor.h>
#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte server[] = { 185, 12, 110, 49 };
byte ip[]     = { 192, 168, 13, 250 };

Servo CarDoor;
//Servo Curtain;
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

const int a0 = 0;
const int a1 = 1;
const int a2 = 2;
const int a3 = 3;
const int a4 = 4;
const int a5 = 5;
const int a6 = 6;

const int a8 = 8; //fire sensor
const int a9 = 9; //temperature sensor
const int a10 = 10; //gas sensor
const int a11 = 11; //pir sensor
const int a12 = 12; //water sensor
const int a13 = 13; //lightSensor
const int a14 = 14;
const int a15 = 15;

const int pin1 = 1;
const int pin2 = 2;
const int pin3 = 3;    //DC Motor 2 or Stepper Motor 1
const int pin4 = 4;    //DC/Stepper Motor drive
const int pin5 = 5;    //DC Motor 3 or Stepper Motor 2
const int pin6 = 6;    //DC Motor 6 or Stepper Motor 2
const int pin7 = 7;    //DC/Stepper Motor drive
const int pin8 = 8;    //DC/Stepper Motor drive
const int pin9 = 9;    //Servo Motor 2
const int pin10 = 10;  //Servo Motor 1
const int pin11 = 11;  //DC Motor 1 or Stepper Motor 1
const int pin12 = 12;  //DC/Stepper Motor drive
const int pin13 = 13;

const int pin22 = 22;  //Banyo
const int pin23 = 23;  //Mutfak
const int pin24 = 24;  //Wc
const int pin25 = 25;  //Salon
const int pin26 = 26;  //Yatak odasi
const int pin27 = 27;  //Cocuk odasi
const int pin28 = 28;  //Garaj
const int pin29 = 29;  //2. Cocuk odasi
const int pin30 = 30;  //Hol
const int pin31 = 31;  //Oturma odasi
const int pin32 = 32;
const int pin33 = 33;
const int pin34 = 34;
const int pin35 = 35;
const int pin36 = 36;
const int pin37 = 37;
const int pin38 = 38;
const int pin39 = 39;
const int pin40 = 40;
const int pin41 = 41;
const int pin42 = 42;
const int pin43 = 43;
const int pin44 = 44;
const int pin45 = 45;
const int pin46 = 46;
const int pin47 = 47;
const int pin48 = 48;
const int pin49 = 49;

#define MQTT_USERNAME "admin"
#define MQTT_PASSWORD "123456"
#define MQTT_SUBSCRIBETOPIC "ABlok/7584a0766efa4f09a62ed5" 
#define MQTT_CLIENTID "7584a0766efa4f09a62ed5"
#define MQTT_PUBLISHTOPIC "ABlok/7584a0766efa4f09a62ed5"
#define MQTT_ROLLBACKTOPIC "ABlok/MeStatus"
#define MQTT_QoS 0
#define MQTT_RETAIN0 0
#define MQTT_RETAIN1 1
#define DEVICE_TAG "Arduino"

#define MotorMaxSpeed 200

String urlParameter = "";
String messageTopic = "";
String clientId = "";
String commandType = "";
String deviceRef = "";
String roomRef = "";
int pin = 0;
int value = 0;
String deviceTag = "";
char message_buff[100];


//Sensor degiskenleri
String commandTypeTemperature = "";
String deviceRefTemperature = "";
String roomRefTemperature = "";
int pinTemperature = 0;

String commandTypeWater = "";
String deviceRefWater = "";
String roomRefWater = "";
int pinWater = 0;

String commandTypeAction = "";
String deviceRefAction = "";
String roomRefAction = "";
int pinAction = 0;

String commandTypeFire = "";
String deviceRefFire = "";
String roomRefFire = "";
int pinFire = 0;

String commandTypeGas = "";
String deviceRefGas = "";
String roomRefGas = "";
int pinGas = 0;

String commandTypeLightSensor = "";
String deviceRefLightSensor = "";
String roomRefLightSensor = "";
int pinLightSensor = 0;

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

unsigned long checkPreviousMillis  = 0;
unsigned long checkCurrentMillis   = 0;
//int interval = 300000; //5 minutes
int checkInterval = 60000; //1 munite

unsigned long betweenPreviousMillis  = 0;
unsigned long betweenCurrentMillis   = 0;
int betweenInterval = 5000; //1 munite

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("==STARTING==");
  
  //pinMode(pin0, OUTPUT);    //TX0
  //pinMode(pin1, OUTPUT);    //RX0
  //pinMode(pin2, OUTPUT);    
  //pinMode(pin3, OUTPUT);    
  //pinMode(pin3, OUTPUT);    //DC Motor 2 or Stepper Motor 1
  //pinMode(pin4, OUTPUT);    //DC/Stepper Motor drive
  //pinMode(pin5, OUTPUT);    //DC Motor 3 or Stepper Motor 2
  //pinMode(pin6, OUTPUT);    //DC Motor 6 or Stepper Motor 2
  //pinMode(pin7, OUTPUT);    //DC/Stepper Motor drive
  //pinMode(pin8, OUTPUT);    //DC/Stepper Motor drive
  //pinMode(pin9, OUTPUT);    //Servo Motor 2
  //pinMode(pin10, OUTPUT);   //Servo Motor 1
  //pinMode(pin11, OUTPUT);   //DC Motor 1 or Stepper Motor 1
  //pinMode(pin12, OUTPUT);   //DC/Stepper Motor drive
  //pinMode(pin13, OUTPUT);   //Blink pin
  //pinMode(pin14, OUTPUT);   //TX1
  //pinMode(pin15, OUTPUT);   //RX1
  //pinMode(pin16, OUTPUT);   //TX2
  //pinMode(pin17, OUTPUT);   //RX2
  //pinMode(pin18, OUTPUT);   //TX3
  //pinMode(pin19, OUTPUT);   //RX3
  //pinMode(pin20, OUTPUT);   //TX4
  //pinMode(pin21, OUTPUT);   //RX4
  pinMode(pin22, OUTPUT);  //Banyo
  pinMode(pin23, OUTPUT);  //Mutfak
  pinMode(pin24, OUTPUT);  //Wc
  pinMode(pin25, OUTPUT);  //Salon
  pinMode(pin26, OUTPUT);  //Yatak odasi
  pinMode(pin27, OUTPUT);  //Cocuk odasi
  pinMode(pin28, OUTPUT);  //Garaj
  pinMode(pin29, OUTPUT);  //2. Cocuk odasi
  pinMode(pin30, OUTPUT);  //Hol
  pinMode(pin31, OUTPUT);  //Oturma odasi
  pinMode(pin32, OUTPUT);
  pinMode(pin33, OUTPUT);
  pinMode(pin34, OUTPUT);
  pinMode(pin35, OUTPUT);
  pinMode(pin36, OUTPUT);
  pinMode(pin37, OUTPUT);
  pinMode(pin38, OUTPUT);
  pinMode(pin39, OUTPUT);
  pinMode(pin40, OUTPUT);
  pinMode(pin41, OUTPUT);
  pinMode(pin42, OUTPUT);
  pinMode(pin43, OUTPUT);
  pinMode(pin44, OUTPUT);
  pinMode(pin45, OUTPUT);
  pinMode(pin46, OUTPUT);
  pinMode(pin47, OUTPUT);
  pinMode(pin48, OUTPUT);
  pinMode(pin49, OUTPUT);
  
  CarDoor.attach(pin9); // Servo Motor
  CarDoor.write(150); //Closed
  
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  Serial.println("==STARTING==");
  delay(500);
  Serial.println("Connecting...");

  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
}

void loop()
{
  checkCurrentMillis = millis();
  betweenCurrentMillis = millis();
  
  if (!client.connected())
  {
    client.connect(MQTT_CLIENTID, MQTT_USERNAME, MQTT_PASSWORD);
    Serial.println("Server to connected.");
    client.subscribe(MQTT_SUBSCRIBETOPIC);
    client.publish(MQTT_ROLLBACKTOPIC, MQTT_CLIENTID);
  }

  if (urlParameter != "")
  {
    // 0        1            2          3          4        5           6
    //{topic}/{clientRef}/{roomRef}/{deviceRef}/{pinNr}/{deviceType}/{value}
    messageTopic = MQTT_PUBLISHTOPIC;
    clientId = getValue(urlParameter, '/', 1);
    roomRef = getValue(urlParameter, '/', 2);
    deviceRef = getValue(urlParameter, '/', 3);
    pin = getValue(urlParameter, '/', 4).toInt();
    commandType = getValue(urlParameter, '/', 5);
    value = getValue(urlParameter, '/', 6).toInt();
    deviceTag = getValue(urlParameter, '/', 7);
    
    Serial.println(urlParameter);
    if (messageTopic == MQTT_SUBSCRIBETOPIC && deviceTag != DEVICE_TAG)
    {
      Serial.println("girdi");
      if (clientId == MQTT_CLIENTID)
      {
        if (commandType == "CarDoor")
        {
          CarDoor.write(value);
        }
        else if (commandType == "Curtain")
        {
          if(value == 1)
          {
            motor1.run(FORWARD);
            for (int i=0; i<MotorMaxSpeed; i++) {
              motor1.setSpeed(i);
              delay(3);
            }
           
            for (int i=MotorMaxSpeed; i!=0; i--) {
              motor1.setSpeed(i);
              delay(3);
            }
          }

          if(value == 0)
          {
            motor1.run(BACKWARD);
            for (int i=0; i<MotorMaxSpeed; i++) {
              motor1.setSpeed(i);
              delay(3);
            }

            for (int i=MotorMaxSpeed; i!=0; i--) {
              motor1.setSpeed(i);
              delay(3);
            }
          }

          if(value == 2)
          {
            motor1.setSpeed(0);
            delay(3);
          }
        }
        else if (commandType == "digitalWrite")
        {
          digitalWrite(pin, value);
        }
        else if (commandType == "digitalRead")
        {
          int val = digitalRead(pin);
          String result = createMessageFormat(val);
          //toChar(result);
          result.toCharArray(message_buff, 100);
          client.publish(MQTT_PUBLISHTOPIC, message_buff);
        }
        else if (commandType == "analogWrite")
        {
          analogWrite(pin, value);
        }
        else if (commandType == "analogRead")
        {
          int val = analogRead(pin);
          String result = createMessageFormat(val);
          result.toCharArray(message_buff, 100);
          client.publish(MQTT_PUBLISHTOPIC, message_buff);
        }
        else if (commandType == "Temperature")
        {
          commandTypeTemperature = commandType;
          deviceRefTemperature = deviceRef;
          roomRefTemperature = roomRef;
          pinTemperature = pin;
          Temperature();
        }
        else if (commandType == "Fire")
        {
          commandTypeFire = commandType;
          deviceRefFire = deviceRef;
          roomRefFire = roomRef;
          pinFire = pin;
          Fire();
        }
        else if (commandType == "Water")
        {
          commandTypeWater = commandType;
          deviceRefWater = deviceRef;
          roomRefWater = roomRef;
          pinWater = pin;
          Water();
        }
        else if (commandType == "Action")
        {
          commandTypeAction = commandType;
          deviceRefAction = deviceRef;
          roomRefAction = roomRef;
          pinAction = pin;
          Action();
        }
        else if (commandType == "Gas")
        {
          commandTypeGas = commandType;
          deviceRefGas = deviceRef;
          roomRefGas = roomRef;
          pinGas = pin;
          Gas();
        }
        else if (commandType == "LightSensor")
        {
          commandTypeLightSensor = commandType;
          deviceRefLightSensor = deviceRef;
          roomRefLightSensor = roomRef;
          pinLightSensor = pin;
          LightSensor();
        }
      }
    }
    
    urlParameter = "";
  }
  
  //Action();
  if (betweenCurrentMillis - betweenPreviousMillis >= betweenInterval == true ) {
    
    Action();
    delay(10);
    Fire();    
    delay(10);
    Water();
    delay(10);
    Gas();
    delay(10);
    
    betweenPreviousMillis = betweenCurrentMillis;
  }
  
  //belirli araliklarla sensor degerlerini oku ve gonder.
  if (checkCurrentMillis - checkPreviousMillis >= checkInterval == true ) {
    
    Temperature();
    delay(10);    
    LightSensor();
    delay(10);
    checkPreviousMillis = checkCurrentMillis;
  }
  
  client.loop();
}

void Temperature()
{
  int val = analogRead(a9);
  int heat = map(val, 0, 1023, 0, 100);
  
  commandType = commandTypeTemperature;
  deviceRef = deviceRefTemperature;
  roomRef = roomRefTemperature;
  pin = pinTemperature;
  
  String result = createMessageFormat(heat);
  result.toCharArray(message_buff, 100);
  client.publish(MQTT_PUBLISHTOPIC, message_buff);
}

void Fire()
{
  int val = analogRead(a8);
  int range = map(val, 0, 1023, 0, 3);
  
  commandType = commandTypeFire;
  deviceRef = deviceRefFire;
  roomRef = roomRefFire;
  pin = pinFire;
  
  String result = createMessageFormat(range);
  result.toCharArray(message_buff, 100);
  client.publish(MQTT_PUBLISHTOPIC, message_buff);
}

void Water()
{
  int val = analogRead(a12);
  int range = map(val, 0, 1023, 0, 3);       

  commandType = commandTypeWater;
  deviceRef = deviceRefWater;
  roomRef = roomRefWater;
  pin = pinWater;
  
  String result = createMessageFormat(range);
  result.toCharArray(message_buff, 100);
  client.publish(MQTT_PUBLISHTOPIC, message_buff);
}

void Action()
{
  int val = analogRead(a11);
  if(val > 400)
  {
    val = 1;
    digitalWrite(pin29, HIGH);
  }
  else
  {
    val = 0;
    digitalWrite(pin29, LOW);
  }
  
  commandType = commandTypeAction;
  deviceRef = deviceRefAction;
  roomRef = roomRefAction;
  pin = pinAction;
  
  String result = createMessageFormat(val);
  result.toCharArray(message_buff, 100);
  client.publish(MQTT_PUBLISHTOPIC, message_buff);
}

void Gas()
{
  int val = analogRead(a10);
  if(val < 400)
  {
    val = 0;
  }
  else
  {
    val = val / 10;
  }
  
  commandType = commandTypeGas;
  deviceRef = deviceRefGas;
  roomRef = roomRefGas;
  pin = pinGas;
  
  String result = createMessageFormat(val);
  result.toCharArray(message_buff, 100);
  client.publish(MQTT_PUBLISHTOPIC, message_buff);
}

void LightSensor()
{
  int val = analogRead(a13);
  float voltage = val * (5.0 / 1023.0);
  
  commandType = commandTypeLightSensor;
  deviceRef = deviceRefLightSensor;
  roomRef = roomRefLightSensor;
  pin = pinLightSensor;
  
  String result = createMessageFormat(voltage);
  result.toCharArray(message_buff, 100);
  client.publish(MQTT_PUBLISHTOPIC, message_buff);
}

//message publish format
String createMessageFormat(int value)
{
  return messageTopic + "/" + roomRef + "/" + deviceRef + "/" + pin + "/" + commandType + "/" + value + "/Arduino";
}

//MQTT message receiver
void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.println(topic);
  payload[length] = '\0';
  String strPayload = String((char*)payload);
  urlParameter = strPayload;
}

//string parse
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

//string to char converter
void toChar(int value)
{
  String str;
  str = String(value);
  str.toCharArray(message_buff, 16);
}
