/*
 * 实现myPrint功能 先学习C语言的可变参数内容
 * 需要调用到格式化输出的function（vsprintf）
 */ 
extern void append2screen(char *str,int color);
extern void uart_put_chars(char *str);

char kBuf[400];
int myPrintk(int color,const char *format, ...){ 
}

char uBuf[400];
int myPrintf(int color,const char *format, ...){
}