# Arquitetura do Sistema 
## 1. Visão Geral

Descrição da arquitetura do sistema de abertura automática de tampa servo motor e uma interface web embarcada.

O sistema permite dois modos de abertura:

* **Aproximação (sensor ultrassônico)** — quando presente no projeto.
* **Comando via Wi-Fi** — através de uma interface Web simples servida pelo próprio ESP8266.

## 2. Componentes Principais

### 2.1. ESP8266 (NodeMCU)

Responsável por:

* hospedar a rede Wi-Fi
* executar o servidor HTTP
* controlar o servo motor
* processar solicitações (*requests*) enviadas pela página web

### 2.2. Servo Motor

Realiza o movimento mecânico da tampa, abrindo ou fechando conforme ângulo definido (0° para fechado, 90° para aberto).

### 2.3. Interface Web

Interface HTML/CSS básica acessada via navegador. É responsável por enviar comandos para o endpoint `/toggle`.

## 3. Arquitetura de Software

O fluxo principal segue esta estrutura:

### **3.1. Setup**

* Inicializa comunicação serial
* Configura pino do servo
* Inicia modo access-point (`softAP`)
* Cria e inicia servidor HTTP

### **3.2. Loop Principal**

* Aguarda conexão HTTP de um cliente
* Lê a requisição
* Verifica se contém `/toggle`
* Alterna estado do servo de **aberto** para **fechado** ou vice-versa
* Retorna página HTML atualizada

### **3.3. Funções Auxiliares**

#### `abrir()`

Move o servo de 0° → 90° gradualmente

#### `fechar()`

Move o servo de 90° → 0° gradualmente

## 4. Comunicação Wi-Fi

### **Modo Access Point (AP)**

O ESP8266 cria uma rede própria:

```
SSID: ServoESP
Senha: 12345678
IP padrão: 192.168.4.1
```

O cliente conecta diretamente a essa rede.

### **Servidor Web**

Opera na porta **80**. Ao acessar `192.168.4.1`, o usuário recebe a interface. Ao clicar no botão:

* Navegador envia requisição GET para `/toggle`
* ESP processa e aciona o servo
* Página recarrega atualizando o estado atual

## 5. Lógica de Controle

### Estados possíveis:

* **aberto = true** → servo no ângulo 90°
* **aberto = false** → servo no ângulo 0°

### Alternância:

```
Se aberto → fechar()
Se fechado → abrir()
```
---
