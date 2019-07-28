#include <ESP8266WiFi.h>

String apiKey = "YOUR THINGSPEAK API KEY";

const char* ssid = "YOUR SSID";
const char* pass = "YOUR_PASSWORD";
const char* server = "api.thingspeak.com";

int led1=D2;
int led2=D3;
int ir=D1;
int val;
int i=0;
int n=0;

WiFiClient client;


void setup()
{
  Serial.begin(115200);
  pinMode(ir,INPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  delay(10);
  
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
    Serial.println("");
    Serial.println("WiFi connected");
  }
  
}

void inc()
{
  i++;
  while(1)
  {}
}


void loop()
{
  analogWrite(led1,150);
  analogWrite(led2,150);
  val=digitalRead(ir);
  
  
  if(val==HIGH);
  {
    digitalWrite(led1,HIGH);
    digitalWrite(led2,HIGH);
    inc();
  }
  Serial.println(i);

  if (client.connect(server,80))//"184.106.153.149" or api.thingspeak.com
  {
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(i);
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.print("IR: ");
    Serial.print(i); 
    Serial.println("%. Send to Thingspeak.");
  }
  Serial.println("Waiting...");
  delay(15000);

}

