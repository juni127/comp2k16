#ifndef __SYSTEM_H
#define __SYSTEM_H

/* MAIN.C */
extern unsigned char *mem_cpy(unsigned char *dest, const unsigned char *src, int count);
extern unsigned char *mem_set(unsigned char *dest, unsigned char val, int count);
extern unsigned short *mem_setw(unsigned short *dest, unsigned short val, int count);
extern int strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

/* SCRN.C */
extern void cls();
extern void putch(unsigned char c);
extern void puts(unsigned char *str);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void init_video();

#endif
