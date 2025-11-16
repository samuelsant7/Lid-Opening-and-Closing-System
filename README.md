# Sistema de Abertura Automática de Tampa

Este repositório documenta um projeto desenvolvido para a disciplina de **Programação de Ambientes Embarcados**, cujo objetivo foi criar um sistema automático de abertura de porta/tampa utilizando **ESP8266 (NodeMCU)**, **sensor ultrassônico HC-SR04** e **servo motor SG90**, com controle adicional via **interface Wi-Fi**.

> **Status do projeto:** Código-fonte será adicionado em breve. Toda a documentação estrutural já está disponível.

---

## 📌 Objetivo do Projeto

Criar um sistema embarcado capaz de:

* Detectar aproximação utilizando sensor ultrassônico.
* Abrir automaticamente uma tampa/portinhola quando o usuário estiver a uma distância configurada.
* Permitir controle manual via interface Wi-Fi local (rede criada pelo ESP8266).
* Acionar o servo motor de forma segura e suave.

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

### **Segurança do Sistema**

* Se algo estiver muito perto, o servo **não fecha**, mesmo se o comando Wi-Fi for acionado.

*(Lógica completa será inserida quando o código for localizado)*

---

## 📸 Fotos do Protótipo

As imagens abaixo mostram o hardware real montado em protoboard:

![Foto 1](imagens/foto1.png)
![Foto 2](imagens/foto2.png)
![Foto 3](imagens/foto3.png)

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

## 🗂 Estrutura do Repositório

```
📦 projeto-embarcados-tampa-automatica
├── README.md
├── src/
│   └── codigo-final.ino (a ser adicionado)
└── docs/
    ├── arquitetura.md
    ├── hardware.md
    ├── funcionamento.md
    ├── fluxograma.png
    └── imagens/
        ├── foto1.png
        ├── foto2.png
        └── foto3.png
```

---

## 📑 Documentação Completa

A documentação técnica está organizada na pasta `/docs`:

### **arquitetura.md**

Descrição dos módulos, fluxos de entrada e saída, e lógica geral do sistema.

### **hardware.md**

* Diagrama de ligação (pinos do ESP → servo e ultrassônico)
* Tensão utilizada
* Justificativa dos sensores e atuadores escolhidos

### **funcionamento.md**

Explica:

* Processo de leitura do HC-SR04
* Cálculo de distância
* Controle PWM do servo
* Lógica de abertura automática
* Lógica da interface Wi-Fi

### **fluxograma.png**

Fluxo completo do sistema (sensor → decisão → servo → Wi-Fi).

---

## 🧩 Próximos Passos

* [ ] Inserir o código-fonte (*.ino*)
* [ ] Comentar todas as funções e variáveis
* [ ] Inserir diagrama de ligações elétricas
* [ ] Inserir vídeo de demonstração

---

## 📝 Licença

Este projeto é apenas para fins acadêmicos.

---

## 📬 Contato

Caso tenha dúvidas, melhorias ou sugestões, entre em contato pelo próprio GitHub ou abra uma *issue*.
