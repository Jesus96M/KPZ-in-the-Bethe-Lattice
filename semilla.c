#include "parametros.h"

void semilla_sistema(void){
	FILE* Frandfile;
	zseed=0;
	Frandfile = fopen("/dev/urandom","r");
	fread(&zseed,8,1,Frandfile);
	zseed=(unsigned long long) abs(zseed);
	fclose(Frandfile);
	sem=zseed;
}

void inicializa_semilla(unsigned long long semilla)     
{
  int i;           
    
  zseed=semilla;
  for (i=0;i<11;i++)         /* Just in case initial randomseed were small */
      CGRANDOM;
  
  ip=128;    
  ip1=ip-24;    
  ip2=ip-55;    
  ip3=ip-61;
  for (i=ip3; i<ip; i++)
      ira[i] = CGRANDOM;

  for (i=0;i<1111;i++)        
    if (!PRRANDOM)
      printf("Found zero in the first P-R random numbers generated\n");
}
