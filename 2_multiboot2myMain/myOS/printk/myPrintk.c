/*
 * 实现myPrint功能 先学习C语言的可变参数内容
 * 需要调用到格式化输出的function（vsprintf）
 */ 
#include  <stdarg.h>
extern int vsprintf(char *buf, const char *fmt, va_list args);
extern void append2screen(char *str,int color);
extern void uart_put_chars(char *str);

char kBuf[400];
int myPrintk(int color,const char *format, ...){ 
    va_list ap;
    va_start(ap,format);
    vsprintf(kBuf,format,ap);   //格式化字符串处理
    append2screen(kBuf,color);
    uart_put_chars(kBuf);   //串口输出
    va_end(ap);

}

char uBuf[400];
int myPrintf(int color,const char *format, ...){
     va_list ap;
    va_start(ap,format);
    vsprintf(uBuf,format,ap);   //格式化字符串处理
     append2screen(kBuf,color);
    uart_put_chars(uBuf);   //串口输出
    va_end(ap);
}