
🍷 Projeto Arduino: Monitoramento Ambiental para Vinheria

📋 Descrição

Este projeto foi desenvolvido para uma vinheria especializada em vinhos de alto padrão, que exige condições ambientais rigorosas para garantir a conservação da qualidade dos seus produtos.

Nossa solução consiste em um sistema embarcado com Arduino Uno, que monitora a temperatura, umidade e luminosidade do ambiente em tempo real. Os dados são exibidos em um display LCD 16x2 com interface I2C, utilizando ícones personalizados para facilitar a leitura. Quando os valores estão fora dos limites adequados, o sistema emite o Buzzer e ativa o LED correspondente a gravidade da inadequação. Além disso, quando os valores estão fora dos limites adequados (estado de ALERTA), a data, horário e os valores numéricos de cada parâmetro são registrados na EEPROM, estes dados podem ser consultados conectando um cabo USB no Arduino e acessando o Serial Monitor. Também, não há problema de memória cheia pois nosso projeto possui um sistema de memória circular, ou seja, quando a memória chega ao seu limite, ela volta para o início.


 🎯 Objetivo

Desenvolver uma solução automatizada e acessível para garantir o controle ideal do ambiente de armazenamento dos vinhos, ajudando na preservação de sua qualidade.

 🛠️ Componentes Utilizados

 Arduino Uno R3                    
 Sensor de temperatura e umidade DHT11 ou DHT22
 Sensor de luminosidade (LDR)       
 Display LCD 16x2 com módulo I2C    
 Módulo RTC
 Protoboard e jumpers                
 Fonte de alimentação (USB ou externa)

⚙️ Funcionamento

O Arduino lê os dados dos sensores a cada poucos segundos.
Exibe no LCD:
  - 🌡️ Temperatura
  - 💧 Umidade
  - ☀️ Luminosidade
- Cada variável tem um ícone customizado.
- Quando todas as variáveis estão na faixa ideal (estado BOM), o LED verde é ativado e também é exibido o horário atual no Display
- Se algum valor estiver fora da faixa ideal, são ativados o LED e o Buzzer, de acordo com o estado de inadequação do parâmetro (ATENÇÃO ou ALERTA)
- Estado ATENÇÃO = LED Amarelo e Buzzer soando por 3 segundos a cada 2 segundos
- Estado ALERTA = LED Vermelho e Buzzer soando por 15 segundos a cada 2 segundos
- Se algum valor estiver em estado de ALERTA, a data, horário e os valores numéricos dos parâmetros do momento são registrados na EEPROM
- Os registros da memória EEPROM são exibidos a cada um minuto via Serial Monitor
- Quando a memória atinge seu limite, ela volta ao início

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
- Lógica de controle
- Criação de ícones no LCD
- Manipulação do display via I2C
- Alertas visuais e sonoros com `delay()` e `if`
- Criação e exibição de ícones e animações personalizadas
- Sistema de data e horário com módulo RTC
- Registro de dados na EEPROM
- Persistência de dados
- EEPROM funcionando como Memória circular (função getNextAddress() no código)
- Acesso e exibição dos dados registrados na EEPROM do Arduino (função get_log() no código)

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

Para replicar este projeto, basta seguir a montagem exibida na imagem, copiar e colar o código (presente no arquivo sketch.ino) no Arduino IDE ou no Wokwi (caso opte pela simulação) e instalar as bibliotecas necessárias (presente no tópico Bibliotecas Utilizadas nesse read.md).

📽️ Demonstrações

 🔌 [Simulação no Wokwi](https://wokwi.com/projects/431513378894330881)  
 ▶️ [Vídeo no YouTube](https://youtu.be/ntugGNwugcQ?si=EWCUDGUSzH9O9Ako)  
 💼 [Aplicação prática via postagem LinkedIn desktop](https://www.linkedin.com/posts/geovana-cardoso-058498355_arduino-fiap-engenharia-activity-7331792706932813824-Exqb?utm_source=share&utm_medium=member_desktop&rcm=ACoAAFiGz0QB2E6qxW78E5OHV1SKHD17FQJnwyo)

Este projeto foi desenvolvido como atividade do CHECKPOINT 2 da disciplina de EDGE COMPUTING AND COMPUTER SYSTEMS do curso de Engenharia de Software - FIAP.

