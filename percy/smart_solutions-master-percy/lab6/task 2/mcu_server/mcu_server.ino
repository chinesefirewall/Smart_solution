// Ref : http://www.esp8266.com/viewtopic.php?f=28&t=2295&p=13730#p13730
//ref https://forum.arduino.cc/index.php?topic=411802.0

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//setting vars
WiFiUDP port;
char packetBuffer[255];
unsigned int localPort = 8080;
int clientNumber;
int client1Msg;
int client2Msg;
int client3Msg;
int command[3];

//setting wifi params
const char *ssid = "smart_wifi";
const char *password = "honolulu";

IPAddress IPClient1(192,168,4,100);            //IP address allocated to client1 PIR
IPAddress IPClient2(192,168,4,101);            //IP address allocated to client2 SONAR
IPAddress IPClient3(192,168,4,102);            //IP address allocated to client3 LED
IPAddress local_IP(192,168,4,1);               //AP IP address
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

//pir delay control
bool delayRun = false;
unsigned long delayStart = 0;

//talking to raspi
#include <SoftwareSerial.h>
String rec_msg;
SoftwareSerial mySerial(D2,D3); //rx,tx

//LED
int LED = 0;

void setup()
{
   mySerial.begin(9600);
  //wi-fi setup
  Serial.begin(9600);
  delay(2000);
  Serial.println("MCU_server");    //prints filename
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.mode(WIFI_AP);                                    // to force connection only as AP (access point)
  delay(1000);
  port.begin(localPort);
  Serial.print("Connecting to WiFi.localIP ");
  Serial.print(WiFi.localIP());                          //0.0.0.0
  Serial.print("\tWiFi.softAPIP ");
  Serial.println(WiFi.softAPIP());                       //192.168.4.1
}

void loop()
{
   int packetSize = port.parsePacket();                   //reads packetSize form client
   Serial.print("Received from client(IP/Size/Data):\t ");
   Serial.print(port.remoteIP());                         //reads & prints client IP address
   Serial.print(" / ");
   Serial.print(packetSize);                             //reads & prints packetSize
   Serial.print(" / ");
    
 if (packetSize)                             //if Data available from client
  {
    int len = port.read(packetBuffer, 255);  //read client packetBuffer Data
    if (len > 0) packetBuffer[len-1] = 0;
    Serial.print(packetBuffer);              //prints client packetBuffer Data

    if (port.remoteIP() == IPClient1)        //IP address = 192,168,4,2
    {
      clientNumber = 1;
      Serial.print("\ndata received from client");
      Serial.println(clientNumber);
      Serial.print("packetBuffer1 = ");
      Serial.println(packetBuffer);
    
//stores data from client packetBuffer char array in command int array reading for conversion to integer   
      command[1] = packetBuffer[0];
      command[2] = packetBuffer[1];
      command[3] = '\0';

//conversion of packetBuffer data from char to integer
      client1Msg = atoi(packetBuffer);
      Serial.print("integer client1Msg = ");
      Serial.println(client1Msg);
  //=============reply msg sending============
      port.beginPacket(port.remoteIP(),port.remotePort());
      port.write("Your UDP packet was received OK\r\n");   //write this AP packetBuffer to client (packet size = 33 out of 255)
      port.endPacket();
    }
    
    if (port.remoteIP() == IPClient2)        //IP address = 192,168,4,3
    {
      clientNumber = 2;
      Serial.print("\ndata received from client");
      Serial.println(clientNumber);
      Serial.print("packetBuffer2 = ");
      Serial.println(packetBuffer);

      command[1] = packetBuffer[0];
      command[2] = packetBuffer[1];
      command[3] = '\0';
      
      client2Msg = atoi(packetBuffer);
      Serial.print("integer client2Msg = ");
      Serial.println(client2Msg);

      //=============reply msg sending============
      port.beginPacket(port.remoteIP(),port.remotePort());
      port.write("Your UDP packet was received OK\r\n");   //write this AP packetBuffer to client (packet size = 33 out of 255)
      port.endPacket();
    }
   
     if (port.remoteIP() == IPClient3)       //IP address = 192,168,4,4
    {
      clientNumber = 3;
      Serial.print("\ndata received from client");
      Serial.println(clientNumber);
      Serial.print("packetBuffer3");
      Serial.println(packetBuffer);

      command[1] = packetBuffer[0];
      command[2] = packetBuffer[1];
      command[3] = '\0';
      
      client3Msg = atoi(packetBuffer);
      Serial.print("integer client3Msg = ");
      Serial.println(client3Msg);
  //=============reply msg sending============
      port.beginPacket(port.remoteIP(),port.remotePort());
      char LEDmsg[1];
      sprintf(LEDmsg,"%d",LED);
      port.write(LEDmsg);   //write this AP packetBuffer to client (packet size = 33 out of 255)
      port.write("\r\n");
      port.endPacket();
    }
    
//Serial testing enviroment
//if (Serial.available()>0){
//  rec_msg = Serial.readStringUntil('\n');
//  
//  if (rec_msg == "21" or rec_msg == "20"){
//    client2Msg = rec_msg.toInt();
//    Serial.println("command overrided");
//  }
//  
//  if (rec_msg == "11" or rec_msg == "10"){
//    client1Msg = rec_msg.toInt();
//    Serial.println("command overrided");
//  }
//}

//set LED message with delay of 30s when first got 11
if ((delayRun == false) && (client1Msg == 11)){
  delayRun = true;
  delayStart = millis();
}

if ((millis()-delayStart)>= 30000){
  delayRun = false;
}

if (delayRun == true){
  LED = 1;
}

if (delayRun == false){
  LED = 0;
}
Serial.println(delayRun);

//SONAR inverter
if ((client2Msg == 21) && (delayRun == false)){
  LED = 1;
}
if (client2Msg == 21){
  delayRun = false;
}

//TALKING TO RASPI
if (Serial.available()>0){
   mySerial.print(Serial.readStringUntil('\n'));
}
if (mySerial.available()>0){
   rec_msg = mySerial.readStringUntil('\n');
   Serial.println("RECEIVED RASPI MSG  ---->");
   Serial.print(rec_msg);
}
  }
  
  Serial.println("");
  delay(100);
 
  Serial.print("AP local IP up with: ");
  Serial.print(WiFi.localIP());                          //0.0.0.0
  Serial.print("\tWiFi.softAPIP ");
  Serial.println(WiFi.softAPIP());                       //192.168.4.1
  Serial.println("");
 
}
//- See more at: http://www.esp8266.com/viewtopic.php?f=29&t=4006#sthash.JrbgCVdt.Q4ILiGvV.dpuf
