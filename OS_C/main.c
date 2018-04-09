#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "Processor.h"
#include "HardDisk.h"
#include "Memory.h"

void intDetected(int x){
	printf("Interrupt code %d\n", x);
    if(x==2){
	printf("Program coused memory overflow\nQuitting Virtual Machine...\n");	
    }else if(x==1){
    	printf("Undefined command detected\nQuitting Virtual Machine...\n"); 
    }else if(x==3){
	printf("bad memory adress in PC\nQuitting Virtual Machine...\n");
    }else if(x==4){
	printf("Bad input of numbers \nQuitting Virtual Machine...\n");
    }else if(x==5){
	printf("No STRT detected\nQuitting Virtual Machine...\n");
    }else if(x==6){
	printf("No HALT detected\nQuitting Virtual Machine...\n");
    }else if(x==7){
	printf("0 in division\nQuitting Virtual Machine...\n");
    }
    //exit(1);

}


int main(int argc, char *argv[]){ 
  printf("Welcome\n");
  int ptr;
  page = allocate_Memory(&ptr);
  set_PTR(ptr); 
  set_MODE(0);
  show_Memory();
    show_Registers();
    
    printf("Change Mode y/n\n");
      char inp;
      scanf(" %c",&inp);
      getchar();
      if(inp != 'y'){exit(0);}
  
  openFile("programa1.txt");       

  printf("*****Starting Virtual Machine*****\n");                
    int end = 0;
    set_MODE(1);
    
    while (!end){
      show_Memory();
      show_Registers();
      int i = testInterrupt();
      if(i!=0) {intDetected(i);break;} 
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
    set_MODE(0);
    show_Memory();
    show_Registers();
    printf("Shutting down\n");
  	
  return 0;
}


