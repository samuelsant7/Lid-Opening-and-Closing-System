#include <ESP8266WiFi.h>
#include <Servo.h>

//Wi-fi
const char* ssid = "ServoESP";       
const char* password = "12345678";   

WiFiServer server(80);

//Servo-motorr
  
Servo servo;
int pos = 0;
bool aberto = false;     // estado da tampa
unsigned long ultimaAbertura = 0;

// Sensor ultrassônico
#define TRIGGER D5
#define ECHO    D6

int distanciaAbertura = 30;

unsigned long tempoFechar = 10000;


void setup() {
  Serial.begin(115200);

  servo.attach(D4);
  servo.write(0);  // posição inicial
  
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  WiFi.softAP(ssid, password);
  server.begin();

  Serial.println();
  Serial.print("Rede criada: ");
  Serial.println(ssid);
  Serial.println("Acesse: http://192.168.4.1");
}


//dist
long medirDistancia() {
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  long duracao = pulseIn(ECHO, HIGH);
  long distancia = duracao * 0.034 / 2; 
  return distancia;
}


void loop() {

  long distancia = medirDistancia();

  if (distancia > 0 && distancia <= distanciaAbertura) {
    if (!aberto) {
      abrir();
      aberto = true;
      ultimaAbertura = millis();
    }
  }

  if (aberto && millis() - ultimaAbertura >= tempoFechar) {
    fechar();
    aberto = false;
  }

  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("/toggle") != -1) {
    if (aberto) fechar();
    else abrir();
    aberto = !aberto;
    ultimaAbertura = millis();
  }

  //pag
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html\n");
  client.println("<!DOCTYPE html><html><head><meta charset='UTF-8'>");
  client.println("<style>");
  client.println("body{font-family:Arial;text-align:center;background:#eef;padding-top:40px;}");
  client.println("button{font-size:22px;padding:12px 26px;border:none;border-radius:10px;background:#007bff;color:white;cursor:pointer;}");
  client.println("button:hover{background:#0056b3;}");
  client.println("</style></head><body>");
  client.println("<h1>Controle da Tampa Automática</h1>");
  client.println("<p>Estado atual: <b>" + String(aberto ? "Aberto" : "Fechado") + "</b></p>");
  client.println("<button onclick=\"location.href='/toggle'\">" + String(aberto ? "Fechar" : "Abrir") + "</button>");
  client.println("<p style='margin-top:20px;'>Distância detectada: " + String(distancia) + " cm</p>");
  client.println("</body></html>");
}


void abrir() {
  Serial.println("Abrindo tampa...");
  for (pos = 0; pos <= 90; pos++) {
    servo.write(pos);
    delay(10);
  }
  Serial.println("Tampa aberta.");
}

void fechar() {
  Serial.println("Fechando tampa...");
  for (pos = 90; pos >= 0; pos--) {
    servo.write(pos);
    delay(10);
  }
  Serial.println("Tampa fechada.");
}
