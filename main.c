#include "parametros.h"

int main(int argc, char *argv[]) {
	//Parametros del metodo main
	int k,i,j;
	double laplaciano,gradiente;
	switch(argc){
		case 2:// uno mas de los que hay. En argv[0] va el nombre del programa
			//printf("%s\n",argv[0]);//nombre programa
			//printf("%s",argv[1]);//nombre archivo para leer los parametros
			fp1=fopen(argv[1],"r");
			fgets(texto,200,fp1);
			fscanf(fp1,"%d\t%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%d\t%d", &z, &numeroDeCapas, &nu, &lambda, &D, &c, &deltaT, &numPasos, &nMedir);
			fclose(fp1);
			break;
		default:
			printf("Error en el programa: %s numero de argumentos incorrecto\n",argv[0]);
			exit(0);
	}
	
	semilla_sistema();
	inicializa_semilla(zseed);
	calculoParametrosRed();
	descripcion();
	reservaMemoria();
	vecinos();
	escribeRed();
	condicionInicial();
	parametrosReducidos();
	abreArchivos();

	//Bucle principal del programa	
	for(k=0;k<numPasos;k++){
		//Actualizamos todos los elementos
		generaRuidos();
		for(i=0;i<numeroNodos;i++){
			// Método Euler explicito
			laplaciano=0.0;
			gradiente=0.0;
			for(j=0;j<numVecinos[i];j++){
				laplaciano+=h[conexiones[inicioVecinos[i]+j]];
				gradiente+=(h[i]-h[conexiones[inicioVecinos[i]+j]])*(h[i]-h[conexiones[inicioVecinos[i]+j]]);

			}
			laplaciano=laplaciano-(1.0*numVecinos[i])*h[i];// Caso combinatorio
			gradiente=(1-exp(-c*gradiente))/c;
			
			hn[i]=h[i]+nuRed*laplaciano+lambdaRed*gradiente+ruido*aleatoriosGauss[i];
			
		}
		if((k%nMedir)==0){
			mideFrente();
		}
		tiempo+=deltaT;
		for(i=0;i<numeroNodos;i++){
			h[i]=hn[i];//Actualizamos los valores
		}
	}
	
	cierraArchivos();
	return 1;
}
