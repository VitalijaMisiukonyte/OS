#define TRUE 1
#define FALSE 0

static short PC = 0;              
static char C = FALSE;            
static long R = 0x30303030;       
long* psl;
long atmintis[35][10];

short get_pc();
int sekanti_komanda();
void rodyti_registrus();
