#define M1PWM 9
#define M1A 12
#define M2PWM 10
#define M2A 11
#define LED1 2
#define LED2 7
#define M1E 8
#define M2E 13

#include "Timer.h"

char Buffer[2] = {0, 0}; // Buffer[0] : Adelante, Buffer[1] : Giro.
byte baseSpeed = 175;
int timerID = 0;
byte balFlag = 0;
byte lightsOn = 0;
Timer t;

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, 0);
  digitalWrite(LED2, 0);
  timerID = t.every(1000, blinkLights);

  delay(500);

  MotoresInit(M1A, M2A, M1E, M2E);
  Serial.begin(9600);
  ApagarMotores(M1PWM, M1A, M2PWM, M2A);
}

void loop()
{
  t.update();
  if ( Serial.available() > 0 )
  {
    Serial.readBytes(&Buffer[0], 1);
    //Serial.flush();

    switch (Buffer[0])
    {
      case 'F':
        MoverMotores(M1PWM, M1A, M2PWM, M2A, baseSpeed, baseSpeed);
        break;

      case 'B':
        MoverMotores(M1PWM, M1A, M2PWM, M2A, -baseSpeed, -baseSpeed);
        break;

      case 'L':
        MoverMotores(M1PWM, M1A, M2PWM, M2A, baseSpeed, -baseSpeed);
        break;

      case 'R':
        MoverMotores(M1PWM, M1A, M2PWM, M2A, -baseSpeed, baseSpeed);
        break;

      case 'G': /*Forward left*/
        MoverMotores(M1PWM, M1A, M2PWM, M2A, 1.2 * baseSpeed, 0.5 * baseSpeed);
        break;

      case 'I': /*  Forward Right */
        MoverMotores(M1PWM, M1A, M2PWM, M2A, 0.5 * baseSpeed, 1.2 * baseSpeed);
        break;

      case 'H': /*  Back Left  */
        MoverMotores(M1PWM, M1A, M2PWM, M2A, -1.2 * baseSpeed, -0.5 * baseSpeed);
        break;

      case 'J':  /* Back Right  */
        MoverMotores(M1PWM, M1A, M2PWM, M2A, -0.5 * baseSpeed, -1.2 * baseSpeed);
        break;

      case 'W': /* Leds on */
        digitalWrite(LED1, 1);
        digitalWrite(LED2, 1);
        lightsOn = 1;
        break;

      case 'w': /* Leds off */
        digitalWrite(LED1, 0);
        digitalWrite(LED2, 0);
        lightsOn = 0;
        break;

      case 'X': /* Balizas  */
        balFlag = 1;
        break;

      case 'x': /* Balizas off */
        balFlag = 0;
        if (!lightsOn)
        {
          digitalWrite(LED1, 0);
          digitalWrite(LED2, 0);
        }
        break;

      case '0':
        baseSpeed = 100;
        t.stop(timerID);
        timerID = t.every(1000, blinkLights);
        break;

      case '1':
        baseSpeed = 110;
        t.stop(timerID);
        timerID = t.every(900, blinkLights);
        break;

      case '2':
        baseSpeed = 120;
        t.stop(timerID);
        timerID = t.every(800, blinkLights);
        break;

      case '3':
        baseSpeed = 130;
        t.stop(timerID);
        timerID =  t.every(700, blinkLights);

        break;

      case '4':
        baseSpeed = 140;
        t.stop(timerID);
        timerID = t.every(600, blinkLights);

        break;


      case '5':
        baseSpeed = 150;
        t.stop(timerID);
        timerID = t.every(500, blinkLights);

        break;

      case '6':
        baseSpeed = 160;
        t.stop(timerID);
        timerID = t.every(400, blinkLights);

        break;

      case '7':
        baseSpeed = 170;
        t.stop(timerID);
        timerID = t.every(300, blinkLights);

        break;

      case '8':
        baseSpeed = 180;
        t.stop(timerID);
        timerID = t.every(200, blinkLights);

        break;

      case '9':
        baseSpeed = 200;
        t.stop(timerID);
        timerID = t.every(100, blinkLights);
        break;

      case 'S':
      default:
        ApagarMotores(M1PWM, M1A, M2PWM, M2A);
        break;
    }
  }
}


/*---------------------------------------------------------------------------------
   Timer Balizas
  ----------------------------------------------------------------------------------*/
void blinkLights()
{
  if (balFlag && !lightsOn)
  {
    if (digitalRead(LED1))
    {
      digitalWrite(LED1, 0);
      digitalWrite(LED2, 0);
    } else {
      digitalWrite(LED1, 1);
      digitalWrite(LED2, 1);
    }
  }
}


/*----------------------------------------------------------------------------------
    Función para inicializar los Motores
  ----------------------------------------------------------------------------------*/

void MotoresInit(byte motor1D, byte motor2D, byte motor1E, byte motor2E)
{
  pinMode(motor1D, OUTPUT);
  pinMode(motor2D, OUTPUT);
  pinMode(motor2E, OUTPUT);
  pinMode(motor2E, OUTPUT);
  digitalWrite(motor2E, 1);
  digitalWrite(motor2E, 1);
}

/*----------------------------------------------------------------------------------
    Función para apagar los Motores con valores absolutos VelM1/2 : (-255; 255)
  ----------------------------------------------------------------------------------*/

void MoverMotores (byte motor1PWM, byte motor1D, byte motor2PWM, byte motor2D, int velocidadMotor1, int velocidadMotor2)
{
  if (velocidadMotor1 > 0)
  {
    analogWrite(motor1PWM, velocidadMotor1);
    digitalWrite(motor1D, 0);
  } else {
    analogWrite(motor1PWM, 255 + velocidadMotor1);
    digitalWrite(motor1D, 1);
  }

  if (velocidadMotor2 > 0)
  {
    analogWrite(motor2PWM, velocidadMotor2);
    analogWrite(motor2D, 0);
  } else  {
    analogWrite(motor2PWM, 255 + velocidadMotor2);
    digitalWrite(motor2D, 1);
  }
}

/*-------------------------------------------------------------
    Función para apagar los Motores
  -------------------------------------------------------------*/
void ApagarMotores(byte motor1PWM, byte motor1D, byte motor2PWM, byte motor2D)
{
  analogWrite(motor1PWM, 255);
  analogWrite(motor2PWM, 255);
  digitalWrite(motor1D, 1);
  digitalWrite(motor2D, 1);
}
