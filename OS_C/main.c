#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Processor.h"
#include "HardDisk.h"
#include "Memory.h"

char mode;

int compare_Commands(char*, char*, int);
void openFile(char*);
void scanCommands(int);

int main(int argc, char *argv[]){ 
  int character;
  int choice = 0;
  
  page = allocate_Memory();   
  openFile("programa.txt");       
           
  printf("-----Virtual Machine-----");
  printf("\nPlease choose virtual machine mode:\n1 - programm execution\n2 - execute programm step by step\n");
  while(!choice){
  	char character[1];
	gets(character);
    	switch (character[0]){
      	  case '1': mode = 'r'; choice = 1; 
	                 break;
          case '2': mode = 's'; choice = 1;
	                 break;
          default: printf("Bad choice of mode!\n");
        }
  }

  //Programos vykdymas
  if (mode == 'r'){  
    printf("\n");
    while (nextCommand());
  }
  //Pazingsninis programos vykdymas
  else {                 
    int end = 0;
    printf("\n---Programm execution step by step---\n");
    int step = 1;

    while (!end){
      printf("\n_________________________________________\n ", step);
      printf("Choose command number:\n");
      printf("\t     1 - next command execution: ");
      short PC = get_pc();
      char character_pc[4] = { (memory[page[(PC/10)-1]][PC%10] & 0xFF000000) / 0x1000000, (memory[page[(PC/10)-1]][PC%10] & 0xFF0000) / 0x10000, 
                              (memory[page[(PC/10)-1]][PC%10] & 0xFF00) / 0x100, (memory[page[(PC/10)-1]][PC%10] & 0xFF) };
      printf("%c%c%c%c\n", character_pc[0], character_pc[1], character_pc[2], character_pc[3]);
      printf("\t     2 - show memory\n");
      printf("\t     3 - show registers\n");
      printf("\t     4 - terminate\n");
      printf("____________________________________________\n\n");
      
      char buffer[1];
      gets(buffer);
      switch (buffer[0]){
        case '1': end = !nextCommand(); step++;
	               break;
        case '2': show_Memory();
	               break;
        case '3': show_Registers();
	               break;
        case '4': end = 1;
	               break;
        default: printf("Bad command number\n");
      }
    }
    printf("End of processes\n");
  }
  	
  return 0;
}


