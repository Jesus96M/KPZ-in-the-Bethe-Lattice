#include "parametros.h"

void generaRuidos(){//Usa ambos numeros para ahorrar tiempo
	double u1,u2;//Dos uniformes en (0,1)
	int i;
	for(i=0;i<(numeroNodos/2);i++){
		u1=FHIRANDOM;
		u2=FHIRANDOM;
		aleatoriosGauss[2*i]=sqrt(-2.0*log(u1))*cos(TWOPI*u2);
		aleatoriosGauss[2*i+1]=sqrt(-2.0*log(u2))*sin(TWOPI*u1);
	}
	//Si el numero de Nodos es impar el ultimo aleatoriosGauss no se ha generado en el bucle anterior
	// y hay que generar uno más para completar el vector de ruidos
	if(numeroNodos % 2 == 1){
		u1=FHIRANDOM;
		u2=FHIRANDOM;
		aleatoriosGauss[numeroNodos-1]=sqrt(-2.0*log(u1))*cos(TWOPI*u2);
	}
}

//Las dos funciones siguientes ya no se usan

double calculaMedia(){
	int i;
	double media=0.0;
	for(i=0;i<numeroNodos;i++){
		media+=h[i];
	}
	media=media/numeroNodos;
	return media;
}

double calculaVarianza(double media){
	int i;
	double var=0.0;
	for(i=0;i<numeroNodos;i++){
		var+=pow(h[i]-media,2.0);
	}
	var=var/numeroNodos;
	return var;
}
