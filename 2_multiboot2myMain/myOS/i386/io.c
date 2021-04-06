/* 
 * IO 操作
 * 理解了outb函数后实现inb函数
 */
unsigned char inb(unsigned short int port_from){
    
}

void outb (unsigned short int port_to, unsigned char value){
    __asm__ __volatile__ ("outb %b0,%w1"::"a" (value),"Nd" (port_to));
}