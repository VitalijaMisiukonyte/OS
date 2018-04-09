#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "Processor.h"
#include "HardDisk.h"

char header_format[5] = { 'S', 'T', 'R', 'T', '\0' }; 
char ending_format[5] = { 'S', 'T', 'O', 'P', '\0' };
char prog_name[16];
char* buffer = NULL;
size_t len = 0;

// Compare 2 arrays.
int compare_Commands(char* array1, char* array2, int length){
  for (int j = 0; j < length; j++) 
    if (array1[j] != array2[j]) 
      return 0;
  
  
  return 1;
}

//openFile - failo atidarymas ir komandu skaitymas
void openFile(char* current_file){
  FILE *fptr = fopen(current_file, "r");

  if(fptr == NULL){
    printf("Failed to open file!\nEnd of VM\n");
    exit(EXIT_FAILURE);
  }

  // First line should start with programam header
  getline(&buffer, &len, fptr);
  buffer[strlen(buffer) - 1] = 0;
  
  // Header check.
  if (!compare_Commands(buffer, header_format, 4)) {
    set_PI(5);
    return;
  }

  // Read program name.
  getline(&buffer, &len, fptr);

  for(int i = 0; buffer[i] != '\n'; ++i){
    if (i >= 16) { 
      printf("Program name is too long.\n"
             "Expected max length: 16\n"
             "End of VM\n");
      exit(EXIT_FAILURE);
    }

    prog_name[i] = buffer[i];
  }

  set_program_name(prog_name, page[0]);
  
  scanCommands(fptr); 
}

void scanCommands(FILE* fptr){
  int block = 0;
  int word  = 0;

  //Komandu skaitymas is failo
  while(getline(&buffer, &len, fptr) != -1){
    buffer[strlen(buffer) - 1] = '\0';

    if(compare_Commands(buffer, ending_format, 4)){
	set_PI(6);
        return;
    }

    if(strlen(buffer) == 4) {
      

      set_memory(page[0] - 1 + block, word, buffer);

      word ++;
      if((word %= 10) == 0) block++;

      if (block % 10 > 5){
        printf("Not enough memory for program\n");
        exit(EXIT_FAILURE);
      }

    }else{
      printf("Bad format\n");
      exit(EXIT_FAILURE);
    } 
  }  
}
