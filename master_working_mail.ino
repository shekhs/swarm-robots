/*
Wireless Serial using UDP ESP8266
    Hardware: NodeMCU
    Circuits4you.com
    2018
    Master Board creates Access Point
*/
char a[1];
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
//=======================================================================
//                Setup
//=======================================================================

#define a1 D1
#define a2 D2
#define b1 D3
#define b2 D4
#define dataL D5
#define dataR D6

int datavalL;
int datavalR;

void setup()
{
pinMode(a1, OUTPUT);analogWrite(a1,0);
pinMode(a2, OUTPUT);digitalWrite(a2, LOW);
pinMode(b1, OUTPUT);analogWrite(b1, 0);
pinMode(b2, OUTPUT);digitalWrite(b2, LOW);
pinMode(dataL, INPUT);
pinMode(dataR, INPUT);
    Serial.begin(9600);
    Serial.println();
    WiFi.softAP(ssid, pass);    //Create Access point
    //Start UDP
    Serial.println("Starting UDP");
    udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(udp.localPort());
    delay(15000);
    
}
//======================================================================
//                MAIN LOOP
//======================================================================
void loop()
{   

 datavalR = digitalRead(dataR);
 datavalL = digitalRead(dataL);
 // Serial.print("dataL =");Serial.println(datavalL);
 // Serial.print("dataR =");Serial.println(datavalR);
       if (datavalR==0 && datavalL==0) foreward();
  else if (datavalR==0 && datavalL==1) right();
  else if (datavalR==1 && datavalL==0) left();
  else if (datavalR==1 && datavalL==1) halt();
    //char R,L;
    //if (datavalR == 0) R='0';
   //else if (datavalR == 1) R='1';

   
    //if (datavalL == 0) L='0';
   //else if (datavalL == 1) L='1';
   
    
    //delay(20);
    
    
    int cb = udp.parsePacket();
    if (!cb) 
    {
      
      //If serial data is recived send it to UDP
     // if(Serial.available()>0)
        
      {
          
        udp.beginPacket(ClientIP, 2000);
        //Send UDP requests are to port 2000

    //    char a[1];
        
        //a[0]=char(Serial.read()); //Serial Byte Read
        //a=val;
        //char b='0'; 
       // Serial.print("R:");Serial.print(&R);Serial.print("L:");Serial.print(&L);
        //Serial.print(a);
        udp.write(a,1); 
        udp.endPacket();
        }
    }
  /*  else {
      // We've received a UDP packet, send it to serial
      udp.read(packetBuffer, 1); // read the packet into the buffer, we are reading only one byte
      Serial.print(packetBuffer);
      delay(20);
    }*/
}


void foreward(){
  a[0]='f';
  Serial.println('f');
  digitalWrite(a2, HIGH);
  digitalWrite(b2, LOW);
  analogWrite(a1, 600);
  analogWrite(b1, 0);
     
    }
void right(){
  a[0]='r';
  Serial.println('r');     
  digitalWrite(a2, LOW);
  analogWrite(b1, 0);
  digitalWrite(b2, HIGH);
  analogWrite(a1, 600);}
void left(){
  a[0]='l';  
  Serial.println('l');
  digitalWrite(a2, HIGH);
  analogWrite(b1, 600);
  digitalWrite(b2, LOW);
  analogWrite(a1, 0);}
void halt(){
  a[0]='h';
  Serial.println('h');
  digitalWrite(a2, LOW);
  analogWrite(b1, 0);
  digitalWrite(b2, LOW);
  analogWrite(a1, 0);;  
}
