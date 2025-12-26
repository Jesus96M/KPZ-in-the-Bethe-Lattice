#include "parametros.h"

int numeroDeNodosBethe(int numeroCapas, int z){
	return 1+z*(pow((z-1),numeroCapas)-1)/(z-2);
}

int numeroDeCeldasEnCapaBethe(int capa, int z){
	if(z==0){
		return 1;
	} else {
		if(capa==1){
			return z;
		} else{
			return z*pow((z-1),(capa-1));
		}
	}
}

int calculaCapaBethe(int z, int ind){
	int i;
	ind=ind-1;
	if(ind<0){
		return 0;
	} else{
		ind=ind-z;
		if(ind<0){
			return 1;
		} else{
			i=1;
			while(ind>=0){
				ind=ind-z*pow((z - 1),i);
				i++;
			}
			return i;
		}
	}
}

bool pertenceFronteraQBethe(int numeroDeCapas, int z, int ind){
	int dif;
	dif=numeroDeNodosBethe(numeroDeCapas,z)-numeroDeCeldasEnCapaBethe(numeroDeCapas,z);
	if(ind>=dif){
		return true;
	} else{
		return false;
	}
}

int celdaDeDondeProvieneBethe(int ind, int z){
	int capa;
	int delta;
	capa=calculaCapaBethe(z,ind);
	if(ind==0){
		return NULL;
	} else if(capa==1){
		return 0;
	} else{
		delta=ind-z*((pow((z-1),(capa-1)))-1)/(z-2);
		if(delta%(z-1)==0){
			return z*((pow((z-1),(capa-2)))-1)/(z-2)+(delta)/(z-1);
		}else return z*((pow((z-1),(capa-2)))-1)/(z-2)+(delta)/(z-1)+1;//En mathematica usamos ceiling. Aquí usamos la divison entera de C 
		//z*(((z - 1)^(capa - 2)) - 1)/(z - 2) + Ceiling[delta/(z - 1)]]]
	}
}

int celdaQueProduceBethe(int ind, int z){
	//La salida es el indice de la primera celda de las z que hay. El resto es trivial obtenerlas conocido el z.
	int capa;
	int delta;
	capa=calculaCapaBethe(z,ind);
	if(ind==0){
		return 1;
	} else{
		delta=ind-z*((pow((z-1),(capa-1)))-1)/(z-2);
		return z*((pow((z - 1),capa))-1)/(z-2)+(delta-1)*(z-1)+1; 
	}
}

	/*
	//Chekeo de Bethe en el main.c
	printf("nnB:%d\n",numeroDeNodosBethe(8,3));
	printf("nnB:%d\n",numeroDeNodosBethe(10,3));
	printf("nnB:%d\n",numeroDeNodosBethe(5,5));
	
	printf("nCC:%d\n",numeroDeCeldasEnCapaBethe(3,3));
	printf("nCC:%d\n",numeroDeCeldasEnCapaBethe(2,3));
	printf("nCC:%d\n",numeroDeCeldasEnCapaBethe(5,4));
	
	printf("CC:%d\n",calculaCapaBethe(3,15));
	printf("CC:%d\n",calculaCapaBethe(4,68));
	printf("CC:%d\n",calculaCapaBethe(5,156));
	
	if(pertenceFronteraQBethe(10, 3, 0)){
		printf("Pertenece\n");
	}else printf("No pertenece\n");
	
	if(pertenceFronteraQBethe(7, 5, numeroDeNodosBethe(6,5)-1)){
		printf("Pertenece\n");
	}else printf("No pertenece\n");
	
	if(pertenceFronteraQBethe(7,5, numeroDeNodosBethe(6,5))){
		printf("Pertenece\n");
	}else printf("No pertenece\n");
	

	printf("CProv:%d\n",celdaDeDondeProvieneBethe(17,3));
	printf("CProv:%d\n",celdaDeDondeProvieneBethe(18,4));
	printf("CProv:%d\n",celdaDeDondeProvieneBethe(57,5));
	
	printf("CProd:%d\n",celdaQueProduceBethe(1,3));
	printf("CProd:%d\n",celdaQueProduceBethe(18,5));
	printf("CProd:%d\n",celdaQueProduceBethe(5,3));
	*/
