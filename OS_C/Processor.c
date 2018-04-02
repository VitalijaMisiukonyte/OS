#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Processor.h"
#include "HardDisk.h"

#define number 16

char commands[number][2] = { 
 { 'L', 'R' },//Reiksmes issaugojimas registre R
 { 'S', 'R' },//Registro R reiksmes irasymas i atminti
 { 'A', 'D' },//Sudetis (registras + memory) 
 { 'S', 'U' },//Atimtis (registras - memory)
 { 'M', 'U' },//Daugyba (registras * memory)
 { 'C', 'R' },//Palygina registra R su atminties reiksme ir nustato SF
 { 'J', 'P' },//Valdymo perdavimas PC = 10x+y
 { 'J', 'M' },//Jei SF flag'as M=1 perduoda valdyma PC = 10x+y
 { 'J', 'L' },//Jei SF flag'as L=1 perduoda valdyma PC = 10x+y
 { 'J', 'E' },//Jei SF flag'as E=1 perduoda valdyma PC = 10x+y
 { 'P', 'R' },//Isveda duomenis
 { 'I', 'N' },//Skaito duomenis is isores
 { 'D', 'V' },//Dalyba
 { 'M', 'D' },//Moduline dalyba
 { 'H', 'A' }, //Halt - sustojimo komanda
 { 'G', 'O' }
};  
enum { LR = 0, SR, AD, SU, MU, CR, JP, JM, JL, JE, PR, IN, DV, MD, HA, GO };

static short PC = 0;              
static char C = FALSE;
static long SF = 0x30303030;            
static long R = 0x30303030; 
int block_PC;
int field_PC;

long addition(long);
long substraction(long);
long multiplication(long);
void read_data(int, int);
void executeCommand();
void showData(int, int);
long division(long);
long modular(long);
void go();

short get_pc(){
  return PC; 
}
void set_pc(int a){
  PC = a; 
}
//executeCommand - komandos,nuskaitytos is atminties vykdymas
void executeCommand(char* cmd){
  int i = 0;
  int m = 0;
  //Esamu ir nuskaitytu komandu palyginimas
  while ((i < number) && !m) { 
    if (compare_Commands(cmd, commands[i], 2)) m = 1;
    i++;
  }
  //
  if (i > number-1) { 
    //printf("Undefined command: %c%c%c%c.\nQuitting Virtual Machine...\n", cmd[0], cmd[1], cmd[2], cmd[3]); 
    //exit(1);
    printf("Value: %c%c%c%c\n", cmd[0], cmd[1], cmd[2], cmd[3]);     
  }
  
  //char - 48
  int block; 
  int field;
  //char - 48
  if(cmd[2] == 'P' && cmd[3] == 'C'){
	block = block_PC;
	field = field_PC;
  }else{
	block = cmd[2] - 48;
	field = cmd[3] - 48;
  }
  
  //Komandu vykdymas
  switch (--i){ 
    case LR: R = memory[block][field];
	           break;
    case AD: R = addition(memory[page[block]-1][field]);
	           break;
    case SU: R = substraction(memory[page[block]-1][field]);
	           break;
    case MU: R = multiplication(memory[page[block]-1][field]);
	           break;
    case JP: PC = block*10 + field;
	           break;
    case IN: read_data(block, 0);
	           break;
    case CR: if (R > memory[page[block]-1][field]){
                SF = SF + 0x00010000;
             } else if (R < memory[page[block]-1][field]){
                SF = SF + 0x00000100;
             } else SF = SF + 0x00000001;;
	           break;
    case JM: if (SF & 0x00010000){
              PC = block*10 + field;
            }
             break;
    case JL: if (SF & 0x00000100){
              PC = block*10 + field;
            }
             break;
    case JE: if (SF & 0x00000001){
              PC = block*10 + field;
            }
             break;
    case PR: showData(block, field);
	           break;
    case SR: memory[page[block]-1][field] = R;
	           break;
    case DV: R = division(memory[page[block]-1][field]);
		   break;
    case MD: R = modular(memory[page[block]-1][field]);
		   break;
   case GO: go(block, field); PC= PC + 1;break;
  }
}
//Registru turiniu isvedimas i ekrana
void show_Registers() {
  printf("\n*******************************************************\n");
  printf("Registrers: \n");
  if (PC > 10) printf("   PC: %d\n", PC);
  else printf("   PC: 0%d\n", PC);
  printf("   R:  %c%c%c%c\n", (int)(R & 0xFF000000) / 0x1000000, (int)(R & 0xFF0000) / 0x10000, (int)(R & 0xFF00) / 0x100, (int)(R & 0xFF));
  printf("   C:  %d\n", C);
  printf("   SF: %c%c%c%c\n", (int)(SF & 0xFF000000) / 0x1000000, (int)(SF & 0xFF0000) / 0x10000, (int)(SF & 0xFF00) / 0x100, (int)(SF & 0xFF));
  printf("\n");
  printf("\n*******************************************************\n");
}

void go(int block, int word){


      char data[4] = { (memory[PC/10][PC%10] & 0xFF000000) / 0x1000000, (memory[PC/10][PC%10] & 0xFF0000) / 0x10000, 
                       (memory[PC/10][PC%10] & 0xFF00) / 0x100, (memory[PC/10][PC%10] & 0xFF) };

 
	printf(">>>>>>%ld %d\n",block, word);
      if ((block <= 9) && (block >= 0)){
	
	 //printf(">>>>>>%c %c %c %c\n",data[0],data[1],data[2],data[3]);
	//printf(">>>>>>%ld %d\n",PC/10, PC%10);
	//printf(">>>>>>%d\n",command[0]*0x1000000+command[1]*0x10000+command[2]*0x100+command[3]);
	
        memory[block][word] = data[0]*0x1000000+data[1]*0x10000+data[2]*0x100+data[3];
	//set_pc(block*10 + word);
/*        word++;*/
/*        if (word > 9){*/
/*          block++;*/
/*          word = 0;*/
/*        }*/
      }
      else{
        printf("Command %c%c%c%c caused overflow\nEnd of VM\n", data[0], data[1], data[2], data[3]);
        exit(1);        
      }
    
    



}
//Duomenu apsikeitimas su isore (vyksta blokais)
void read_data(int a, int b){
  char* character = calloc(sizeof(char), 41);
  
  fgets(character, 40, stdin);
 
  int i;
  for (i = 0; i < 40; i++) {
    //Naujos eilutes simboliu pasalinimas
    if (character[i] == '\n') {
      character[i] = 0;
      int j;
      //Tarpo uzpildymas simboliais
      for (j = 0; j < (i%4)-1; j++) character[i+j] = ' ';  
    }
  }

  //Nuskaitytu duomenu sudejimas i bloka
  for (i = 0; i < 10; i++){  
    memory[page[a]-1][b+i] = character[0+(4*i)]*0x1000000+character[1+(4*i)]*0x10000+character[2+(4*i)]*0x100+character[3+(4*i)];
  } 
}

//Komandos nuskaitymas is atminties, skaitliuko didinimas
int nextCommand() 
{
  char command[4] = { (memory[PC/10][PC%10] & 0xFF000000) / 0x1000000, (memory[PC/10][PC%10] & 0xFF0000) / 0x10000, 
                       (memory[PC/10][PC%10] & 0xFF00) / 0x100, (memory[PC/10][PC%10] & 0xFF) };
  PC++;
  
  //Halt komanda
  if (!compare_Commands(commands[HA], command, 2)){
    executeCommand(command);
    return 1;
  } 
  else return 0; 
}

//Duomenu isvedimas i ekrana
void showData(int a, int b){
  int i, j;
  for (i = 0; i < 10; i++) { 
    if (memory[page[a]-1][b+i] != 0){
      char data[4] = { (memory[a][b+i] & 0xFF000000) / 0x1000000, (memory[a][b+i] & 0xFF0000) / 0x10000, 
                       (memory[a][b+i] & 0xFF00) / 0x100, (memory[a][b+i] & 0xFF) };
      
      for (j = 0; j < 4; j++) printf("%c", data[j]);
    }                         
  }
  printf("\n");
}

//Registras + atminties adresas
long addition(long adr){
  
  char value1[4] = { (adr & 0xFF000000) / 0x1000000, (adr & 0xFF0000) / 0x10000, (adr & 0xFF00) / 0x100, adr & 0xFF };
  char value2[4] = { (R & 0xFF000000) / 0x1000000, (R & 0xFF0000) / 0x10000, (R & 0xFF00) / 0x100, R & 0xFF };  
  
  //Gaunami desimtainiai skaiciai
  int get_value_1 = (value1[0]-48)*1000 + (value1[1]-48)*100 + (value1[2]-48)*10 + value1[3]-48;
  int get_value_2 = (value2[0]-48)*1000 + (value2[1]-48)*100 + (value2[2]-48)*10 + value2[3]-48;
  int total_sum = get_value_1 + get_value_2;
  
  if (total_sum > 9999){
    printf("Bad sum of input numbers - more than 4 bytes\nQuitting Virtual Machine...\n");
    exit(1);
  }
  int sum1 = total_sum/1000;
  int sum2 = (total_sum%1000)/100;
  int sum3 = (total_sum%100)/10;
  int sum4 = total_sum%10;   
  sum1 = sum1 + 48;
  sum2 = sum2 + 48; 
  sum3 = sum3 + 48; 
  sum4 = sum4 + 48;
  
  return (sum1 * 0x1000000 + sum2 * 0x10000 + sum3 * 0x100 + sum4);
}

//substraction: registras - atmintis su adresu
long substraction(long adr){ 
   
  char line1[4] = { (adr & 0xFF000000) / 0x1000000, (adr & 0xFF0000) / 0x10000, (adr & 0xFF00) / 0x100, adr & 0xFF };
  char line2[4] = { (R & 0xFF000000) / 0x1000000, (R & 0xFF0000) / 0x10000, (R & 0xFF00) / 0x100, R & 0xFF }; 
  
  int nr_1 = (line1[0]-48)*1000 + (line1[1]-48)*100 + (line1[2]-48)*10 + line1[3]-48;
  int nr_2 = (line2[0]-48)*1000 + (line2[1]-48)*100 + (line2[2]-48)*10 + line2[3]-48;
  int substract = nr_1 - nr_2;
  
  if (substract < 0){
    printf("Bad input of data\n");
    exit(1);
  }
  
  int minus1 = substract/1000;
  int minus2 = (substract%1000)/100;
  int minus3 = (substract%100)/10;
  int minus4 = substract%10;
  
  minus1 = minus1 + 48;
  minus2 = minus2 + 48;
  minus3 = minus3 + 48;
  minus4 = minus4 + 48;
  
  long result = minus1 * 0x1000000 + minus2 * 0x10000 + minus3 * 0x100 + minus4;
  return result;
}

long multiplication(long adr){ 
   
  char line1[4] = { (adr & 0xFF000000) / 0x1000000, (adr & 0xFF0000) / 0x10000, (adr & 0xFF00) / 0x100, adr & 0xFF };
  char line2[4] = { (R & 0xFF000000) / 0x1000000, (R & 0xFF0000) / 0x10000, (R & 0xFF00) / 0x100, R & 0xFF }; 
  
  int nr_1 = (line1[0]-48)*1000 + (line1[1]-48)*100 + (line1[2]-48)*10 + line1[3]-48;
  int nr_2 = (line2[0]-48)*1000 + (line2[1]-48)*100 + (line2[2]-48)*10 + line2[3]-48;
  int multiplication = nr_1 * nr_2;
  
  if ((nr_1 < 0) || (nr_1 < 0) || (multiplication > 9999)){
    printf("Bad input of numbers\n");
    exit(1);
  }
  else{
    int mul1 = multiplication/1000;
    int mul2 = (multiplication%1000)/100;
    int mul3 = (multiplication%100)/10;
    int mul4 = multiplication%10;
    
    mul1 = mul1 + 48;
    mul2 = mul2 + 48;
    mul3 = mul3 + 48;
    mul4 = mul4 + 48;
    
    long result = mul1 * 0x1000000 + mul2 * 0x10000 + mul3 * 0x100 + mul4;
    return result;
  }
}
long division(long adr){ 
   
  char line1[4] = { (adr & 0xFF000000) / 0x1000000, (adr & 0xFF0000) / 0x10000, (adr & 0xFF00) / 0x100, adr & 0xFF };
  char line2[4] = { (R & 0xFF000000) / 0x1000000, (R & 0xFF0000) / 0x10000, (R & 0xFF00) / 0x100, R & 0xFF }; 
  
  int nr_1 = (line1[0]-48)*1000 + (line1[1]-48)*100 + (line1[2]-48)*10 + line1[3]-48;
  int nr_2 = (line2[0]-48)*1000 + (line2[1]-48)*100 + (line2[2]-48)*10 + line2[3]-48;
  int division = nr_1 / nr_2;
  
  if ((nr_1 < 0) || (nr_1 < 0) || (division > 9999)){
    printf("Bad input of numbers\n");
    exit(1);
  }
  else{
    int div1 = division/1000;
    int div2 = (division%1000)/100;
    int div3 = (division%100)/10;
    int div4 = division%10;
    
    div1 = div1 + 48;
    div2 = div2 + 48;
    div3 = div3 + 48;
    div4 = div4 + 48;
    
    long result = div1 * 0x1000000 + div2 * 0x10000 + div3 * 0x100 + div4;
    return result;
  }
}

long modular(long adr){ 
   
  char line1[4] = { (adr & 0xFF000000) / 0x1000000, (adr & 0xFF0000) / 0x10000, (adr & 0xFF00) / 0x100, adr & 0xFF };
  char line2[4] = { (R & 0xFF000000) / 0x1000000, (R & 0xFF0000) / 0x10000, (R & 0xFF00) / 0x100, R & 0xFF }; 
  
  int nr_1 = (line1[0]-48)*1000 + (line1[1]-48)*100 + (line1[2]-48)*10 + line1[3]-48;
  int nr_2 = (line2[0]-48)*1000 + (line2[1]-48)*100 + (line2[2]-48)*10 + line2[3]-48;
  int module = nr_1 % nr_2;
  
  if ((nr_1 < 0) || (nr_1 < 0) || (module > 9999)){
    printf("Bad input of numbers\n");
    exit(1);
  }
  else{
    int mod1 = module/1000;
    int mod2 = (module%1000)/100;
    int mod3 = (module%100)/10;
    int mod4 = module%10;
    
    mod1 = mod1 + 48;
    mod2 = mod2 + 48;
    mod3 = mod3 + 48;
    mod4 = mod4 + 48;
    
    long result = mod1 * 0x1000000 + mod2 * 0x10000 + mod3 * 0x100 + mod4;
    return result;
  }
}

// Puslapiu lentejei, iraso programos varda
void set_program_name(char* name, int block){
  int paging_adr = 30;
  while (memory[paging_adr][0] != block) 
    if(paging_adr < 33)
      paging_adr++;
    else{
      printf("Can't set name\n");
      exit(EXIT_FAILURE);
    }

  for (int i = 0,j = 6; i < strlen(name); i += 4){
   set_memory(paging_adr, j, name + i);
   j++; 
  }
}

void set_memory(int i, int j, char* buffer){
  memory[i][j] =   buffer[0] * 0x1000000
                 + buffer[1] * 0x10000
                 + buffer[2] * 0x100
                 + buffer[3] * 0x1;
}
