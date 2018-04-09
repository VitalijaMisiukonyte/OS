#define TRUE 1
#define FALSE 0


long* page;
long memory[33][10];

short get_pc();

void set_PTR(int value);
int get_PTR();

void set_PI(int value);
int get_PI();

void set_MODE(int value);
int get_MODE();

int nextCommand();
int testInterrupt();
void show_Registers();
void set_program_name(char* name, int block);
void set_memory(int i, int j, char* buffer);
