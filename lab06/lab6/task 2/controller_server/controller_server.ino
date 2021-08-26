// Ref : http://www.esp8266.com/viewtopic.php?f=28&t=2295&p=13730#p13730
//ref https://forum.arduino.cc/index.php?topic=411802.0

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//setting vars
WiFiUDP port;
char packetBuffer[255];
unsigned int localPort = 8080;
int client_number;
int first_client_msg;
int second_client_msg;
int third_client_msg;
int line_command[3];

//setting wifi params
const char *ssid = "smart_solution";
const char *password = "password";

IPAddress IPClient1(192,168,4,100);            //IP address allocated to client1 PIR
IPAddress IPClient2(192,168,4,101);            //IP address allocated to client2 SONAR
IPAddress IPClient3(192,168,4,102);            //IP address allocated to client3 LED
IPAddress local_IP(192,168,4,1);               //AP IP address
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

//pir delay control
bool delay_run = false;
bool ledStatus = false;
bool was_on = false;
bool start_count = false;
unsigned long counter;

unsigned long delayStart = 0;

//talking to raspi
#include <SoftwareSerial.h>
String received_msg;
SoftwareSerial mySerial(D2,D3); //rx,tx

//LED
int LED = 0;

void setup()
{
   mySerial.begin(9600);
  //wi-fi setup
  Serial.begin(9600);
  delay(2000);
  Serial.println("AP_server");    //prints filename
  
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
//   Serial.print("Received from client(IP/Size/Data):\t ");
//   Serial.print(port.remoteIP());                         //reads & prints client IP address
//   Serial.print(" / ");
//   Serial.print(packetSize);                             //reads & prints packetSize
//   Serial.print(" / ");
    
 if (packetSize)                             //if Data available from client
  {
    int len = port.read(packetBuffer, 255);  //read client packetBuffer Data
    if (len > 0) packetBuffer[len-1] = 0;
//    Serial.println("PacketBuffer: ");
//    Serial.print(packetBuffer);              //prints client packetBuffer Data

    if (port.remoteIP() == IPClient1)        //IP address = 192,168,4,100
    { 
      second_client_msg = 0;
      client_number = 1;
//      Serial.print("\ndata received from client");
//      Serial.println(client_number);
//      Serial.print("packetBuffer1 = ");
//      Serial.println(packetBuffer);
    
    //stores data from client packetBuffer char array in line_command int array reading for conversion to integer   
      line_command[1] = packetBuffer[0];
      line_command[2] = packetBuffer[1];
      line_command[3] = '\0';

    //conversion of packetBuffer data from char to integer
      first_client_msg = atoi(packetBuffer);
//      Serial.print("integer first_client_msg = ");
//      Serial.println(first_client_msg);
      
    //=============reply msg sending============
      port.beginPacket(port.remoteIP(),port.remotePort());
      port.write("Your UDP packet was received OK\r\n");   //write this AP packetBuffer to client (packet size = 33 out of 255)
      port.endPacket();
    }
    
    if (port.remoteIP() == IPClient2)        //IP address = 192,168,4,101
    {
      client_number = 2;
//      Serial.print("\ndata received from client");
//      Serial.println(client_number);
//      Serial.print("packetBuffer2 = ");
//      Serial.println(packetBuffer);

      line_command[1] = packetBuffer[0];
      line_command[2] = packetBuffer[1];
      line_command[3] = '\0';
      
      second_client_msg = atoi(packetBuffer);
//      Serial.print("integer second_client_msg = ");
//      Serial.println(second_client_msg);

     //=============reply msg sending============
      port.beginPacket(port.remoteIP(),port.remotePort());
      port.write("Your UDP packet was received OK\r\n");   //write this AP packetBuffer to client (packet size = 33 out of 255)
      port.endPacket();
    }
   
     if (port.remoteIP() == IPClient3)       //IP address = 192,168,4,102
    {
      second_client_msg = 0;
      client_number = 3;
//      Serial.print("\ndata received from client");
//      Serial.println(client_number);
//      Serial.print("packetBuffer3");
//      Serial.println(packetBuffer);

      line_command[1] = packetBuffer[0];
      line_command[2] = packetBuffer[1];
      line_command[3] = '\0';
      
      third_client_msg = atoi(packetBuffer);
//      Serial.print("integer third_client_msg = ");
//      Serial.println(third_client_msg);
  //=============reply msg sending============
      port.beginPacket(port.remoteIP(),port.remotePort());
      char led_message[1];
      sprintf(led_message,"%d",LED);
      port.write(led_message);   //write this AP packetBuffer to client (packet size = 33 out of 255)
      port.write("\r\n");
      port.endPacket();
    }
    
//Serial testing enviroment
if (Serial.available()>0){
  received_msg = Serial.readStringUntil('\n');
  
  if (received_msg == "21" or received_msg == "20"){
    second_client_msg = received_msg.toInt();
    Serial.println("line_command overrided");
  }
  
  if (received_msg == "11" or received_msg == "10"){
    first_client_msg = received_msg.toInt();
    Serial.println("line_command overrided");
  }
}

  //set LED message with delay of 30s when first got 11
  if ((delay_run == false) && (first_client_msg == 11)){
    delay_run = true;
    start_count = true;
    LED = 1;
    delayStart = millis();
    Serial.println("Turn on and start counting");
  }

  // starting counting until 30 seconds reached
  if(start_count == true) {
      Serial.println("Counting...");
      
      counter = millis()-delayStart;
      if(counter >= 30000){
          delay_run = false;
          start_count = false;
          Serial.println("Finished counting");
          LED = 0;
        }
    }
  

Serial.println(delay_run);

// SONAR sensor acting as intertor
if (second_client_msg == 21){

  // when the led is controlled by the proximity sensor
  if (LED == 1){
      Serial.println("Switch off");
      LED = 0;
  
    } else { LED = 1;}
}

//TALKING TO RASPI
if (Serial.available()>0){
   mySerial.print(Serial.readStringUntil('\n'));
}
if (mySerial.available()>0){
   received_msg = mySerial.readStringUntil('\n');
   Serial.println("RECEIVED RASPI MSG  ---->");
   Serial.print(received_msg);
}
  }
  
  //Serial.println("");
  delay(100);
 
//  Serial.print("AP local IP up with: ");
//  Serial.print(WiFi.localIP());                          //0.0.0.0
//  Serial.print("\tWiFi.softAPIP ");
//  Serial.println(WiFi.softAPIP());                       //192.168.4.1
//  Serial.println("");
 
}
//- See more at: http://www.esp8266.com/viewtopic.php?f=29&t=4006#sthash.JrbgCVdt.Q4ILiGvV.dpuf
