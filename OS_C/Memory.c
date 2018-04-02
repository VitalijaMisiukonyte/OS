#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Memory.h"
#include "Processor.h"

long* allocate_Memory(){
//Puslpiu bloko adresas
  int paging_adr = 30;      
  int nr = 0;
  int i = 0;
  
  while ((memory[paging_adr][0] != 0) && (paging_adr < 35)) paging_adr++;  
  //Atmintyje nera laisvos vietos puslapiams
  if (memory[paging_adr][0] != 0) return 0; 
 
  while ((nr < 10) && (i < 30)){
    if (check_Memory(i)){
      //Realaus takelio numeris
      memory[paging_adr][nr] = i + 1;   
      nr++;
    }
    i++;
  }
  
  if (nr == 10){
    return &memory[paging_adr][0];
  }
  //Nera vietos printinimui
  else return 0;   
}

//show_Memory - parodo kaip atrodo atmintis 
void show_Memory(){
  int i, j, k;
  
  printf("\nB/W");
  for (k = 0; k < 10; k++) printf("  %d  ", k);
  printf("\n*******************************************************\n");
  for (i = 0; i < 35; i++){
    if (i < 10) printf("%d  | ", i);
    else printf("%d | ", i);
    for (j = 0; j < 10; j++){
      if (memory[i][j] > 10) printf("%c%c%c%c ", (int)(memory[i][j] & 0xFF000000) / 0x1000000, (int)(memory[i][j] & 0xFF0000) / 0x10000, (int)(memory[i][j] & 0xFF00) / 0x100, (int)(memory[i][j] & 0xFF));
      else if (memory[i][j] == 0) printf("0    ");
           else if (memory[i][j] != 10) printf("%ld    ", memory[i][j]);
                else printf("10   ");
    }
    printf("\n");
  }
  printf("\n*******************************************************\n");
}

//check_Memory, kurio paskirtis - tikrinti ar yra laisvas atminties laukas.
int check_Memory(int x){
  int i, j;
  int free = TRUE;
  
  for (i = 30; i < 35; i++){
    for (j = 0; j < 10; j++){
      if ((free) && (x == memory[i][j] - 1)) free = FALSE; 
    }
  }
  return free;
}
