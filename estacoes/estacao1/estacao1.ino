#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient wifi_client;
PubSubClient mqtt(wifi_client);

const String SSID = "FIESC_IOT_EDU";
const String PASS = "8120gv08";

const String brokerURL = "test.mosquitto.org";
const int brokerPort = 1883;
const String topic = "churros";

const String brokerUser = "";
const String brokerPass = "";

int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  WiFi.begin(SSID, PASS);
  Serial.println("Conectado no Wifi");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("Conectado com sucesso!");
  mqtt.setServer(brokerURL.c_str(),brokerPort);
  String clientID = "estacao1-";
  clientID += String(random(0xffff),HEX);
  Serial.println("Conectando ao Broker");
  while(mqtt.connect(clientID.c_str()) == 0){
    Serial.print(".");
    delay(200);
  }
  mqtt.subscribe(topic.c_str());
  mqtt.setCallback(callback);
  Serial.println("\nConectado ao broker!");
}
void loop() {
  String mensagem = "";
  if(Serial.available() > 0){
    mensagem = Serial.readStringUntil('\n');
    mensagem = "Laura: " + mensagem;
    mqtt.publish("Andrezao",mensagem.c_str());
  }
  mqtt.loop();
}
void callback(char* topic, byte* payload, unsigned long length){
  String MensagemRecebida = "";
  for (int i = 0; i < length; i++) {
    //Pega cada letra de payload e junta na mensagem
    MensagemRecebida += (char) payload[i];
  }
  Serial.println(MensagemRecebida);
  if (MensagemRecebida.indexOf("acender") != -1){
    digitalWrite(ledPin, HIGH);
  }
}