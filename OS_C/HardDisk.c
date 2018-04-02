#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "Processor.h"
#include "HardDisk.h"

char header_format[5] = { 'S', 'T', 'R', 'T', '\0' }; 
char ending_format[4] = { 'S', 'T', 'O', 'P' };
char prog_name[8];
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
    printf("Bad header.\n" "Expected: %s\n" "Got: %s\n" "End of VM\n"
                           ,header_format   ,buffer);
    exit(EXIT_FAILURE);
  }

  // Read program name.
  getline(&buffer, &len, fptr);

  for(int i = 0; buffer[i] != '\n'; ++i){
    if (i >= 8) { 
      printf("Program name is too long.\n"
             "Expected max length: 8\n"
             "End of VM\n");
      exit(EXIT_FAILURE);
    }

    prog_name[i] = buffer[i];
  }
 
  //  
  scanCommands(fptr); 
  
 //  //Komandu (ne)buvimo tikrinimas
 //  // MEMORY LEAK. THROW EXECPTION, NO CLOSE(FILE)

	// short PC = get_pc();

 //  if ((PC == 0) && (memory[page[(PC/10)]-1][(PC%10)] == 0)) {
 //    printf("There are no commands in the program!\nEnd of VM\n");
 //    close(file);
 //    exit(EXIT_FAILURE);    
 //  }  
  
 //  close(file);
}

void scanCommands(FILE* fptr){
  int block = 0;
  int word  = 0;

  void incr(){ word++; if((word %= 10) == 0) block++; }

  //Komandu skaitymas is failo
  while(getline(&buffer, &len, fptr) != -1){
    buffer[strlen(buffer) - 1] = '\0';

    if (strlen(buffer) == 6){ 
      memory[block][word] =   buffer[0] * 0x10000000000
                            + buffer[1] * 0x100000000
                            + buffer[2] * 0x1000000
                            + buffer[3] * 0x10000
                            + buffer[4] * 0x100
                            + buffer[5] * 0x1;

      incr();

    } else if(strlen(buffer) == 4) {
      memory[block][word] =   buffer[0] * 0x1000000
                            + buffer[1] * 0x10000
                            + buffer[2] * 0x100
                            + buffer[3] * 0x1;

      incr();

    }else{
      printf("Bad format\n");
      exit(EXIT_FAILURE);
    } 
  }  
}