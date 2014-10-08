#define O2 9
#define CS 11
#define RS 10
#define RW 12

#define D0 3
#define D1 4
#define D2 5
#define D3 6

#define IRQ 8

void mt8880_init();
char mt8880_read(bool rs = false);
void mt8880_write(char data, bool rs = false);
