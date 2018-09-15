 /*Wireless Serial using UDP ESP8266
    Hardware: NodeMCU
    Circuits4you.com
    2018
    Slave Board connects to Access Point
*/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
const char *ssid = "circuits4you";
const char *pass = "password"; 
 
unsigned int localPort = 2000; // local port to listen for UDP packets
 
IPAddress ServerIP(192,168,4,1); 
IPAddress ClientIP(192,168,4,2);
 
// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;
 
char packetBuffer[9];   //Where we get the UDP data
//======================================================================
//                Setup
//======================================================================
#define R D2
#define Y D5
#define a1 D1
#define a2 D2
#define b1 D3
#define b2 D4
void setup()
{
  pinMode(a1,OUTPUT);pinMode(a2,OUTPUT); pinMode(b1,OUTPUT);pinMode(b2,OUTPUT);
    
    Serial.begin(9600);
    Serial.println();
 
    WiFi.begin(ssid, pass);   //Connect to access point
  
    Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
    
    //Start UDP
    Serial.println("Starting UDP");
    udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(udp.localPort());
}
//======================================================================
//                MAIN LOOP
//======================================================================
void loop()
{
    int cb = udp.parsePacket();
    /*if (!cb)*/ 
    /*{
      //If serial data is recived send it to UDP
      if(Serial.available()>0)
        {
        udp.beginPacket(ServerIP, 2000);  //Send Data to Master unit
        //Send UDP requests are to port 2000
        
        char a[1];
        a[0]=char(Serial.read()); //Serial Byte Read
        udp.write(a,1); //Send one byte to ESP8266 
        udp.endPacket();
        }
    }*/
    if (cb) {
      // We've received a UDP packet, send it to serial
      udp.read(packetBuffer, 1); // read the packet into the buffer, we are reading only one byte
      Serial.print(packetBuffer);
      
      
      
      if(*packetBuffer == 'f'){
       foreward();
       ;
       }
      else if (*packetBuffer == 'r'){
       right();
       }
       else if(*packetBuffer == 'l'){
       left();
       }
       else if (*packetBuffer == 'h'){
       halt();
       }        
    }
}


void foreward(){
  //Serial.println("f");
  digitalWrite(a2, HIGH);
  digitalWrite(b2, LOW);
  digitalWrite(a1, HIGH);
  digitalWrite(b1, LOW);
     
    }
void right(){
  //Serial.println("r");
  digitalWrite(a2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH);
  digitalWrite(a1, HIGH);}
void left(){
  //Serial.println("l");
  digitalWrite(a2, HIGH);
  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);
  digitalWrite(a1, LOW);}
void halt(){
  //Serial.println("h");  
  digitalWrite(a2, LOW);
  digitalWrite(b1, LOW);
  digitalWrite(b2, LOW);
  digitalWrite(a1, LOW);  
}
