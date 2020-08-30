#include <analogWrite.h>
#include <SimpleTimer.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "HX711.h"
#define calibration_factor -11373.09 //Calibration sketch
#define DOUT  12
#define CLK  14
float t;
HX711 scale;
#include <DHT.h>
#define DHTPIN 21
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
char auth[] = "b2RmvUDC0SIGxj-SU8u11qYk3eLraWJt";

// Your WiFi credentials.
// Set password to "" for open networks.
//char ssid[] = "digitak_studio";
//char pass[] = "P4stiB1sa";
char ssid[] = "Xperia XZ1";
char pass[] = "mamatnaga";

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
 
  if (isnan(h) || isnan(t)) {
    
    return;
  }
  
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V7, h);
}

#define MOTOR1 16 //IN1
#define MOTOR2 17 //IN2
#define MOTOR3 18 //IN3
#define MOTOR4 19 //IN4
#define EN1 25 //IN2
#define EN2 26 //IN3

int maxSpeed = 1023;
int noSpeed = 0;

#define relay1 33
#define relay2 32
#define laser 27
void moveControl(int x, int y) {if(y == 1  && x >= 0) {
analogWrite(EN1,maxSpeed);
analogWrite(EN2,maxSpeed);
digitalWrite(MOTOR1,HIGH);
digitalWrite(MOTOR2,LOW);
digitalWrite(MOTOR3,HIGH);
digitalWrite(MOTOR4,LOW); }
////MOVE FORWARD RIGHT
//
//else if(x <= minRange && y >= maxRange ) {
//
//digitalWrite(EN1,maxSpeed);
//
//digitalWrite(EN2,minSpeed);
//
//digitalWrite(MOTOR1,HIGH);
//
//digitalWrite(MOTOR2,HIGH);
//
//digitalWrite(MOTOR3,LOW);
//
//digitalWrite(MOTOR4,LOW); } 

// move right

else if(x == 1 && y == 0)
{ analogWrite(EN1,180);
analogWrite(EN2,180);
digitalWrite(MOTOR1,LOW);
digitalWrite(MOTOR2,HIGH);
digitalWrite(MOTOR3,HIGH);
digitalWrite(MOTOR4,LOW);
}
//stop
else if(x == 0 && y == 0 )
{ analogWrite(EN1,0);
analogWrite(EN2,0);
digitalWrite(MOTOR1,LOW);
digitalWrite(MOTOR2,LOW);
digitalWrite(MOTOR3,LOW);
digitalWrite(MOTOR4,LOW);
}

//// move forward LEFT
//
//else if(x <= minRange && y >= maxRange ) {
//
//digitalWrite(EN1,minSpeed);
//
//digitalWrite(EN2,maxSpeed);
//
//digitalWrite(MOTOR1,HIGH);
//
//digitalWrite(MOTOR2,HIGH);
//
//digitalWrite(MOTOR3,LOW);
//
//digitalWrite(MOTOR4,LOW); }

// moveleft
else if(x == -1 && y == 0) {
analogWrite(EN1,180);
analogWrite(EN2,180);
digitalWrite(MOTOR1,HIGH);
digitalWrite(MOTOR2,LOW);
digitalWrite(MOTOR3,LOW);
digitalWrite(MOTOR4,HIGH); }


// move back

else if(y == -1 && x == 0) {
analogWrite(EN1,maxSpeed);
analogWrite(EN2,maxSpeed);
digitalWrite(MOTOR1,LOW);
digitalWrite(MOTOR2,HIGH);
digitalWrite(MOTOR3,LOW);
digitalWrite(MOTOR4,HIGH); 
}
else{
analogWrite(EN1,0);
analogWrite(EN2,0);
digitalWrite(MOTOR1,LOW);
digitalWrite(MOTOR2,LOW);
digitalWrite(MOTOR3,LOW);
digitalWrite(MOTOR4,LOW); }
}

//// move back and right
//
//else if(y <= minRange && x <= minRange) {
//
//digitalWrite(EN1,maxSpeed);
//
//digitalWrite(EN2,minSpeed);
//
//digitalWrite(MOTOR1,LOW);
//
//digitalWrite(MOTOR2,HIGH);
//
//digitalWrite(MOTOR3,LOW);
//
//digitalWrite(MOTOR4,HIGH); }

//// move back and left
//
//else if(y <= minRange && x >= maxRange) {
//
//digitalWrite(EN1,minSpeed);
//
//digitalWrite(EN2,maxSpeed);
//
//digitalWrite(MOTOR1,LOW);
//
//digitalWrite(MOTOR2,LOW);
//
//digitalWrite(MOTOR3,HIGH);
//
//digitalWrite(MOTOR4,HIGH); } }

// SETUP
void setup()
{
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor);
  dht.begin();
  timer.setInterval(1000L, sendSensor); 
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
  pinMode(MOTOR3, OUTPUT);
  pinMode(MOTOR4, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(laser, OUTPUT);

  analogWrite(EN1,0);
  analogWrite(EN2,0);
  digitalWrite(MOTOR1,LOW);
  digitalWrite(MOTOR2,LOW);
  digitalWrite(MOTOR3,LOW);
  digitalWrite(MOTOR4,LOW);
  
  
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }

  //Serial.println("WiFi connected");  

  //Blynk.begin("b2RmvUDC0SIGxj-SU8u11qYk3eLraWJt", ssid, pass);
  Blynk.begin(auth,ssid,pass, IPAddress(47,251,15,245),8080);
  //47.251.15.245:9443

  // Connect Blynk
  //Blynk.begin(auth, ssid, pass);
}
//
//// Handling joystick data 
//BLYNK_WRITE(V2){ 
//     int x = param[0].asInt();
//     int y = param[1].asInt();
//     
//     if (x == 0 && y == 1) {// Forwards
//     //Serial.println("Moving Forwards");
//     digitalWrite(EN1, HIGH);
//     digitalWrite(EN2, HIGH);
//     digitalWrite(MOTOR1, HIGH);
//     digitalWrite(MOTOR2, LOW);
//     digitalWrite(MOTOR3, HIGH);
//     digitalWrite(MOTOR4, LOW);
//     }  else if (x == 0 && y == -1) {//  Backwards
//     //Serial.println("Moving Backwards");
//     digitalWrite(EN1, HIGH);
//     digitalWrite(EN2, HIGH);
//     digitalWrite(MOTOR1, LOW);
//     digitalWrite(MOTOR2, HIGH);
//     digitalWrite(MOTOR3, LOW);
//     digitalWrite(MOTOR4, HIGH);
//     }  else if (x == -1 && y == 0) {// Right
//     //Serial.println("Turning Right");
//     analogWrite(EN1, 250);
//     analogWrite(EN2, 450);
//     
//     digitalWrite(MOTOR1, LOW);
//     digitalWrite(MOTOR2, HIGH);
//     digitalWrite(MOTOR3, 150);
//     digitalWrite(MOTOR4, LOW);
//     while (dutyCycle <= 200){
//       ledcWrite(pwmChannel, dutyCycle);   
//       dutyCycle = dutyCycle + 5;
//     }  else if (x == 1 && y == 0) {// Left
//     //Serial.println("Turning Left");
//     analogWrite(EN1, 450);
//     analogWrite(EN2, 250);
//     
//     digitalWrite(MOTOR1, HIGH);
//     digitalWrite(MOTOR2, LOW);
//     digitalWrite(MOTOR3, LOW);
//     digitalWrite(MOTOR4, 150);
//     while (dutyCycle <= 200){
//       ledcWrite(pwmChannel, dutyCycle);   
//       dutyCycle = dutyCycle + 5;
//    }
//    /*
//    
//    else if (x == 1 && y == 1) {// Forwards Left 
//     //Serial.println("Moving Forwards and Left");
//     digitalWrite(MOTOR1, HIGH);
//     digitalWrite(MOTOR2, LOW);
//     digitalWrite(MOTOR3, LOW);
//     digitalWrite(MOTOR4, HIGH);
//     }  else if (x == -1 && y == 1) {// Forwards Right
//     //Serial.println("Moving Forwards and Right");
//     digitalWrite(MOTOR1, LOW);
//     digitalWrite(MOTOR2, HIGH);
//     digitalWrite(MOTOR3, HIGH);
//     digitalWrite(MOTOR4, LOW);
//     }  else if (x == 1 && y == -1) {// Backwards Left
//     //Serial.println("Moving Backwards and Left");
//     digitalWrite(MOTOR1, HIGH);
//     digitalWrite(MOTOR2, LOW);
//     digitalWrite(MOTOR3, LOW);
//     digitalWrite(MOTOR4, HIGH);
//     }  else if (x == -1 && y == -1) {// Backwards Right
//     //Serial.println("Moving Backwards and Right");
//     digitalWrite(MOTOR1, LOW);
//     digitalWrite(MOTOR2, HIGH);
//     digitalWrite(MOTOR3, HIGH);
//     digitalWrite(MOTOR4, LOW);
//     } */ 
//    else {
//     //Serial.println("Motors Stopped");
//     analogWrite(EN1, LOW);
//     analogWrite(EN2, LOW);
//     digitalWrite(MOTOR1, LOW);
//     digitalWrite(MOTOR2, LOW);
//     digitalWrite(MOTOR3, LOW);
//     digitalWrite(MOTOR4, LOW);
//     }

BLYNK_WRITE(V8) {
  int button = param.asInt(); // read button
  if (button == 1) {
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,HIGH);
  }
  else{
      digitalWrite(relay1,LOW);
      digitalWrite(relay2,LOW);
      }
      
}
BLYNK_WRITE(V9) {
  int button = param.asInt(); // read button
  if (button == 1) {
    digitalWrite(laser,HIGH);
  }
  else{
      digitalWrite(laser,LOW);
      }
}
     BLYNK_WRITE(V3) {
  int button = param.asInt(); // read button
  if (button == 1) {
    scale.tare();
    }
}
//MAIN CODE
void loop()
{
  Blynk.run();
  timer.run();
//scale.set_scale(calibration_factor);
  t = scale.get_units(2);
  Blynk.virtualWrite(V5,t);
}
  BLYNK_WRITE(V2)
{ int x = param[0].asInt();

int y = param[1].asInt();

moveControl(x,y); }
