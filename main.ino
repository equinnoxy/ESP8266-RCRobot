/*
Code Name: Arduino Wifi Control Car 
Code URI: https://circuitbest.com/category/arduino-projects/
Additional Board Manager URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json 
Install: ESP8266 by ESP8266 Community
Author: Make DIY
Author URI: https://circuitbest.com/author/admin/
Description: This program is used to control a robot using a app
that communicates with Arduino through a ESP8266 Module.
App URI: https://drive.google.com/file/d/1pvtWsTeXhcJdpHMfGlFmbGDuH7eoLfoP/view?usp=sharing
Version: 2.0
License: Remixing or Changing this Thing is allowed. Commercial use is not allowed.
*/

/*
 Recoded by
 https://github.com/equinnoxy
 for removing some unused lines (pwm)
 */

//#define ENA   14          // Enable/speed motors Kiri          GPIO14(D5)
//#define ENB   12          // Enable/speed motors Kanan         GPIO12(D6)
#define IN_1  15          // L298N in1 motors Kiri             GPIO15(D8)
#define IN_2  13          // L298N in2 motors Kiri             GPIO13(D7)
#define IN_3  2           // L298N in3 motors Kanan            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Kanan            GPIO0(D3)

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;             // String to store app command state.
//int speedCar = 800;         // 400 - 1023.
//int speed_Coeff = 3;

const char* ssid = "sum0 pr0t0typ3"; // you can change wifi name here
const char* psk = "77889900"; // password
ESP8266WebServer server(80);

void setup() {
 Serial.begin(115200);
// pinMode(ENA, OUTPUT);
// pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, psk);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "/", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void jalanMaju(){ 
      Serial.println("Robot Maju");
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
//      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
//      analogWrite(ENB, speedCar);
  }

void jalanMundur(){ 
      Serial.println("Robot Mundur");
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
//      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
//      analogWrite(ENB, speedCar);
  }

void putarKiri(){ 
      Serial.println("Robot Putar Kiri");
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
//      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
//      analogWrite(ENB, speedCar);
  }

void putarKanan(){
      Serial.println("Robot Putar Kanan");
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
//      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
//      analogWrite(ENB, speedCar);
  }

/*
void jalanMajuKiri(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar/speed_Coeff);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
   }

void jalanMajuKanan(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void jalanMundurKiri(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar/speed_Coeff);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void jalanMundurKanan(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar/speed_Coeff);
  }
*/
void stopRobot(){  
      Serial.println("Robot Berhenti");
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
//      analogWrite(ENA, speedCar);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
//      analogWrite(ENB, speedCar);
 }

void loop() {
    server.handleClient();
    
      command = server.arg("State");
      if (command == "F") jalanMaju();
      else if (command == "B") jalanMundur();
      else if (command == "R") putarKanan();
      else if (command == "L") putarKiri();
/*    else if (command == "G") jalanMajuKiri();
      else if (command == "I") jalanMajuKanan();
      else if (command == "H") jalanMundurKiri();
      else if (command == "J") jalanMundurKanan();
      else if (command == "0") speedCar = 400;
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023;
      else if (command == "S") stopRobot();
*/
}

void HTTP_handleRoot(void) {

if( server.hasArg("State") ){
       Serial.println(server.arg("State"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
