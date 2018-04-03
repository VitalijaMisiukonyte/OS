#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Memory.h"
#include "Processor.h"
// Veikimo principas
// Nuo 30 bloka prasideda puslapiu lentele
// 
long* allocate_Memory(){
//Puslpiu bloko adresas
  int paging_adr = 30;      
  
  while ((memory[paging_adr][0] != 0) && (paging_adr < 33)) paging_adr++;  
  //Atmintyje nera laisvos vietos puslapiams
  if (memory[paging_adr][0] != 0) return 0; 
 
  // Vieta kur prasideda programos kodas
  // skiriami 5 blokai
  int progr_adr = (paging_adr % 30) * 10 + 1;
  memory[paging_adr][0] = progr_adr;

  for (int i = 1; i <= 5; ++i){
    memory[paging_adr][i] = 5 + progr_adr++ ;
  }

  return &memory[paging_adr][0];
}

//check_Memory, kurio paskirtis - tikrinti ar yra laisvas atminties laukas.
int check_Memory(int x){
  int i, j;
  int free = TRUE;
  
  for (i = 30; i < 33; i++){
    for (j = 0; j < 10; j++){
      if ((free) && (x == memory[i][j] - 1)) free = FALSE; 
    }
  }
  return free;
}


//show_Memory - parodo kaip atrodo atmintis 
void show_Memory(){
  int i, j, k;
  printf("Bl/Wr");
  for (k = 0; k < 10; k++) printf("  %d  ", k);
  printf("\n*******************************************************\n");
  for (i = 0; i < 33; i++){
    if (i < 10) printf("%d  | ", i);
    else printf("%d | ", i);
    for (j = 0; j < 10; j++){
      if (memory[i][j] != 0){
        if(i < 30 || (i >= 30 && j > 5)){
          char character[4] = { (memory[i][j] & 0xFF000000) / 0x1000000,
                                (memory[i][j] & 0xFF0000) / 0x10000, 
                                (memory[i][j] & 0xFF00) / 0x100, 
                                (memory[i][j] & 0xFF)};

          printf("%c%c%c%c ", character[0], 
                              character[1], 
                              character[2], 
                              character[3]);
        }else{
          printf("%-5ld", memory[i][j]);
        }
      }else{
        printf("0    ");
      }
    }
    printf("\n");
  }
  printf("\n*******************************************************\n");
}
