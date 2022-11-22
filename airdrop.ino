#include <ESP32Servo.h>
#include <WiFi.h>
#include <WebServer.h>

const int servoPin = 13;
bool servo_state = LOW;
int pos = 0;

const char* ssid     = "Airdrop";
const char* password = "Airdrop";

IPAddress local_ip(192,168,0,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

Servo myservo;
WebServer server(80);



void setup() {
  myservo.attach(servoPin);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/",main_page);
  server.on("/airdrop_open", airdrop_open);
  server.on("/airdrop_close", airdrop_close);

  server.begin();

  
}

void loop() {
    server.handleClient();
}

    void main_page(){
     server.send(200, "text/html", SendHTML(false)); 
}


    void airdrop_open(){
    for (pos = 190; pos >= 80; pos -= 1) { 
      myservo.write(pos);    
      delay(15);             
  }          
    server.send(200, "text/html", SendHTML(false)); 
 }

    void airdrop_close(){
      for (pos = 80; pos <= 190; pos += 1) { 
          myservo.write(pos);    
          delay(15);           
    } 
      server.send(200, "text/html", SendHTML(true)); 

      } 
         
    String SendHTML(uint8_t servo_state){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Drone Airdrop</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Airdrop Switch</h1>\n";
   if(servo_state)
  {ptr +="<p>Airdrop Status: Open</p><a class=\"button button-off\" href=\"/airdrop_open\">OFF</a>\n";}
  else
  {ptr +="<p>Airdrop Status: Close</p><a class=\"button button-on\" href=\"/airdrop_close\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
  
  
