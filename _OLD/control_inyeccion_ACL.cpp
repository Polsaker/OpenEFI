void ControlINY(){
	CINY_RPM = RPM();
	if(acl = false){
		if(CINY_RPM <= ARR_FLAG2 && CINY_RPM != 0){
			ARR_FRIO();
		}else if(CINY_RPM >= ARR_FLAG2 && CINY_RPM != 0){
			inyT = Tiny(CINY_RPM, marv); 
			 CINY_X = map(rpm,0,7000,0,70);
			CINY_X = CINY_X * 100;
			acl = ACL(CINY_X, inyT);
		}
	}else{acl = ACL(CINY_X, inyT);}
}
bool ACL(int rpmOBJ, int TBASE){
	int ACL_RPM = RPM() - rpmOBJ;
	if(ACL_RPM >= 400 &&  vuelta2 > ACL_PER){ //diferencia mayor a 400 vueltas
		TBASE = TBASE - ACL_TMP; // sacamos 1.5mS de tiempo de inyeccion
		vuelta2 = 0;
		return true;
	} else if(ACL_RPM <= 400 && vuelta2 > ACL_PER){
		TBASE = TBASE + ACL_TMP;
		vuelta2 = 0;
		return true;
	}else {// ya no hace falta cambiar el tiempo desde esta funcion, esto habilita correccion por sonda lambda y TMAP
		acl = false;
		vuelta2 = 0;
		return false;} 
	}

int Tiny(int rpm2, int marv2, int op){
	int rpm3  = map(rpm2,0,7000,0,17); //aproximamos las rpm
	int marv3 = map(marv2,0,255,0,10); //aproximamos el valor de la mariposa de aceleracion
	if(OP == 0){ //Tiempo de inyeccion base
		return TINY[marv3,rpm3];
	}
}