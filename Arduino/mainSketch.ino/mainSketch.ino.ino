#define M1PWM 9
#define M1A 12
#define M2PWM 11
#define M2A 13
#define LED1 2
#define LED2 7

char Buffer[2] = {0, 0}; // Buffer[0] : Adelante, Buffer[1] : Giro.

void setup()
{
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  digitalWrite(LED1,0);
  digitalWrite(LED2,0);
  MotoresInit(M1A, M2A);
  Serial.begin(9600);
  ApagarMotores(M1PWM, M1A, M2PWM, M2A);
}

void loop()
{
  if (Serial.available() > 0)
  {
    Serial.readBytes(&Buffer[0], 1);

    switch(Buffer[0])
    {
      case 'a':
        digitalWrite(LED1,1);
        digitalWrite(LED2,1);
        MoverMotoresPorcentaje(M1PWM, M1A, M2PWM, M2A, 40, 40);
        break;

      case 'b':
        digitalWrite(LED1,0);
        digitalWrite(LED2,0);
        MoverMotoresPorcentaje(M1PWM, M1A, M2PWM, M2A, -40, -40);
        break;

      case 'c':
        digitalWrite(LED1,1);
        digitalWrite(LED2,0);
        MoverMotoresPorcentaje(M1PWM, M1A, M2PWM, M2A, 40, -40);
        break;

     case 'd':
        digitalWrite(LED1,0);
        digitalWrite(LED2,1);
        MoverMotoresPorcentaje(M1PWM, M1A, M2PWM, M2A, -40, 40);
        break;

     case 'd':
     default:
        digitalWrite(LED1,0);
        digitalWrite(LED2,0);
        ApagarMotores(M1PWM, M1A, M2PWM, M2A);
        break;
    }
    
  }
}

/*----------------------------------------------------------------------------------
 *  Función para inicializar los Motores
 *----------------------------------------------------------------------------------*/

void MotoresInit(byte M1A, byte M2A)
{
  pinMode(M1A,OUTPUT);
  pinMode(M2A,OUTPUT);
}

/*----------------------------------------------------------------------------------
 *  Función para apagar los Motores con valores absolutos VelM1/2 : (-255; 255)
 *----------------------------------------------------------------------------------*/

void MoverMotores (byte M1PWM, byte M1A, byte M2PWM, byte M2A, int VelM1, int VelM2)
{

    if(VelM1 > 0)
    {
        analogWrite(M1PWM,VelM1);
        //digitalWrite(M1A,0);
        analogWrite(M1A,0); 
    }
  else
       {
  analogWrite(M1PWM,255+VelM1);
  //digitalWrite(M1A,1);
        analogWrite(M1A,255); 
  }

    if(VelM2 > 0)
    {
        analogWrite(M2PWM,VelM2);
        analogWrite(M2A,0); 
  }
  else
        {
  analogWrite(M2PWM,255+VelM2);
        analogWrite(M2A,255); 
  }

}

/*-------------------------------------------------------------
 *  Función para mover los Motores a partir de porcentajes
 *-------------------------------------------------------------*/

void MoverMotoresPorcentaje(byte M1PWM, byte M1A, byte M2PWM, byte M2A, int VelM1Por, int VelM2Por)
{
    MoverMotores(M1PWM, M1A, M2PWM, M2A, VelM1Por*2.55, VelM2Por*2.55);
}

/*-------------------------------------------------------------
 *  Función para apagar los Motores
 *-------------------------------------------------------------*/

void ApagarMotores(byte M1PWM, byte M1A, byte M2PWM, byte M2A)
{
      analogWrite(M1PWM,255);
      analogWrite(M2PWM,255);          
      digitalWrite(M1A,1); 
      digitalWrite(M2A,1); 
}
