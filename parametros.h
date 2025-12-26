#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////
//////// DEFINICIONES PARA GENERACION N ALEATORIO ////////
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef unsigned long long randint;
// typedef double randreal;
#define TWOBRMINUS1   18446744073709551615ULL //2^64 - 1
#define TWOBR         18446744073709551616.   //2^64
#define TWOBRM1       9223372036854775808ULL  //2^63
#define FNORM (5.4210108624275218e-20)// max double such that RAND_MAX*NORMF<1
#define CGRANDOM  ( zseed=zseed*3202034522624059733LLU+1)
#define PRRANDOM  ( (ira[ip++]=ira[ip1++]+ira[ip2++]) ^ira[ip3++] )
// #define MYRANDOM   PRRANDOM                         // P-R generator
#define MYRANDOM   CGRANDOM                       // Congruential generator
#define HIRANDOM  ((randint) (PRRANDOM + CGRANDOM)) //Addition of both
#define FRANDOM (FNORM*MYRANDOM)   //A floating point, 0<=pseudo-random<1
#define CGFRANDOM (FNORM*CGRANDOM)   //A floating point, 0<=pseudo-random<1
#define FHIRANDOM (FNORM*HIRANDOM) //A floating point, 0<=pseudo-random<1
randint ira[256];        //The Parisi-Rapuano wheel
unsigned char ip,ip1,ip2,ip3; //Variables for Parisis-Rapuano PRNG 
randint zseed;
////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////


// CONSTANTES
#define PI 3.14159265358979323846// PI
#define TWOPI 6.2831853071795864769
// PARAMETROS DE LA ECUACION
//#define deltaX 1.0//Discretizacion espacial// Se asume como 1 sin perdidad de generalidad



// VARIABLES GLOBALES
int numeroConexiones;
int numeroNodos;
int numeroNodosFrontera;
int z;//numero de coordinacion
int numeroDeCapas;
double* h;//valor de las celdas que hay en el sistema
double* hn;//valores del paso siguiente
double* aleatoriosGauss;//ruidos
int* numVecinos;//numero de vecinos de cada indice
int* inicioVecinos;//donde empieza cada vecino en la lista de conexiones
int* conexiones;//lista de los vecinos.
double* coeficienteLaplaciano;
double* coeficienteGradiente;
int* celdaDeLaQueProviene;
double tiempo;//tiempo global del sistema
randint sem;//Semilla leida
FILE *fp1;//Archivo de salida;
FILE *fp2;//Archivo de salida;
FILE *fp3;//Archivo de salida;
FILE *fp4;//Archivo de salida;
FILE *fp5;//Archivo de salida;
double nu;
double lambda;
double D;
double c;
double nuRed;//nu*deltaT (para ahorrar calculos)
double lambdaRed;//lambda*deltaT/2
double ruido;//(para ahorrar calculos)
double deltaT;//Discretizacion temporal. Se asume que deltaX=1
int numPasos;//Numero de pasos de integracion
int nMedir;//Cada cuantos pasos se mide
char nombre[50];//Nombre del archivo donde vamos a escribir los datos.
char texto[200];//comodin para leer la primera linea


// Declaracion de las funciones
void semilla_sistema();
void inicializa_semilla(unsigned long long);
void descripcion();
void calculoParametrosRed();
void reservaMemoria();
void vecinos();
void escribeRed();
void condicionInicial();
void generaRuidos();
double calculaMedia();
double calculaVarianza(double);
void abreArchivos();
void cierraArchivos();
//void escribeVarianza();
void parametrosReducidos();
void mideFrente();

//Funciones especificas de la red de Bethe
int numeroDeNodosBethe(int , int );
int numeroDeCeldasEnCapaBethe(int , int );
int calculaCapaBethe(int , int );
bool pertenceFronteraQBethe(int , int , int );
int celdaDeDondeProvieneBethe(int , int );
int celdaQueProduceBethe(int , int );


