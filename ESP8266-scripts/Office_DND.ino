#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "Waffle House";
const char* password =  "kap0d45kp7";
const char* mqttServer = "192.168.0.20";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
boolean flag = false;
 
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  //LED is off
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) { 
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.publish("office/dnd", "Hello from ESP8266");
  client.subscribe("office/dnd");
}
//Handle messages from MQTT subscription.
void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for(int i = 0; i<length; i++){
    Serial.print((char)payload[i]);
    }
  flag = !flag; //Switches flag state
  Serial.println();
  Serial.println("----------------------------------");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, password);
  }
  client.loop(); //Call the loop to maintain connection to the server
  if(flag){
      digitalWrite(LED_BUILTIN, LOW);
  } else{
      digitalWrite(LED_BUILTIN, HIGH);
  }
  delay(1);
}

  
