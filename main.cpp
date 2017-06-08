//Programa principal
//Creado por FDSoftware/Frenoux Diego

#include <Arduino.h>

int ord_enc[] = 0, 2 ,3 ,1; //orden de encendido motor
int iny[] = 2,3,4,5;       //Pines de arduino que esta conectados los inyectores
int tRalenti = 2;          //tiempo de inyeccion en ralenti
int tMax     = 22;          //timpo maximo de inyeccion

int pul  = LOW;             //pulso de disparo de sensor de posicion de cigueñal
bool varrpm = LOW;          //variable para no volver a contar mismo diente como pulso
int pinrpm = 10;            //pin conectado al sensor de posicion de cigueñal

int diente = 0;             //numero de diente actual de la corona
int intervalo1 = 500;       //intervalo para medir rpm

int dnt  = XX;              //cantidad de dientes de corona
int dntI = XX;              //cantidad de dientes entre inyecciones
int dntE = XX;              //cantidad de dientes entre punto muerto superior de cilindros

/*
int avEnFunc = XX;          //cantidad de grados/dientes de avance del encendido con motor a temperatura funcionamiento
int avEnFrio = XX;          //cantidad de grados/dientes de avance del encendido con motor frio
int avEnArra  = XX;         //cantidad de grados/dientes de avance del encendido con motor en modo arranque
----------------------------IMPORTANTE----------------------------------
reemplazo estas tres variables por una sola para una facil utilización del avance del encendido
en cambio, en vez de tener 3 variables de avance tenemos 3 métodos , frio, normal y arranque
--------------------------------------------------------------------------
    |
    V
*/
avanceDeChispa = 3;//en dientes de volante (2,42 grados) , default en 3

int Mar   = AN0;            //pin de mariposa de acelerador
int Lamb  = AN1;            //pin de sonda lambda

int var = 0;                //variable usada para bucles
int rpm = 0;
unsigned long prevMillis; //tiempo previo ultimo periodo medicion rpm
unsigned long curMillis; //tiempo actual del micro

void setup(){
    //definir E/S
    pinMode(pinrpm, INPUT);

    for(var = 0, var >= 3, var++;){
        pinMode(iny[var], OUTPUT);
    }

    for(var = 0, var >= 3, var++;){
        digitalWrite(iny[var], LOW);
    }
}

void loop(){

        Temperatura();
        ControlRPM();
        ControlINY();
        ControlENC();
}

void ControlRPM(){
    //cada vez que detecta un pulso del sensor de posicion de cigueñal, miede las rpm, y guarda
    //la cantidad de dientes que va detectando

    //Detectamos pulsos y guardamos dato
     puls = digitalRead(IN1);
     if (puls == LOW && var == false){
         diente++;
        varrpm = true;
    }if(puls == HIGH && var6[var5] == true){
     varrpm = false;
  }
    //calculo RPM
     curMillis = millis();
      if (curMillis - prevMillis >= intervalo1) {
	    	prevMillis = curMillis;
	    	if(diente <= dnt){
                rpm = ((diente * 2)*60 /dnt);
		    }
      }

if (diente == dnt){
	diente = 0;
}

}

void ControlINY(){
    //Controla los tiempos de inyeccion dependiendo la mariposa,rpm y temperatura del motor
}

//---------------
void ControlEncendidoFrio(){
    if(rpm < 2000){
        avanceDeChispa = 4;//+-10°
    }else if(rpm < 3000){
        avanceDeChispa = 6;//+-15°
    }else if(rpm < 4000){
        avanceDeChispa = 8;//+-20°
    }else if(rpm < 5000){
        avanceDeChispa = 10;//+-25°
    }else if(rpm < 6000){
        avanceDeChispa = 12;//+-30°
    }
}
void ControlEncendidoNormal(){
    if(rpm < 2000){
        avanceDeChispa = 4;//+-10°
    }else if(rpm < 3000){
        avanceDeChispa = 7;//+-17,5°
    }else if(rpm < 4000){
        avanceDeChispa = 10;//+-25°
    }else if(rpm < 5000){
        avanceDeChispa = 13;//+-32,5°
    }else if(rpm < 6000){
        avanceDeChispa = 15;//+-37,5°
    }
}
//se comprende que este método solo se va a ejecutar durante el funcionamiento del burro y solo
//5 segundos despues del arranque. acto seguidop pasar al metodo de avance en frio o caliente
//respectivamente
void ControlEncendidoArranque(float temperatura){
    if(temperatura < 45){
        avanceDeChispa = 2;//+-5°
    }else{
        avanceDeChispa = 3;//+-7,5°
    }
}
//------------

void Temperatura(){
    //Controla el ventilador y apagado de emergencia del motor
}
