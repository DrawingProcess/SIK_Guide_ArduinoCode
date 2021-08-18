#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include "ControlMotor.h"


#define MOT_LEFT_FORWARD digitalWrite(MotLeft1,HIGH);digitalWrite(MotLeft2, LOW)
#define MOT_LEFT_REVERSE  digitalWrite(MotLeft1, LOW);digitalWrite(MotLeft2, HIGH)

#define MOT_RIGHT_FORWARD digitalWrite(MotRight1,HIGH);digitalWrite(MotRight2, LOW)
#define MOT_RIGHT_REVERSE  digitalWrite(MotRight1, LOW);digitalWrite(MotRight2, HIGH)


ControlMotor::ControlMotor(int MR1,int MR2,int ML1,int ML2,int PWMR,int PWML)
{
   pinMode(MR1,OUTPUT);  // Configuramos como salida el Enable 1 del Derecho
   pinMode(MR2,OUTPUT);  // Configuramos como salida el Enable 2 del Derecho
   pinMode(ML1,OUTPUT);  // Configuramos como salida el Enable 1 del Izquierdo
   pinMode(ML2,OUTPUT);  // Configuramos como salida el Enable 2 del Izquierdo
   pinMode(PWMR,OUTPUT); // PWM usado para el motor Derecho
   pinMode(PWML,OUTPUT); // PWM usado para el motor Izquierdo

   MotRight1=MR1;  // Almacenamos el pin seleccionado para el motor Derecho Enable 1 en la variable correspondiente para su posterior uso
   MotRight2=MR2;  // Almacenamos el pin seleccionado para el motor Derecho Enable 2 en la variable correspondiente para su posterior uso
   MotLeft1=ML1;  // Almacenamos el pin seleccionado para el motor Izquierdo Enable 1 en la variable correspondiente para su posterior uso
   MotLeft2=ML2;  // Almacenamos el pin seleccionado para el motor Izquierdo Enable 2 en la variable correspondiente para su posterior uso
   pwmR=PWMR;    // Almacenamos el pin seleccionado para el PWM Derecho en la variable correspondiente para su posterior uso  
   pwmL=PWML;    // Almacenamos el pin seleccionado para el PWM Izquierdo en la variable correspondiente para su posterior uso  
}

// Esta función se encarga de calcular la velocidad de los motores según el ángulo que seleccionemos y la velocidad.
void ControlMotor::CalculateSpeed(int speed, int turn, int *vel_left, int *vel_right ){
  
    if( speed < 0 ){speed *= -1;}  // Pasamos a positivo el valor velocidad para hacer los c�lculos
    
    if((turn>=100)||(turn<=-100)){ // Al 100% o al -100% el robot solo gira, por lo que ambas ruedas van al 100% de velocidad
      *vel_left = speed;
      *vel_right = speed;
    }
    else{ // Si no est� al 100% de giro, realizamos los c�lculos
      // Realizamos los c�lculos
      if(turn >= 0){       // El robot retrocede o avanza recto o a la derecha seg�n la variable giro
        turn = 100 - turn; // Invertimos los valores para hacer la regla de 3 ya que 0� el 100% de los motores y 100� es 0% de los motores
        *vel_left = speed; // Como el giro es para la derecha si la variable es mayor que 0, el motor izquierdo va a la vecodidad m�xima que le marquemos
        *vel_right = (turn*speed)/100; // Hacemos una regla de tres y calculamos, si 255(m�xima velocidad) es el 100%(del giro), "variable giro" ser� X
      }
      else{                // El robot avanza recto o a la izquierda seg�n la variable giro
        turn += 100;       // Invertimos los valores y lo pasamos a positivo para hacer la regla de 3 ya que 0� el 100% de los motores y -100� es 0% de los motores
        *vel_right = speed;// Como el giro es para la izquierda si la variable es menor que 0, el motor derecho va a la vecodidad m�xima que le marquemos
        *vel_left = (turn*speed)/100; // Hacemos una regla de tres, pasando el valor de giro a positivo y calculamos, si 255(m�xima velocidad) es el 100%(del giro), "variable giro" ser� X
      }
    }
    
}

// Esta función carga los valores correspondientes en cada motor
void ControlMotor::Motor(int speed, int turn){
  int  vel_left,vel_right;  // Almacenamos las variables una vez procesada para cargarla despu�s a los motores.
   
  //------------------------------- Nos aseguramos que la variable giro no sobrepasa del 100% o del -100% --------------------------------------------//
  if(turn > 100){turn = 100;}
  if(turn < -100){turn = -100;}
  //---------------------------- Nos aseguramos que la variable velocidad no sobrepasa del 255 o del -255 --------------------------------------------//
  if(speed > 255){speed = 255;}
  if(speed < -255){speed = -255;}
  
  CalculateSpeed(speed,turn,&vel_left,&vel_right);  // Realizamos los calculos y almacemos los valores en las variables que mandamos por puntero
  analogWrite(pwmL,vel_left);  // Cargamos el valor de la velocidad en el motor izquierdo
  analogWrite(pwmR,vel_right);  // Cargamos el valor de la velocidad en el motor derecho

  //-------------------------------- Realizamos los c�lculos para los motores seg�n las variables recibidas ------------------------------------------//
  if (speed >= 0){   // En este caso se entiende que el robot debe avanzar  
    if(turn >= 100){        // Giramos a la derecha completamente al 100% por lo que el motor derecho gira en sentido contrario (El robot no avanza, solo gira)
      MOT_LEFT_FORWARD;
      MOT_RIGHT_REVERSE;
    }
    else if( turn <= -100){ // Giramos a la izquierda completamente al 100% por lo que el motor izquierdo gira en sentido contrario (El robot no avanza, solo gira)
      MOT_LEFT_REVERSE;
      MOT_RIGHT_FORWARD;
    }
    else{                   // El robot avanza o gira mientras continua hacia delante por lo que ambos motores van giran en sentido positivo.
      MOT_LEFT_FORWARD;
      MOT_RIGHT_FORWARD;
    }
  }
  else{                  // En este caso se entiende que el robot debe retroceder
    if(turn >= 100){        // Giramos a la derecha (Visto desde atr�s) completamente al 100% por lo que el motor derecho gira en sentido contrario (El robot no retrocede, solo gira)
      MOT_LEFT_REVERSE;
      MOT_RIGHT_FORWARD;
    }
    else if( turn <= -100){ // Giramos a la izquierda (Visto desde atr�s) completamente al 100% por lo que el motor izquierdo gira en sentido contrario (El robot no retrocede, solo gira)
      MOT_LEFT_FORWARD;
      MOT_RIGHT_REVERSE;
    }
    else{                   // El robot retrocede o gira continua hacia atr�s por lo que ambos motores van giran en sentido negativo.
      MOT_LEFT_REVERSE;
      MOT_RIGHT_REVERSE;
    }
  }
}
