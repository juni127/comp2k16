#include < system.h >

/* You will need to code these up yourself!  */
unsigned char *mem_cpy(unsigned char *dest, const unsigned char *src, int count){
	// Copy 'count' bytes of data from 'src' to 'dest', finally return 'dest'.
	int x;
	for(x = 0; x < count; x++)
		*(dest+x) = *(src+x);
	return dest;
}

unsigned char *mem_set(unsigned char *dest, unsigned char val, int count){
    // Set 'count' bytes in 'dest' to 'val'. Again, return 'dest'.
	int x;
	for(x = 0; x < count; x++)
		*(dest+x) = val;
	return dest;
}

unsigned short *mem_set_w(unsigned short *dest, unsigned short val, int count){
    // Set 'count' bytes in 'dest' to 'val'. Again, return 'dest'. BUT WITH 16BITS
	int x;
	for(x = 0; x < count; x++)
		*(dest+x) = val;
	return dest;
}

int strlen(const char *str){
	// Return string size
    int size;
	for(size = 0; *(str+size) != '\0'; size++);
	return size;
}

/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

/* This is a very simple main() function. All it does is sit in an
*  infinite loop. This will be like our 'idle' loop */
void main()
{
    /* You would add commands after here */

    /* ...and leave this loop in. There is an endless loop in
    *  'start.asm' also, if you accidentally delete this next line */
    for (;;);
}
