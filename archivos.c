#include "parametros.h"

void abreArchivos(){
	snprintf(nombre,sizeof(nombre),"Salida_frente_%lld.dat",sem);
	fp1=fopen(nombre,"a");
}

void cierraArchivos(){
	fclose(fp1);
}

void mideFrente(){//debe ser definida en los parametros y eliminada las otras salidas
	int i;
	fprintf(fp1,"%lf",tiempo);//Primero medimos el tiempo
	fflush(fp1);
	for(i=0;i<numeroNodos;i++){
		fprintf(fp1,"\t%lf",h[i]);//Mido el valor de todos los nodos
		fflush(fp1);
	}
	fprintf(fp1,"\n");//Pasamos a la siguiente linea
	fflush(fp1);
}