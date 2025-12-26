#include "parametros.h"

void descripcion(){
	// Funcion que genera un archivo txt donde se escriben las caracteristicas de la simulacion
	FILE *datos1=fopen("descripcion.txt","w");
	fprintf(datos1,"Integracion numerica de KPZ para la red de Bethe.\n");
	fprintf(datos1,"Metodo de integracion utilizado:\n");
	fprintf(datos1,"Euler explícito \n");
	fprintf(datos1,"Discretizacion estandar para el gradiente \n");
	fprintf(datos1,"Regularización con c=%lf \n",c);
	fprintf(datos1,"Los parámetros utilizados son:\n");
	fprintf(datos1,"z=%d, numeroDeCapas=%d\n",z,numeroDeCapas);
	fprintf(datos1,"numeroNodos=%d, numeroConexiones=%d\n",numeroNodos,numeroConexiones);
	fprintf(datos1,"nu=%lf, lambda=%f, D=%lf \n",nu,lambda,D);
	fprintf(datos1,"deltaT=%lf, numPasos=%d, nMedir=%d \n",deltaT,numPasos,nMedir);
	fclose(datos1);
}

