#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Processor.h"
#include "HardDisk.h"
#include "Memory.h"

int main(int argc, char *argv[]){ 
  
  page = allocate_Memory(); 
  openFile("programa1.txt");       

           
  printf("*****Starting Virtual Machine*****\n");                
    int end = 0;

    while (!end){
      show_Memory();
      show_Registers(); 
      printf("Choose menu number:\n");
      printf("* 1 execute: ");
      short PC = get_pc();
      char character_pc[6] = {  (memory[PC/10][PC%10] & 0xFF0000000000) / 0x10000000000,
                                (memory[PC/10][PC%10] & 0xFF00000000) / 0x100000000,
                                (memory[PC/10][PC%10] & 0xFF000000) / 0x1000000,
                                (memory[PC/10][PC%10] & 0xFF0000) / 0x10000, 
                                (memory[PC/10][PC%10] & 0xFF00) / 0x100, 
                                (memory[PC/10][PC%10] & 0xFF) };
      printf("%c%c%c%c%c%c *\n",  character_pc[0], 
                                  character_pc[1], 
                                  character_pc[2], 
                                  character_pc[3],
                                  character_pc[4],
                                  character_pc[5]
          );
      printf("* 2 Exit *\n");
      char in;
      scanf(" %c",&in);
      getchar(); 
      switch (in){
        case '1': end = !nextCommand();
	               break;
        case '2':  end = 1;
	               break;
        default: printf("Bad command number\n");
      }
    }
    printf("Exiting Virtual Machine...\n");
  	
  return 0;
}


