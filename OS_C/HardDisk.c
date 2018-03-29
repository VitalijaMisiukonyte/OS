#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "Processor.h"
#include "HardDisk.h"

char programos_antraste[4];
char antraste_formatas[4] = { 'P', 'R', 'O', 'G' }; 
char pavadinimas[20];

//Palygina 2 char masyvus. Grazina 1, jei abu yra vienodi
int palyginti_komandas(char* mas1, char* mas2, int ilgis) {
  int palyginimas = 1, j;
  for (j = 0; j < ilgis; j++) {
    if ((palyginimas) && (mas1[j] != mas2[j])) palyginimas = 0;
  }
  return palyginimas;
}
//------------------------------------------------------------------------------
//Atidaro faila ir is jo skaito komandas
void atidaryti_faila(char* failas)
{
  char* simb = calloc(sizeof(char), 1);
  
  int file = open(failas, O_RDONLY, 0); 
   
  if (file == -1) { 
    printf("Failo atidaryti neimanoma.\nVM darbo pabaiga.\n");
    
    exit(1);
  } 

  int bytes = read(file, programos_antraste, 4); 
  read(file, simb, 1); 
  *simb = 0;
  //patikrina, ar teisingai nuroyta programos antraste
  if (!palyginti_komandas(programos_antraste, antraste_formatas, 4)) {
    printf("Klaidingai nurodyta programos antraste.\nVM darbo pabaiga.\n");
    
    exit(1);
  }
  
  //skaito programos pavadinimas
  int i = 0; 
  while (*simb != '\n') {
    read(file, simb, 1);
    if (*simb != '\n') {
      pavadinimas[i] = *simb;
      i++;
    }
    if (i > 20) { 
      printf("Programoje nurodytas per ilgas pavadinimas.\nVM darbo pabaiga.\n");
      
      exit(1);
    }
  }
  
  //is isorines atminties nuskaito komandas i atminti
  nuskaityti_komandas(file); 
  
  //faile nera aprasyta jokiu VM komandu
  if ((PC == 0) && (atmintis[psl[(PC/10)]-1][(PC%10)] == 0)) {
    printf("Programoje nera uzrasytu komandu.\nVM darbo pabaiga.\n");
    
    exit(1);    
  }  
  
  close(file);
}
//------------------------------------------------------------------------------
void nuskaityti_komandas(int handle) 
{
  int blokas = 0, zodis = 0;
  char pabaiga_formatas[4] = { '.', 'E', 'N', 'D' };
  char komanda[4];
  
  //skaitomos komandos is failo
  while ((read(handle, komanda, 4) != 0) && !palyginti_komandas(komanda, pabaiga_formatas, 4)) { 
    char s; 
    read(handle, &s, 1);

    char komanda_move[2] = { 'M', 'V' };
    if (palyginti_komandas(komanda, komanda_move, 2)) { 
      blokas = komanda[2] - 48;
      zodis = komanda[3] - 48;
      if ((blokas > 9) || (blokas < 0)) {
        printf("Nekorektiskai parasyta komanda (nurodo bloga adresa atmintyje): %c%c%c%c.\nVM darbo pabaiga.\n", komanda[0], komanda[1], komanda[2], komanda[3]);
        
        exit(1);
      }
    }
    else {
      if ((blokas <= 9) && (blokas >= 0)) { 
        atmintis[psl[blokas]-1][zodis] = komanda[0]*0x1000000+komanda[1]*0x10000+komanda[2]*0x100+komanda[3];
        zodis++;
        if (zodis > 9) {
          blokas++;
          zodis = 0;
        }
      }
      else {
        printf("Komanda %c%c%c%c perzenge atminties ribas.\nVM darbo pabaiga.\n", komanda[0], komanda[1], komanda[2], komanda[3]);
        
        exit(1);        
      }
    }
  }  
}
