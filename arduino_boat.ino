// Arduino Boat 07/01/2024

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define INCLUDE_TERMINAL_MODULE

#define DHTTYPE DHT11  // DHT11 Sensor

#include <Dabble.h>  // Dabble Library

// Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 5                   // Arduino pin connect to DHT Sensor
DHT_Unified dht(DHTPIN, DHTTYPE);  // DHT Sensor config
uint32_t delayMS;                  // Variable for delay

boolean interruptorAtivo = false;
bool wasLeftPressed, wasRightPressed, wasDownPressed, wasUpPressed;

void displayHardwareDetails() {  // Show hardware details in Serial Monitor
  Serial.println();
  Serial.println("Inicializando...");
  delay(500);
  Serial.println();
  dht.begin();  // Start the function (DHT11)
  Serial.println("Usando o Sensor DHT");
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);  // Print DHT11 details - temperature
  Serial.println("------------------------------------");
  Serial.println("Temperatura");
  Serial.print("Sensor:       ");
  Serial.println(sensor.name);
  Serial.print("Valor max:    ");
  Serial.print(sensor.max_value);
  Serial.println(" *C");
  Serial.print("Valor min:    ");
  Serial.print(sensor.min_value);
  Serial.println(" *C");
  Serial.print("Resolucao:   ");
  Serial.print(sensor.resolution);
  Serial.println(" *C");
  Serial.println("------------------------------------");
  dht.humidity().getSensor(&sensor);  // Print DHT11 details - humidity
  Serial.println("------------------------------------");
  Serial.println("Umidade");
  Serial.print("Sensor:       ");
  Serial.println(sensor.name);
  Serial.print("Valor max:    ");
  Serial.print(sensor.max_value);
  Serial.println("%");
  Serial.print("Valor min:    ");
  Serial.print(sensor.min_value);
  Serial.println("%");
  Serial.print("Resolucao:   ");
  Serial.print(sensor.resolution);
  Serial.println("%");
  Serial.println("------------------------------------");
  delayMS = sensor.min_delay / 100;  // delay between readings
}

void setup() {  // Dabble config (Bluetooth BLE)
  Serial.begin(9600);
  Dabble.begin(9600);  // PIN2 - TX | PIN3 - RX
  pinMode(9, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  displayHardwareDetails();
}

// Motor: [ [pin-4]Foward B-1A ] -- [ [pin-5]Reverse B-1B ] -- [ [pin-6]Foward A-1A ] -- [ [pin-7]Reverse A-1B ]

void loop() {
  Dabble.processInput();  // Dabble gamepad
  //  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed()) {
    wasUpPressed = true;
    //    Serial.print("UP");
    digitalWrite(4, HIGH);
    digitalWrite(6, HIGH);
  } else if (wasUpPressed == true) {
    wasUpPressed = false;
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
  }

  if (GamePad.isDownPressed()) {
    wasDownPressed = true;
    //    Serial.print("DOWN");
    digitalWrite(5, HIGH);
    digitalWrite(7, HIGH);
  } else if (wasDownPressed == true) {
    wasDownPressed = false;
    digitalWrite(5, LOW);
    digitalWrite(7, LOW);
  }

  if (GamePad.isLeftPressed()) {
    wasLeftPressed = true;  // remember button was pressed
    // Serial.print("Left");
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
  } else if (wasLeftPressed == true) {  // here when button is no longer pressed
    wasLeftPressed = false;
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }

  if (GamePad.isRightPressed()) {
    wasRightPressed = true;
    // Serial.print("Right");
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
  } else if (wasRightPressed == true) {
    wasRightPressed = false;
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
  }



  if (GamePad.isSquarePressed()) {
    // Serial.print("Square");
  }


  if (GamePad.isCirclePressed()) {
    // Serial.print("Circle");
  }


  if (GamePad.isCrossPressed()) {
    // Serial.print("Cross");
  }


  if (GamePad.isTrianglePressed()) {
    // Serial.print("Triangle");
  }


  if (GamePad.isStartPressed()) {
    // Serial.print("Start");
  }



  if (GamePad.isSelectPressed())  // Blue LED
  {
    //    Serial.print("Select");
    interruptorAtivo = !interruptorAtivo;
    digitalWrite(9, interruptorAtivo ? HIGH : LOW);
  }
  //  Serial.print('\t');

  delay(delayMS);                      // atraso entre as medições
  sensors_event_t event;               // inicializa o evento da Temperatura
  dht.temperature().getEvent(&event);  // faz a leitura da Temperatura
  if (isnan(event.temperature))        // se algum erro na leitura
  {
    Serial.println("Erro na leitura da Temperatura!");
  } else  // senão
  {
    Serial.print("Temperatura: ");  // imprime a Temperatura
    Serial.print(event.temperature);
    Serial.println(" *C");
    Terminal.print("Temeperatura: ");
  }
  dht.humidity().getEvent(&event);     // faz a leitura de umidade
  if (isnan(event.relative_humidity))  // se algum erro na leitura
  {
    Serial.println("Erro na leitura da Umidade!");
  } else  // senão
  {
    Serial.print("Umidade: ");  // imprime a Umidade
    Serial.print(event.relative_humidity);
    Serial.println("%");
  }
}
