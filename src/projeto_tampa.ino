#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>

// ====== CONFIGURAÇÃO ======
const char* ssid = "auau";
const char* password = "miau";

// Pinos (ESP32)
const int servoPin = 23;
const int trigPin  = 2;
const int echoPin  = 16;

// Ângulos / limites
const int anguloFechado = 90;
const int anguloAberto  = 0;
const int distanciaLimite = 50; // cm

// Tempos
const unsigned long tempoAbertoMs = 5000; // tempo que a tampa fica aberta ao detectar objeto

// Estado
bool aberta = false;
unsigned long abertaDesde = 0;

long duracao;
int distancia;
int posAtual = anguloFechado;

Servo servo; 
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Servo
  servo.attach(servoPin);
  servo.write(anguloFechado);
  posAtual = anguloFechado;

  // Sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // WiFi AP
  WiFi.softAP(ssid, password);
  server.begin();

  Serial.println();
  Serial.print("AP criado: ");
  Serial.println(ssid);
  Serial.println("Conecte-se e abra 192.168.4.1");
  Serial.println("Simulador iniciado!");
}

void abrirTampa() {
  if (!aberta) {
    abrirAnimado();
    aberta = true;
    abertaDesde = millis();
    Serial.println("Tampa aberta (por sensor/web)");
  }
}

void fecharTampa() {
  if (aberta) {
    fecharAnimado();
    aberta = false;
    Serial.println("Tampa fechada (por sensor/web)");
  }
}

// Anima a abertura (suave)
void abrirAnimado() {
  for (int p = posAtual; p >= anguloAberto; p--) { // decrementa se anguloAberto < anguloFechado
    servo.write(p);
    delay(8);
  }
  posAtual = anguloAberto;
}

// Anima o fechamento (suave)
void fecharAnimado() {
  for (int p = posAtual; p <= anguloFechado; p++) {
    servo.write(p);
    delay(8);
  }
  posAtual = anguloFechado;
}

int medirDistancia() {
  // Trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // pulseIn com timeout (30 ms -> evita bloqueio indefinido)
  duracao = pulseIn(echoPin, HIGH, 30000);
  if (duracao == 0) return -1; // sem eco (out of range)
  distancia = duracao * 0.034 / 2;
  return distancia;
}

void handleClient() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  Serial.print("Request: ");
  Serial.println(request);

  // Rotas: /abrir, /fechar, /toggle
  if (request.indexOf("GET /abrir ") != -1) {
    abrirTampa();
  } else if (request.indexOf("GET /fechar ") != -1) {
    fecharTampa();
  } else if (request.indexOf("GET /toggle ") != -1) {
    if (aberta) fecharTampa();
    else abrirTampa();
  }

  // Resposta HTML
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html; charset=UTF-8");
  client.println("Connection: close");
  client.println("");
  client.println("<!DOCTYPE html><html><head><meta charset='UTF-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  client.println("<title>Controle Servo</title>");
  client.println("<style>");
  client.println("body{font-family:Arial,Helvetica,sans-serif;text-align:center;padding:20px;background:#f4f7fb}");
  client.println("button{font-size:20px;padding:12px 24px;margin:8px;border:none;border-radius:8px;cursor:pointer}");
  client.println(".open{background:#28a745;color:white} .close{background:#dc3545;color:white} .toggle{background:#007bff;color:white}");
  client.println("</style></head><body>");
  client.println("<h1>Controle de Servo via WiFi</h1>");
  client.printf("<p>Estado: <strong>%s</strong></p>\n", (aberta ? "Aberto" : "Fechado"));
  client.printf("<p>Distância atual: <strong>%s cm</strong></p>\n", (distancia>0?String(distancia):String("---")));
  client.println("<p>");
  client.println("<a href='/abrir'><button class='open'>Abrir</button></a>");
  client.println("<a href='/fechar'><button class='close'>Fechar</button></a>");
  client.println("<a href='/toggle'><button class='toggle'>Alternar</button></a>");
  client.println("</p>");
  client.println("<p>Ao detectar objeto a tampa abre automaticamente por 5s.</p>");
  client.println("</body></html>");

  delay(1);
  client.stop();
}

unsigned long ultimaMedida = 0;
const unsigned long intervaloMedida = 300; // ms

void loop() {
  // 1) tratar requisições web a cada iteração
  handleClient();

  // 2) medir distância periodicamente (sem bloquear)
  unsigned long agora = millis();
  if (agora - ultimaMedida >= intervaloMedida) {
    ultimaMedida = agora;
    int d = medirDistancia();
    distancia = d;
    if (d > 0) {
      Serial.print("Distância: ");
      Serial.println(d);
      if (d < distanciaLimite && !aberta) {
        abrirTampa();
      }
    } else {
      // sem leitura válida
      // Serial.println("Sem leitura do sensor");
    }
  }

  // 3) fechar automaticamente após tempoAbertoMs
  if (aberta && (millis() - abertaDesde >= tempoAbertoMs)) {
    fecharTampa();
  }

  // Pequena pausa para economia (e evitar loop frenético)
  delay(10);
}
