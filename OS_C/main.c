#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Processor.h"
#include "HardDisk.h"
#include "atmintis.h"

char rezimas;

int palyginti_komandas(char*, char*, int);
void atidaryti_faila(char*);
void nuskaityti_komandas(int);

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{ 
  int simb;
  int pasirinkta = 0;
  
  psl = isskirti_atminti();   
  atidaryti_faila("programa.txt");       
           
  printf("=== VIRTUALI MASINA ===\n");
  printf("\nPasirinkite VM darbo rezima:\n1 - programos vykdymas is karto\n2 - programos vykdymas pazingsniniu rezimu\n");
  while (!pasirinkta) {
	char simb[1];
      gets(simb);
    switch (simb[0]){
      case '1': rezimas = 'r'; pasirinkta = 1; break;
      case '2': rezimas = 's'; pasirinkta = 1; break;
      default: printf("Neteisingai pasirinktas VM darbo rezimas.\n");
    }
  }
  
  if (rezimas == 'r') {  //prorama vykdoma is karto
    printf("\n");
    while (sekanti_komanda());
  }
  else {                 //programa vykdoma pazingsniui
    int end = 0;
    printf("\n---Programos vykdymas pazingsniui---\n");
    int step = 1;
    while (!end) {
      printf("\n(%d zingsnis)_________________________________________\n ", step);
      printf("Pasirinkite komandos numeri is saraso:\n");
      printf("\t     1 - sekancios komandos vykdymas: ");
      short PC = get_pc();
      char simb_pc[4] = { (atmintis[psl[(PC/10)-1]][PC%10] & 0xFF000000) / 0x1000000, (atmintis[psl[(PC/10)-1]][PC%10] & 0xFF0000) / 0x10000, 
                          (atmintis[psl[(PC/10)-1]][PC%10] & 0xFF00) / 0x100, (atmintis[psl[(PC/10)-1]][PC%10] & 0xFF) };
      printf("%c%c%c%c\n", simb_pc[0], simb_pc[1], simb_pc[2], simb_pc[3]);
      printf("\t     2 - atminties rodymas\n");
      printf("\t     3 - registru rodymas\n");
      printf("\t     4 - darbo nutraukimas\n");
      printf("______________________________________________________\n\n");
	char buffer[1];
      gets(buffer);
      switch (buffer[0]) {
        case '1': end = !sekanti_komanda(); step++; break;
        case '3': rodyti_registrus(); break;
        case '2': rodyti_atminti(); break;
        case '4': end = 1; break;
        default: printf("Neteisingai ivestas komandos numeris.\n");
      }
    }
    printf("Programa baige darba.\n");
  }
  	
  return 0;
}
//------------------------------------------------------------------------------

