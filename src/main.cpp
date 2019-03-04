#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiType.h>

#define RELAY 0 
#define HEAD "HTTP/1.1 200 OK \r\n Content-Type: text/other \r\n"

// #define LED_BUILTIN 2
// #define BUILTIN_LED 2

uint8_t favicon[] ={0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x10, 0x10, 0x00, 0x01, 0x00, 0x04, 0x00, 0x28, 0x01, 
                    0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 
                    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0xFF, 
                    0x00, 0x00, 0x11, 0x00, 0xFF, 0x00, 0xFF, 0x84, 0x00, 0x00, 0x6C, 0xB2, 0xEB, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 
                    0x22, 0x23, 0x32, 0x22, 0x22, 0x00, 0x02, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x20, 0x02, 0x33, 
                    0x33, 0x33, 0x33, 0x33, 0x33, 0x20, 0x02, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x20, 0x00, 0x22, 
                    0x22, 0x23, 0x32, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x23, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x23, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x23, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x23, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x02, 0x23, 0x33, 0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x33, 0x33, 0x20, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x21, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


void printScans(int networksFound)
{
    Serial.printf("%d networks found\n\n", networksFound);
    for(int i = 0; i < networksFound; i++)
    {
        Serial.printf("%d: %s, Ch:%d (%ddBm) %s\n", i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i) == ENC_TYPE_NONE ? "open" : "");
    }

}

String prepareHTML(int val)
{
    String page = String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            "SUCC" +
            "</html>" +
            "\r\n";
    return page;
}

String sendFavicon()
{
        String page = String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: image/x-icon\r\n" +
            "Connection: close\r\n" ;  // the connection will be closed after completion of the response
            

    return page;
}


String get13()
{
        String page = String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            "Value of Pin13 is" + digitalRead(13) +
            "</html>" +
            "\r\n";
    return page;
}

const char* ssid = "Obi-LAN Kenobi";
const char* password = "woollymammoth";

WiFiServer server(80);

IPAddress staticIP(10, 0, 0, 6);
IPAddress gateway(10,0,0,1);
IPAddress subnetMask(255, 255, 255, 0);

unsigned char stateVar;


void retState(WiFiClient &client)
{
    if(!client.available())
    {
        return;
    }
    else
    {
        if(stateVar == LOW)
        {
            client.println(HEAD);
            client.println("ON");
            Serial.println("RELAY=OFF");
        }
        else
        {
            client.println(HEAD);
            client.println("OFF");
            Serial.println("RELAY=ON");
        }
    }
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);

    pinMode(RELAY,OUTPUT);
    stateVar = LOW;
    digitalWrite(RELAY, LOW);

    delay(2000);
    Serial.printf("Connecting to %s", ssid);

    
    WiFi.mode((WiFiMode_t)(1));
    WiFi.setOutputPower(0.0f);
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    WiFi.config(staticIP, gateway, subnetMask);
    Serial.println(" connected");

    WiFi.printDiag(Serial);

    server.begin();
    Serial.printf("Web started, go to %s \n", WiFi.localIP().toString().c_str());
   
}   



void loop() {
    // put your main code here, to run repeatedly:
    WiFiClient client = server.available();
    if(!client)
    {
        return;
    }
        Serial.printf("Client Connected from %s \n", client.remoteIP().toString().c_str());
    
    String line = client.readStringUntil('\r');
    Serial.println(line);
    client.flush();

    int val = 0;
    if(line.indexOf("/favicon.ico") != -1)
    {
        Serial.println("Sending favicon");
        client.println(sendFavicon());
        client.write(favicon,318 );
        client.println("\r\n");
        delay(1);
        client.stop();
        Serial.println("Client Disconnected");
        return;
    }  
    else if (line.indexOf("/RELAY=ON") != -1)  
    {
        stateVar = LOW;
        digitalWrite(RELAY,LOW);
        retState(client);
    }
    else if (line.indexOf("/RELAY=OFF") != -1)  
    {
        stateVar = HIGH;
        digitalWrite(RELAY,HIGH);
        retState(client);
    }
    else if (line.indexOf("/RELAYGET") != -1)  
    {
        retState(client);
    }
    else
    {
        client.println(prepareHTML(1));
    }


    delay(10);

    client.stop();
    Serial.println("Client Disconnected");

}