/*
 * 本文件实现vga的相关功能，清屏和屏幕输出
 * clear_screen和append2screen必须按照如下借口实现
 * 可以增加其他函数供clear_screen和append2screen调用
 */
extern void outb (unsigned short int port_to, unsigned char value);
extern unsigned char inb(unsigned short int port_from);

#define vga_base 0xB8000//vga初始地址
#define vga_size 0x1000//vga大小
#define index_port 0x3d4//索引端口     通过索引端口指定要读写的寄存器 然后通过数据端口读写
#define data_port 0x3d5//数据端口
#define buffer_width 80//缓冲区宽度
#define buffer_height 25//缓冲区高度

int cursor_pos;
 int cursor_x ;
 int cursor_y ;
char *   VGABASE;
void set_cursor(int x,int y){
    int  pos = y*buffer_width + x;
  	outb(index_port, 0xe);
	outb(data_port, (pos >> 8) & 0xff);//写光标的行位置
	outb(index_port, 0xf);
	outb(data_port, pos & 0xff);// 写光标的列位置
	cursor_x = x;
	cursor_y = y;
}

void ScrollUp() {  //实现滚屏一行
    for(int line = 0 ;line<buffer_height;line++)
        for(int  i = 0 ;i<buffer_width*2;i++)
            *(VGABASE+line*buffer_width*2+i) = *(VGABASE+(line+1)*buffer_width*2+i);
    
    cursor_y = 24;   


}


void putchar(unsigned char c,int color){
    switch(c){
        case '\r':
        case '\n':
                cursor_x = 0;
                cursor_y++;
                break;
        case '\t':
                cursor_x+=4;
                if(cursor_x>=buffer_width){
                    cursor_x -= buffer_width;
                    cursor_y++;
                }
                break;
            default:
            {
                int pos =  cursor_y*buffer_width + cursor_x;
                *(VGABASE+pos*2) = c;   
                *(VGABASE+pos*2+1) = color;
                pos++;
                cursor_x = pos%buffer_width;
                cursor_y = pos/buffer_width;

            }
            break;

    }
    if(cursor_y == buffer_height)   ScrollUp();
    set_cursor(cursor_x,cursor_y);

}


void clear_screen(void) {	

     VGABASE = (char*)vga_base;

      for(int line = 0 ;line<buffer_height;line++)
        for(int  i = 0 ;i<buffer_width;i++)
        putchar(' ',0);
    
    cursor_x = 0;
    cursor_y = 0;
    set_cursor(cursor_x,cursor_y);

}



void append2screen(char *str,int color){ 
    for (int i = 0; str[i] != '\0'; i++) {
		putchar(str[i], color);
	}
}