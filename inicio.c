#include "parametros.h"

void calculoParametrosRed(){
	//Calculamos el numero total de nodos en la red y el numero total de conexiones (hay el doble de conexiones que de links que unen nodos)
	numeroNodos=numeroDeNodosBethe(numeroDeCapas,z);
	numeroNodosFrontera=numeroDeCeldasEnCapaBethe(numeroDeCapas,z);
	numeroConexiones=(numeroNodos-numeroNodosFrontera)*z+numeroNodosFrontera;
}

void reservaMemoria(){
	h=malloc(numeroNodos*sizeof(double));
	hn=malloc(numeroNodos*sizeof(double));
	aleatoriosGauss=malloc(numeroNodos*sizeof(double));
	numVecinos=malloc(numeroNodos*sizeof(int));
	inicioVecinos=malloc(numeroNodos*sizeof(int));
	conexiones=malloc(numeroConexiones*sizeof(int));
	coeficienteLaplaciano=malloc(numeroConexiones*sizeof(double));
	coeficienteGradiente=malloc(numeroConexiones*sizeof(double));
	celdaDeLaQueProviene=malloc(numeroNodos*sizeof(int));
}

void vecinos(){
	// Calculo de los vecinos de la red. Rellenar los vectores numVecinos,inicioVecinos y conexiones
	int i,acum,j,produce;
	for(i=0;i<numeroNodos;i++){
		if(pertenceFronteraQBethe(numeroDeCapas,z,i)){
			numVecinos[i]=1;
		}else{
			numVecinos[i]=z;
		}
	}
	inicioVecinos[0]=0;//Inicializamos el valor
	for(i=1;i<numeroNodos;i++){
		inicioVecinos[i]=inicioVecinos[i-1]+numVecinos[i-1];
	}
	for(i=0;i<z;i++){
		conexiones[i]=i+1;//Inicializamos los valores de la lista de conexiones con el valor de la celda central
		//printf("conexiones[%d]=%d\n",i,conexiones[i]);
	}
	acum=z;//indice de la lista de conexiones
	
	for(i=1;i<numeroNodos;i++){
		conexiones[acum]=celdaDeDondeProvieneBethe(i,z);
		//printf("conexiones[%d]=%d\n",acum,conexiones[acum]);
		produce=celdaQueProduceBethe(i,z);
		acum=acum+1;
		for(j=1;j<numVecinos[i];j++){//Si es de la frontera no entra en este bucle.
			conexiones[acum]=produce;
			//printf("conexiones[%d]=%d\n",acum,conexiones[acum]);
			produce=produce+1;//para el siguiente paso del bucle
			acum=acum+1;//Asi cuando recorra la siguiente iteracion del bulce anterior esta bien puesto
		}
	}
	//printf("acum: %d\n",acum);
}

void escribeRed(){
	FILE* red;
	int i;
	snprintf(nombre,sizeof(nombre),"NumVecinos_%lld.dat",sem);
	red=fopen(nombre,"a");
	for(i=0;i<numeroNodos;i++){
		fprintf(red,"%d\n",*(numVecinos + i ));
		fflush(red);
	}
	fclose(red);
	snprintf(nombre,sizeof(nombre),"InicioVecinos_%lld.dat",sem);
	red=fopen(nombre,"a");
	for(i=0;i<numeroNodos;i++){
		fprintf(red,"%d\n",*(inicioVecinos + i ));
		fflush(red);
	}
	fclose(red);
	snprintf(nombre,sizeof(nombre),"Conexiones_%lld.dat",sem);
	red=fopen(nombre,"a");
	for(i=0;i<numeroConexiones;i++){
		fprintf(red,"%d\n",*(conexiones + i ));
		fflush(red);
	}
	fclose(red);
}

void condicionInicial(){
	int i;
	for(i=0;i<numeroNodos;i++){
		h[i]=0.0;
	}
	tiempo=0.0;//tiempo
}

void parametrosReducidos(){
	int i,j,k;
	nuRed=nu*deltaT;
	ruido=sqrt(2.0*D*deltaT);
	lambdaRed=lambda*deltaT/2.0;
	// Ahora calculamos los coeficientes de la ecuacion.
	k=0;
	for(i=0;i<numeroNodos;i++){
		//En inicioVecinos[i]+j esta el nodo al que va el enlace concreto.
		for(j=0;j<numVecinos[i];j++){
			// Caso de la ecuacion con los operadores normalizados
			/*
			coeficienteLaplaciano[k]=1.0/sqrt(1.0*numVecinos[i]*numVecinos[conexiones[inicioVecinos[i]+j]]);
			coeficienteGradiente[k]=(1.0*numVecinos[conexiones[inicioVecinos[i]+j]])/(1.0*numVecinos[i]);
			*/
			// Caso combinatorio
			
			coeficienteLaplaciano[k]=1.0;
			coeficienteGradiente[k]=1.0;///numVecinos[i];
			
			//printf("%d --> %d coef Lapla:%lf , coef Grad^2:%lf \n",i,conexiones[inicioVecinos[i]+j],coeficienteLaplaciano[k],coeficienteGradiente[k]);
			k++;
		}
	}
	//printf("k:%d,numeroConexiones:%d \n",k,numeroConexiones);//Deben ser iguales
	for(i=1;i<numeroNodos;i++){
		celdaDeLaQueProviene[i]=celdaDeDondeProvieneBethe(i,z);
	}
}



