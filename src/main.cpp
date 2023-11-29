#include "html.h"
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <LiquidCrystal_I2C.h>

const char *SSID = "LAMPS WiFi";
const char *PSWD = "asdf1234";

ESP8266WebServer server(80);

String renderizarIndex() {
  String page = indexPageStart;
  page += estadoLed;
  if(digitalRead(LED_BUILTIN) == LOW) {
    page.replace("{s}", "Prendido");
  } else {
    page.replace("{s}", "Apagado");
  }
  page += indexPageEnd;
  return page;
}

void home() { 
  server.send(200, "text/html", renderizarIndex()); 
}

void notFound(){
  server.send(404, "text/plain", "404 - No se encontro");
}

void toggleLed() {
  digitalWrite(LED_BUILTIN, not digitalRead(LED_BUILTIN));
  server.send(200, "text/html", renderizarIndex());
}

void cambiarEstado() {
  if(server.method() == HTTP_POST) {
    String estado = server.arg("estado");
    digitalWrite(LED_BUILTIN, estado == "on" ? LOW : HIGH);
    server.send(200, "text/html", renderizarIndex());
  }
  server.send(503, "text/plain", "503 - Ud. no deberia estar aqui");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Hola desde el ESP8266");
  while (not WiFi.softAP(SSID, PSWD)) {
    Serial.print('.');
  }
  server.on("/", home);
  server.on("/toggle", toggleLed);
  server.on("/cambiar_estado", cambiarEstado);
  server.onNotFound(notFound);
  server.begin();
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
