# Sistema de Abertura Automática de Tampa

Este repositório documenta um projeto desenvolvido para a disciplina de **Programação de Ambientes Embarcados**, cujo objetivo foi criar um sistema automático de abertura de porta/tampa utilizando **ESP8266 (NodeMCU)**, **sensor ultrassônico HC-SR04** e **servo motor SG90**, com controle adicional via **interface Wi-Fi**.


---

## 📌 Objetivo do Projeto

Criar um sistema embarcado capaz de:

* Detectar aproximação utilizando sensor ultrassônico.
* Abrir automaticamente uma tampa/portinhola quando o usuário estiver a uma distância configurada.
* Permitir controle manual via interface Wi-Fi local (rede criada pelo ESP8266).
* Acionar o servo motor de forma segura.

Esse sistema simula o funcionamento real de lixeiras automáticas e portas inteligentes.

---

## 🧠 Como o Sistema Funciona

O projeto combina duas formas de acionamento:

### **1. Abertura Automática (Sensor Ultrassônico)**

* O sensor mede constantemente a distância.
* Quando um objeto/pessoa está abaixo do limite (ex.: 10 cm), o servo abre automaticamente.
* Após alguns segundos sem detecção, o servo fecha.

### **2. Abertura via Wi-Fi**

* O ESP8266 cria um ponto de acesso próprio.
* Ao acessar o endereço *192.168.4.1*, o usuário encontra uma interface com:

  * Estado do servo (aberto/fechado)
  * Distância lida pelo sensor
  * Botão para abrir/fechar manualmente
    
---

## 📸 Fotos do Protótipo

As imagens abaixo mostram o hardware real montado em protoboard:

![servo_3](https://github.com/user-attachments/assets/9351039b-6f3a-4166-98ef-4a702cd8fc2c)
![servo_2](https://github.com/user-attachments/assets/3cbb780d-b900-40bf-8a12-7e40d4cbee69)
![servo_1](https://github.com/user-attachments/assets/7f57429d-8445-44b5-9229-5f286c690f75)

*(As imagens já foram anexadas ao repositório dentro da pasta `/docs/imagens`)*

---

## 🔌 Componentes Utilizados

* ESP8266 NodeMCU
* Sensor Ultrassônico HC-SR04
* Servo Motor SG90
* Jumper wires
* Protoboard
* Cabo USB de alimentação

---

## 📬 Contato

Caso tenha dúvidas, melhorias ou sugestões, entre em contato pelo próprio GitHub ou abra uma *issue*.
