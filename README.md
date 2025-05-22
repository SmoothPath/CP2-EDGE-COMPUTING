
🍷 Projeto Arduino: Monitoramento Ambiental para Vinheria

📋 Descrição

Este projeto foi desenvolvido para uma vinheria especializada em vinhos de alto padrão, que exige condições ambientais rigorosas para garantir a conservação da qualidade dos seus produtos.

Nossa solução consiste em um sistema embarcado com Arduino Uno, que monitora a temperatura, umidade e luminosidade do ambiente em tempo real. Os dados são exibidos em um display LCD 16x2 com interface I2C, utilizando ícones personalizados para facilitar a leitura. Quando os valores estão fora dos limites adequados, o sistema emite o Buzzer e ativa o LED correspondente a gravidade da inadequação.


 🎯 Objetivo

Desenvolver uma solução automatizada e acessível para garantir o controle ideal do ambiente de armazenamento dos vinhos, ajudando na preservação de sua qualidade.

 🛠️ Componentes Utilizados

 Arduino Uno R3                    
 Sensor de temperatura e umidade DHT11 ou DHT22
 Sensor de luminosidade (LDR)       
 Display LCD 16x2 com módulo I2C     
 Protoboard e jumpers                
 Fonte de alimentação (USB ou externa)

⚙️ Funcionamento

O Arduino lê os dados dos sensores a cada poucos segundos.
Exibe no LCD:
  - 🌡️ Temperatura
  - 💧 Umidade
  - ☀️ Luminosidade
- Cada variável tem um ícone customizado.
- Se algum valor estiver fora da faixa ideal, são ativados o LED e o Buzzer, de acordo com o estado de inadequação do parâmetro (Atenção ou Alerta)

 🧪 Parâmetros Ideais (Vinheria)

Temperatura = 20°C a 30°C
Umidade = 30% a 60%
Luminosidade = 0% a 64%

 📦 Bibliotecas Utilizadas

Instale estas bibliotecas na IDE Arduino:

- `LiquidCrystal_I2C.h`
- `DHT.h` 
- `RTClib.h`
- `Wire.h`
- `EEPROM.h`

📷 Imagens
![image](https://github.com/user-attachments/assets/0789a32e-14f5-45b4-80dc-123a09d555b1)

 🧠 Aprendizados

- Sensores ambientais com Arduino
- Lógica de comparação de faixas ideais
- Criação de ícones no LCD
- Manipulação do display via I2C
- Alertas visuais e sonoros com `delay()` e `if`

 👥 Equipe SmoothPath

- Geovana Cardoso  
- Lucas Oliveira  
- Gabriel Cardoso  
- Gustavo Torres  
- Mariana Egito  

Turma: 1ESPF  
Professor: Fábio Henrique Cabrini

 💼 Aplicação Real

Este projeto simula um sistema real de controle ambiental para vinherias, mas pode ser adaptado para outros ambientes sensíveis como laboratórios, estufas ou salas técnicas.

