#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#define INCLUDE_TERMINAL_MODULE
#include <Dabble.h>

boolean interruptorAtivo = false;

// Dabble config

void setup() {
  Serial.begin(9600);
  Dabble.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

// Motor: [ [pin-4]F B-1A ] -- [ [pin-5]Reverse B-1B ] -- [ [pin-6]F A-1A ] -- [ [pin-7]Reverse A-1B ]

void loop() {
  Dabble.processInput(); 
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.print("UP");
  }

  if (GamePad.isDownPressed())
  {
    Serial.print("DOWN");
  }

  if (GamePad.isLeftPressed())
  {
    Serial.print("Left");
  }

  if (GamePad.isRightPressed())
  {
    Serial.print("Right");
  }

  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
  } else{
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);

  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");
    digitalWrite(4, HIGH);
    digitalWrite(7, HIGH);
  } else{
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
  }

  if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");
    digitalWrite(5, HIGH);
    digitalWrite(7, HIGH);
  } else{
    digitalWrite(5, LOW);
    digitalWrite(7, LOW);
  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");
    digitalWrite(4, HIGH);
    digitalWrite(6, HIGH);
  } else{
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
  }

  if (GamePad.isStartPressed())
  {
    Serial.print("Start");
  }

  if (GamePad.isSelectPressed()) // Blue LED
  {
    Serial.print("Select");
    interruptorAtivo = !interruptorAtivo;
    digitalWrite(9, interruptorAtivo ? HIGH : LOW);
  }
  Serial.print('\t');

  int a = GamePad.getAngle();
  Serial.print("Angle: ");
  Serial.print(a);
  Serial.print('\t');
  int b = GamePad.getRadius();
  Serial.print("Radius: ");
  Serial.print(b);
  Serial.print('\t');
  float c = GamePad.getXaxisData();
  Serial.print("x_axis: ");
  Serial.print(c);
  Serial.print('\t');
  float d = GamePad.getYaxisData();
  Serial.print("y_axis: ");
  Serial.println(d);
  Serial.println();

}
