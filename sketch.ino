//Declarando bibliotecas que vamos precisar
#include <LiquidCrystal_I2C.h>  // Biblioteca para LCD I2C
#include <RTClib.h> // Biblioteca para Relógio em Tempo Real
#include <Wire.h>   // Biblioteca para comunicação I2C
#include <EEPROM.h> //Bibli para acessar a EEPROM
#include "DHT.h" //Para acessar o sensor de temp e umidade

#define LOG_OPTION 1     // Opção para ativar a leitura do log
#define UTC_OFFSET -3    // Ajuste de fuso horário para UTC-3

// Configurações do DHT22
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2); // Endereço de acesso: 0x3F ou 0x27
RTC_DS1307 RTC;

// Configurações da EEPROM
const int maxRecords = 100;
//Alterando a recordSize para 10 bytes ao invés de 8
const int recordSize = 10; // Tamanho de cada registro em bytes
int startAddress = 0;
int endAddress = maxRecords * recordSize;
int currentAddress = 0;

int lastLoggedMinute = -1;

// Triggers de temperatura e umidade
float trigger_t_min = 20.0; // Exemplo: valor mínimo de temperatura
float trigger_t_max = 30.0; // Exemplo: valor máximo de temperatura
float trigger_u_min = 30.0; // Exemplo: valor mínimo de umidade
float trigger_u_max = 60.0; // Exemplo: valor máximo de umidade


//Declaração das variavéis dos leds, ldr e buzzer

// Definição dos pinos
const int ldrPin = A0;         // Sensor de luz (LDR)
const int ledVerde = 6;        // LED verde (OK)
const int ledAmarelo = 7;      // LED amarelo (atenção)
const int ledVermelho = 8;     // LED vermelho (alerta)
const int buzzer = 9;          // Buzzer para alerta sonoro

// Tempo de leitura e intervalo entre amostras
const int tempoLeitura = 10000; // Tempo total de leitura: 10 segundos (como o prof solicitou nesse cp)
const int intervaloLeitura = 100; // Intervalo entre leituras (ms)
const int numLeituras = tempoLeitura / intervaloLeitura; // Total de amostras

// --- Custom Chars (Ícones e bandeira) ---
byte flag1[8] = {B00110, B01100, B11000, B10001, B00011, B00110, B01100, B00000};
byte flag2[8] = {B00011, B00110, B01100, B10000, B11001, B10011, B00110, B00000};
byte flag3[8] = {B00000, B00110, B01111, B11100, B01110, B00111, B00011, B00000};
byte iconTemp[8] = {B00100, B01010, B01010, B01010, B01110, B11111, B01110, B00000};
byte iconHum[8]  = {B00100, B00100, B01010, B01010, B10001, B10001, B01110, B00000};
byte iconLuz[8]  = {B00100, B10101, B01110, B11111, B01110, B10101, B00100, B00000};
byte iconClock[8]= {B01110, B10001, B10111, B10101, B10101, B10001, B01110, B00000};


void setup() {
  // Define os pinos dos LEDs e buzzer como saída
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

 lcd.init();   // Inicialização do LCD
 lcd.backlight();  // Ligando o backlight do LCD
// Define ícones no LCD
 lcd.createChar(0, flag1);
 lcd.createChar(1, flag2);
 lcd.createChar(2, flag3);
 lcd.createChar(3, iconTemp);
 lcd.createChar(4, iconHum);
 lcd.createChar(5, iconLuz);
 lcd.createChar(6, iconClock);

  pinMode(LED_BUILTIN, OUTPUT);
  dht.begin();
  Serial.begin(9600);
  RTC.begin();    // Inicialização do Relógio em Tempo Real
  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // RTC.adjust(DateTime(2024, 5, 6, 08, 15, 00));  // Ajustar a data e hora apropriadas uma vez inicialmente, depois comentar
  EEPROM.begin(); 
  animacaoInicial();
  animacaoCarregando();
}


void loop() {

DateTime now = RTC.now();

// Calculando o deslocamento do fuso horário
int offsetSeconds = UTC_OFFSET * 3600; // Convertendo horas para segundos
now = now.unixtime() + offsetSeconds; // Adicionando o deslocamento ao tempo atual

// Convertendo o novo tempo para DateTime
DateTime adjustedTime = DateTime(now);

// Verifica se o minuto atual é diferente do minuto do último registro
if (adjustedTime.minute() != lastLoggedMinute) {
  lastLoggedMinute = adjustedTime.minute();

  if (LOG_OPTION) get_log();

  digitalWrite(LED_BUILTIN, HIGH);   
  delay(1000);                       
  digitalWrite(LED_BUILTIN, LOW);    
   delay(1000);                       

  // Leitura da LDR
  long soma = 0;
  for (int i = 0; i < numLeituras; i++) {
    soma += analogRead(ldrPin);
    delay(intervaloLeitura);
  }

  int mediaLDR = soma / numLeituras;
  int intensidade = map(mediaLDR, 8, 1016, 100, 0); // 0 escuro, 100 claro

  // Leitura dos sensores DHT
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // bools para estados
  bool alerta = false;
  bool atencao = false;
  
  // Verificações dos limites
  if (intensidade >= 75 || temperature > trigger_t_max || temperature < trigger_t_min || humidity > trigger_u_max || humidity < trigger_u_min) {
    alerta = true;
    
  } 
  else if (
    (intensidade >= 65 && intensidade < 75) ||
    (temperature >= trigger_t_min - 1 && temperature <= trigger_t_min + 1) ||
    (temperature >= trigger_t_max - 1 && temperature <= trigger_t_max + 1) ||
    (humidity >= trigger_u_min - 2 && humidity <= trigger_u_min + 2) ||
    (humidity >= trigger_u_max - 2 && humidity <= trigger_u_max + 2)
  ) {
    atencao = true;
  } 
  

lcd.clear();
lcd.setCursor(0, 0);
lcd.write(3); lcd.print(" ");
if (temperature > trigger_t_max || temperature < trigger_t_min) {
  lcd.print("ALERTA ");
} else if (
  (temperature == trigger_t_min - 1 || temperature == trigger_t_min + 1) ||
  (temperature == trigger_t_max - 1 || temperature == trigger_t_max + 1)
) {
  lcd.print("ATENCAO");
} else {
  lcd.print("BOM     ");
}

lcd.setCursor(9, 0);
lcd.write(4); lcd.print(" ");
if (humidity > trigger_u_max || humidity < trigger_u_min) {
  lcd.print("ALERTA ");
} else if (
  (humidity == trigger_u_min - 1 || humidity == trigger_u_min + 1) ||
  (humidity == trigger_u_max - 1 || humidity == trigger_u_max + 1)
) {
  lcd.print("ATENCAO");
} else {
  lcd.print("BOM     ");
}

lcd.setCursor(0, 1);
lcd.write(5); lcd.print(" ");
if (intensidade >= 75) {
  lcd.print("ALERTA ");
} else if (intensidade >= 65 && intensidade < 75) {
  lcd.print("ATENCAO");
} else {
  lcd.print("BOM     ");
}

  
  if (alerta) {
   

    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, LOW);
    noTone(buzzer); // interrompe o som atual
    tone(buzzer, 265, 15000);  // Tom de alerta por 15 segundos

    // Registra o evento
    DateTime now = RTC.now();
    long timestamp = adjustedTime.unixtime();
    int tempInt = (int)(temperature * 100);
    int humiInt = (int)(humidity * 100);
    int luzInt = intensidade;

    EEPROM.put(currentAddress, timestamp);       // 4 bytes
    EEPROM.put(currentAddress + 4, tempInt);     // 2 bytes
    EEPROM.put(currentAddress + 6, humiInt);     // 2 bytes
    EEPROM.put(currentAddress + 8, luzInt);      // 2 bytes
    getNextAddress();                            // atualiza para o próximo registro
  } 
  else if (atencao) {
    
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVerde, LOW);
    tone(buzzer, 265, 3000);  // Tom de alerta por 3 segundos
  } 
  else {
    lcd.setCursor(9, 1);
    lcd.write(6); // ícone "ok" ou relógio, por exemplo
    lcd.print(" ");
  lcd.print(adjustedTime.hour());
  lcd.print(":");
  if (adjustedTime.minute() < 10) lcd.print("0");
  lcd.print(adjustedTime.minute());

    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVerde, HIGH);
    noTone(buzzer);
  }

  delay(2000); // intervalo até próxima leitura
}
}
  

//A função avança 10 bytes
void getNextAddress() {
    currentAddress += recordSize;
    if (currentAddress >= endAddress) {
        currentAddress = 0; // Volta para o começo se atingir o limite
    }
}

void get_log() {
    Serial.println("Registro na EEPROM:");
    Serial.println("Data\t\t\tTemperatura\tUmidade\t\tLuz");

    for (int address = startAddress; address < endAddress; address += recordSize) {
        long timeStamp;
        int tempInt, humiInt, luzInt;

        // Ler dados da EEPROM
        EEPROM.get(address, timeStamp);
        EEPROM.get(address + 4, tempInt);
        EEPROM.get(address + 6, humiInt);
        EEPROM.get(address + 8, luzInt);

        // Converter valores
        float temperature = tempInt / 100.0;
        float humidity = humiInt / 100.0;

        // Verificar se os dados são válidos antes de imprimir
        if (timeStamp != 0xFFFFFFFF) { // 0xFFFFFFFF é o valor padrão de uma EEPROM não inicializada
            DateTime dt = DateTime(timeStamp);
            Serial.print(dt.timestamp(DateTime::TIMESTAMP_FULL));
            Serial.print("\t");
            Serial.print(temperature);
            Serial.print(" C\t\t");
            Serial.print(humidity);
            Serial.println(" %");
            Serial.print(luzInt);
            Serial.println(" %");
        }
    }
}

//Animação inicial 
void animacaoInicial() {
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.write(0); lcd.write(1); lcd.write(2);
 lcd.print(" SmoothPath ");
 lcd.setCursor(0, 1);
 String msg = "Iniciando...";
 for (int i = 0; i < msg.length(); i++) {
   lcd.print(msg[i]);
   delay(150);
 }
 delay(3000);
}

//Barra de carregamento com ícone relógio (diferencial)
void animacaoCarregando() {
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.write(6); lcd.print(" Carregando...");
 lcd.setCursor(0, 1);
 for (int i = 0; i < 16; i++) {
   lcd.print((char)255); // Bloco cheio
   delay(150);
 }
}