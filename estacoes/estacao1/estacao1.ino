#include <Wifi.h>
WifiClient client;
const String SSID = "nome da rede";
const String PASS = "senha da rede";

void setup() {
  Serial.begin(115200);
  client.begin(nome, senha);
  Serial.println("Conectado no Wifi");
  while(cliente.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
