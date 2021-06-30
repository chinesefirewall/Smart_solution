/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-class.rst
 *       https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-examples.rst
 *       https://github.com/esp8266/Arduino/issues/504
 *  Works with: station_bare_01.ino
 */ 


#include <ESP8266WiFi.h>

String inString,outString;

//WiFiServer server(80);
IPAddress IP(192,168,4,1);
IPAddress mask = (255, 255, 255, 0);

char ssid[] = "Wemos_AP_rebriks";           // SSID of your AP
char pass[] = "rebriks_sheesh";         // password of your AP

WiFiServer server(80);

//byte ledPin = 2;

WiFiClient *clients[3]={NULL};
int i,count1,count2;


String led_status, switch_status, mov_status;

void setup() {
  Serial.begin(115200);
  Serial.println();
//  Serial.printf("== connecting to %s ==",ssid);

//  WiFi.mode(WIFI_STA);
//  WiFi.begin(ssid, pass);           // connects to the WiFi AP

//  while (WiFi.status() != WL_CONNECTED) {
//    Serial.print(".");
//    delay(500);
//  }

//  Serial.println();
//  Serial.println("== Connected ==");
//  Serial.println("== station-server.ino ==");
//  Serial.print("== LocalIP:"); Serial.println(WiFi.localIP());
//  Serial.println("== MAC:" + WiFi.macAddress());
//  Serial.print("== Gateway:"); Serial.println(WiFi.gatewayIP());
//  Serial.print("== AP MAC:"); Serial.println(WiFi.BSSIDstr());

 
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
//  pinMode(ledPin, OUTPUT);
//  Serial.println();
//  Serial.println("accesspoint_bare/_01.ino");
  Serial.println("Server started.");
  Serial.print("AP IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("AP MAC:");     Serial.println(WiFi.softAPmacAddress());
}

void loop() {
  
  WiFiClient newClient = server.available();
//  if (!client) {return;}
//  digitalWrite(ledPin, LOW);
  if(newClient) {
    Serial.print("== new client connected with IP: ");
    Serial.println(newClient.remoteIP());

    for(i=0;i<3;i++) {
      if(NULL == clients[i]) {
        clients[i]=new WiFiClient(newClient);
        break;
      }
    }
  }
  for(i=0;i<3;i++) {
    if(NULL != clients[i]) {
      if(clients[i]->connected()) {
        if(clients[i]->available()) {
          delay(500);
          inString = "";
          while(clients[i]->available()) {
            char c=clients[i]->read();
            inString+=c;
            delay(2);
            
          }
          Serial.print("message: " + inString);
          /*
          if (inString.startsWith("led_")){
            led_status = inString;
          } else if (inString.startsWith("mov_")) {
            mov_status = inString;
          } else if (inString.startsWith("switch_")) {
            switch_status = inString;
          }

          if (inString.startsWith("led") && mov_status == "mov_true") {
            clients[i]->println("led_on");
          }

          
          //Serial.println("client:" + clients[i]->remoteIP());
          if(inString.toInt()>0)
            count1=inString.toInt();
          if(inString.toInt()<0)
            count2=inString.toInt();
          if(inString=="LED")
          {
            clients[i]->print(String(count1)+" "+String(count2));
          }
          */
        }
        if(Serial.available()) {
          outString=Serial.readString();
          clients[i]->print(outString);
          Serial.println("== local: "+outString);
//  digitalWrite(ledPin, HIGH);
          }
      }
      
      else
      {
        clients[i]->stop();
        delete clients[i];
        clients[i]=NULL;
        Serial.println("== client lost ==");
      }
      
    }
  }
}
