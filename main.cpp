//Programa principal
//Creado por FDSoftware y FrancisJPK

#include <Arduino.h>

int ord_enc[] = {0, 2 ,3 ,1};//orden de encendido motor
int iny[] = {2,3,4,5};       //Pines de arduino que esta conectados los inyectores
int tMax     = 22;           //tiempo maximo de inyeccion

int pul  = LOW;             //pulso de disparo de sensor de posicion de cigueñal
bool varrpm = LOW;          //variable para no volver a contar mismo diente como pulso
int pinrpm = 10;            //pin conectado al sensor de posicion de cigueñal

int diente = 0;             //numero de diente actual de la corona
int intervalo1 = 500;       //intervalo para medir rpm
float inyT = 1.5;              //tiempo de inyeccion ms
int esperaINY = 500;      //tiempo que espera inyeccion para ver si el motor acelera


int avanceDeChispa = 3;        //en dientes de volante (2,42 grados) , default en 3
bool arrancando = true;       //variable que indica si el motor esta apagado, se cambia a FALSE cuando el motor paso 800 rpm
int pinBobinas13 = 1;
int pinBobinas24 = 2;

int Mar   = AN0;            //pin de mariposa de acelerador
int marv  = 0;              //valor de mariposa de acelerador
int Lamb  = AN1;            //pin de sonda lambda
int sensorT = AN3;           //pin de sensor Temperatura
float temp = 0;             //temperatura motor

int var = 0;                //variable usada para bucles
int varX = 0;               //variable temporal, multiples usos
int varINY = 0              //varible temporal, guarda ultimo inyector activado

int rpm    = 0;                //numero actual de rpm
int rpmMIN = 800;             //numero minimo de rpm
int rpmMAX = 7000;            //numero maximo de rpm

int vuelta;                    //numero de vuelta para rpm
bool varr = false;             //variable para evitar calcular rpm varias veces
int vuelta2;                   //numero de vuelta para inyeccion/encendido
bool inyec = false;            //variable para saber si se esta inyectando todavia o no
bool acelerar;                 //varible temporar, guarda si se intento acelerar las rpm o no
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
    //definir interrupciones HW
    attachInterrupt(0,int0,RISING);
}

void loop(){

        Temperatura();
        ControlRPM();
        ControlINY();
        temp = sensortemp();
        controlDeEncendido(temp);
        ControlPWM();
}

void ControlRPM(){
   //calcula rpm cada 1 vuelta del cigueñal
      if(varr == false && vuelta == 0){
	  milisant = millis();
	  varr = true;
     }

     if(varr == true && vuelta == 2){
	    rpm = (millis() - milisant) * 60000;
	    varr = false;
	    var2 = 0;
     }
}

void ControlINY(){
    //Controla los tiempos de inyeccion dependiendo la mariposa,rpm y temperatura del motor
    if(rpm <= rpmMIN && varm <= 10 && acelerar == false){ //si las rpm caen debajo las rpm minimas y no esta presionado acelerador
            inyT = intT + 0.5;
            acelerar = true;
            rpmant = rpm;
         }

         if(rpm >= rpmMIN && varm <= 10 && acelerar == false){ //si las rpm pasan las rpm minimas y no esta presionado acelerador
            inyT = intT - 0.5;
            acelerar = true;
            rpmant = rpm;
         }
 int varxx = rpm - rpmant;
    if(vuelta3 >= 20 && varxx <= 5){
        // si no hubo un cambio mayor a 5 rpm luego de 10 vueltas de cigueñal volver a corregir
        acelerar = false;
        vuelta3 = 0;
    }

}
void Control PWM{
    if (inyectando == false){
	digitalWrite(iny[vuelta2++],HIGH);
	inyectando = true
}

	if (millis() - millis >= inYT) {
		digitalWrite(iny[vuelta2++],LOW);
		if(vuelta2 == 3){
			vuelta2 == 0;
		}
		inyectando == false
	}
}


void controlDeEncendido(float temperatura){

    //----bloque que controla el avance antes de hacer la chispa----
    if(arrancando == true){
        ControlEncendidoArranque(temperatura);
    }else if(arrancando == false){
        if(temperatura < 40){
            ControlEncendidoFrio();
        }else{
            ControlEncendidoNormal();
        }
    }
    //-------fin del bloque de control de avance-----------
    if(diente == (33 - avanceDeChispa) ){//chispazo para el piston 1 y 3(siendo el 3 chispa perdida)
        iniciarChispazo(pinBobinas13);
        //esperar un tiempito
        pararChispazo(pinBobinas13);
    }else if(diente == (66 - avanceDeChispa){//chispazo para el piston 1 y 3(siendo el 1 chispa perdida)
        iniciarChispazo(pinBobinas13);
        //esperar un tiempito
        pararChispazo(pinBobinas13);
    }else if(diente == (99 - avanceDeChispa){//chispazo para el piston 2 y 4(siendo el 4 chispa perdida)
        iniciarChispazo(pinBobinas24);
        //esperar un tiempito
        pararChispazo(pinBobinas24);
    }else if(diente == (132 - avanceDeChispa){//chispazo para el piston 2 y 4(siendo el 2 chispa perdida)
        iniciarChispazo(pinBobinas24);
        //esperar un tiempito
        pararChispazo(pinBobinas24);
    }
    //------bloque que controla la mandada de chispa


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
void ControlEncendidoArranque(float temperatura){
    if(temperatura < 45){
        avanceDeChispa = 2;//+-5°
    }else{
        avanceDeChispa = 3;//+-7,5°
    }
}
void iniciarChispazo(int pin){//inicia la chispa hasta que se llame al metodo pararChispazo()
    digitalWrite(pin, HIGH);
}
void pararChispazo(int pin){//para la chispa
    digitalWrite(pin, HIGH);
}
//------------

void Temperatura(){
    //Controla el ventilador y apagado de emergencia del motor
}

float  sensortemp(){
    int value = analogRead(sensorPin);
    float millivolts = (value / 1023.0) * 5000;
    float celsius = millivolts / 10;
    return celsius;
}
void int0{
    vuelta++;
    vuelta2++;
    vuelta3++;
    varr = true;
}
