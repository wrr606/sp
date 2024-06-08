#include<stdio.h>
#include<string.h>
#include<stdarg.h>

void _print_string(const char *s){
    while(*s)
        putc(*s++, stdout);
}

void _print_int(int n){
    if(n<0)
        putc('-', stdout), n*=-1;
    char t[10]={'0'};
    int length=(n==0?1:0);
    while(n){
        t[length++]=n%10+'0';
        n/=10;
    }
    for(int i=length-1;i>=0;i--)
        putc(t[i], stdout);
}

void _print_float(double n){
    if(n<0)
        putc('-', stdout), n*=-1;
    _print_int((int)n), putc('.', stdout), n-=(int)n;
    for(int i=0;i<6;i++){
        n=(n-(int)n)*10;
        putc((int)n+'0', stdout);
    }
}

void _print_pointer(void *ptr) {
    uintptr_t addr = (uintptr_t)ptr;
    char buffer[16];
    int i = 0;
    while(addr>0){
        int digit=addr%16;
        if (digit<10)
            buffer[i++]='0'+digit;
        else
            buffer[i++]='a'+(digit-10);
        addr/=16;
    }
    for(int j=i;j<16;j++)
        putc('0', stdout);
    while(i>0)
        putc(buffer[--i], stdout);
}

void print(const char *txt, ...){
    va_list args;
    va_start(args, txt);

    while(*txt){
        if(*txt == '%'){
            ++txt;
            switch (*txt){
                case '%':
                    putc('%', stdout);
                    break;
                case 'd':
                    _print_int(va_arg(args, int));
                    break;
                case 'f':
                    _print_float(va_arg(args, double));
                    break;
                case 'c':
                    putc((char)va_arg(args, int), stdout);
                    break;
                case 's':
                    _print_string(va_arg(args, const char*));
                    break;
                case 'p':
                    _print_pointer(va_arg(args, const char*));
                    break;
                default:
                    putc('%', stdout), putc(*txt, stdout);
                    break;
            }
        }
        else
            putc(*txt, stdout);
        ++txt;
    }

    va_end(args);
}

int main(){
    printf("TEST:\n");
    print("It is my print:\t%d\n",999);
    printf("It is printf:\t%d\n",999);
    print("It is my print:\t%f\n",123.456);
    printf("It is printf:\t%f\n",123.456);
    print("It is my print:\t%c\n",'z');
    printf("It is printf:\t%c\n",'z');
    print("It is my print:\t%s\n","abcdefg");
    printf("It is printf:\t%s\n","abcdefg");
    char* x="1245";
    print("It is my print:\t%p\n",x);
    printf("It is printf:\t%p\n",x);
    print("It is my print:\t%%\n");
    printf("It is printf:\t%%\n");
    print("It is my print:\t%z\n");
    printf("It is printf:\t%z\n");
}