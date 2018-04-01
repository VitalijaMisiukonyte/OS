#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "Processor.h"
#include "HardDisk.h"

char prog_header[4];
char header_format[4] = { 'S', 'T', 'R', 'T' }; 
char name[20];

//compare_Commands. Paskirtis - masyvu lyginimas
int compare_Commands(char* array1, char* array2, int length){
  int comparison = 1, j;
  for (j = 0; j < length; j++){
    if ((comparison) && (array1[j] != array2[j])) comparison = 0;
  }
  return comparison;
}

//openFile - failo atidarymas ir komandu skaitymas
void openFile(char* current_file){
  char* character = calloc(sizeof(char), 1);
  
  int file = open(current_file, O_RDONLY, 0); 
   
  if (file == -1){ 
    printf("Failed to open file!\nEnd of VM\n");
    exit(1);
  } 

  read(file, prog_header, 4); 
  read(file, character, 1); 
  *character = 0;

  //Headerio tikrinimas
  if (!compare_Commands(prog_header, header_format, 4)) {
    printf("Bad header.\nEnd of VM\n");
    exit(1);
  }
  
  //Komandu pavadinimu skaitymas
  int i = 0; 
  while (*character != '\n'){
    read(file, character, 1);
    if (*character != '\n'){
      name[i] = *character;
      i++;
    }
    if (i > 20) { 
      printf("Name of command is too long!\nEnd of VM\n");
      exit(1);
    }
  }
  
  //Komandu nuskaitymas is isorines atminties i atminti
  scanCommands(file); 
  
  //Komandu (ne)buvimo tikrinimas
	short PC = get_pc();
  if ((PC == 0) && (memory[page[(PC/10)]-1][(PC%10)] == 0)) {
    printf("There are no commands in the program!\nEnd of VM\n");
    
    exit(1);    
  }  
  
  close(file);
}

void scanCommands(int handle){
  int block = 0, word = 0;
  char ending_format[4] = { 'S', 'T', 'O', 'P' };
  char command[4];
  
  //Komandu skaitymas is failo
  while ((read(handle, command, 4) != 0) && !compare_Commands(command, ending_format, 4)){ 
    char s; 
    read(handle, &s, 1);

    char command_MV[2] = { 'G', 'O' };
    if (compare_Commands(command, command_MV, 2)){ 
      block = command[2] - 48;
      word = command[3] - 48;
      if ((block > 9) || (block < 0)){
        printf("Bad memory adress provided: %c%c%c%c.\nEnd of VM\n", command[0], command[1], command[2], command[3]);
        exit(1);
      }
    }
    else{
      if ((block <= 9) && (block >= 0)){ 
        memory[page[block]-1][word] = command[0]*0x1000000+command[1]*0x10000+command[2]*0x100+command[3];
        word++;
        if (word > 9){
          block++;
          word = 0;
        }
      }
      else{
        printf("Command %c%c%c%c caused overflow\nEnd of VM\n", command[0], command[1], command[2], command[3]);
        exit(1);        
      }
    }
  }  
}
