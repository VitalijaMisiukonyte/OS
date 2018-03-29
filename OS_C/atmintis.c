#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "atmintis.h"
#include "Processor.h"


long* isskirti_atminti()
{
  int psl_adr = 30;      //Bloko adresas atminyje puslapiams
  int sk = 0;
  int i = 0;
  
  while ((atmintis[psl_adr][0] != 0) && (psl_adr < 35)) psl_adr++;  
  if (atmintis[psl_adr][0] != 0) return 0; //Atmintyje nera laisvos vietos puslapiams
 
  while ((sk < 10) && (i < 30)) {
    if (tikrinti_atminti(i)) {
      atmintis[psl_adr][sk] = i + 1;   //realaus takelio numeris
      sk++;
    }
    i++;
  }
  
  if (sk == 10) {
    return &atmintis[psl_adr][0];
  }
  else return 0;   //Atmintyje nera laisvos vietos isskirti 10 bloku virtualaus adreso
}
//------------------------------------------------------------------------------
//I ekrana isveda atminties turini 
void rodyti_atminti()
{
  int i, j, k;
  
  printf("   |Atmintis:\n");
  printf("Blokas/Zodis:\n");
  printf("     ");
  for (k = 0; k < 10; k++) printf("  %d  ", k);
  printf("\n______________________________________________________\n");
  for (i = 0; i < 35; i++) {
    if (i < 10) printf("%d  | ", i);
    else printf("%d | ", i);
    for (j = 0; j < 10; j++) {
      if (atmintis[i][j] > 10) printf("%c%c%c%c ", (atmintis[i][j] & 0xFF000000) / 0x1000000, (atmintis[i][j] & 0xFF0000) / 0x10000, (atmintis[i][j] & 0xFF00) / 0x100, atmintis[i][j] & 0xFF); 
      else if (atmintis[i][j] == 0) printf("0    ");
           else if (atmintis[i][j] != 10) printf("%d    ", atmintis[i][j]);
                else printf("10   ");
    }
    printf("\n");
  }
  printf("______________________________________________________\n");
}
//------------------------------------------------------------------------------
//Tikrina, ar atminties laukas laisvas
int tikrinti_atminti(int x)
{
  int i, j;
  int laisva = TRUE;
  
  for (i = 30; i < 35; i++) {
    for (j = 0; j < 10; j++) {
      if ((laisva) && (x == atmintis[i][j] - 1)) laisva = FALSE; 
    }
  }
  return laisva;
}
