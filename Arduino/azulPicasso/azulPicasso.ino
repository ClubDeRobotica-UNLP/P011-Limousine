#define M1PWM 9
#define M1A 12
#define M2PWM 10
#define M2A 11
#define LED1 2
#define LED2 7

char Buffer[2] = {0, 0}; // Buffer[0] : Adelante, Buffer[1] : Giro.

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, 0);
  digitalWrite(LED2, 0);

  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(8, 1);
  digitalWrite(13, 1);
  
  delay(500);
  
  MotoresInit(M1A, M2A);
  Serial.begin(9600);
  ApagarMotores(M1PWM, M1A, M2PWM, M2A);  
}

void loop()
{
  Buffer[0] = 0;
  delay(40);
  if (Serial.available() > 0)
  {
    Serial.readBytes(&Buffer[0], 1);
  }
  switch (Buffer[0])
  {
    case 'a':
      digitalWrite(LED1, 1);
      digitalWrite(LED2, 1);
      MoverMotores(M1PWM, M1A, M2PWM, M2A, 200, 200);
      break;

    case 'b':
      digitalWrite(LED1, 0);
      digitalWrite(LED2, 0);
      MoverMotores(M1PWM, M1A, M2PWM, M2A, -200, -200);
      break;

    case 'c':
      digitalWrite(LED1, 1);
      digitalWrite(LED2, 0);
      MoverMotores(M1PWM, M1A, M2PWM, M2A, 200, -100);
      break;

    case 'd':
      digitalWrite(LED1, 0);
      digitalWrite(LED2, 1);
      MoverMotores(M1PWM, M1A, M2PWM, M2A, -100, 200);
      break;

    case 'e':
    default:
      digitalWrite(LED1, 0);
      digitalWrite(LED2, 0);
      ApagarMotores(M1PWM, M1A, M2PWM, M2A);
      break;
  }
}

/*----------------------------------------------------------------------------------
    Función para inicializar los Motores
  ----------------------------------------------------------------------------------*/

void MotoresInit(byte motor1D, byte motor2D)
{
  pinMode(motor1D, OUTPUT);
  pinMode(motor2D, OUTPUT);
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
