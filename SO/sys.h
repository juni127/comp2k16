#define MEM_LENGHT 65500

//Espaço do buffer de E/S
#define BUFFER_START 0
#define BUFFER_END 1013

//Espaço de dispositivos de E/S
#define ES_START 1014
#define ES_END 1023

unsigned char MEM[MEM_LENGHT];
unsigned char ES_STATUS_REG[ES_END - ES_START];

//GRUPO 4 - Memoria virtual: mecanismo de paginação
void mem_cpy(unsigned int f, unsigned int s, unsigned int t);

//GRUPO 5 e 6 - Algoritmos de substituição FIFO, MRU, LRU e MFU
void fifo(unsigned int addr);
void mru(unsigned int addr);
void lru(unsigned int addr);
void mfu(unsigned int addr);

// GRUPO 9 - E/S programada
void p_input(unsigned int f, unsigned int s, unsigned int t);
void p_output(unsigned int f, unsigned int s, unsigned int t);

// GRUPO 10 - E/S por interrupção
void i_input(unsigned int f, unsigned int s, unsigned int t);
void i_output(unsigned int f, unsigned int s, unsigned int t);