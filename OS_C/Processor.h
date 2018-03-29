#define TRUE 1
#define FALSE 0

static short PC = 0;              
static char C = FALSE;            
static long R = 0x30303030;       
long* page;
long memory[35][10];

short get_pc();
int nextCommand();
void show_Registers();
