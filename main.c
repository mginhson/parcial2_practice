#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

struct{
    uint16_t a :15;
    uint8_t  b  :1;
}myvar;

void rawPrintLiteral(size_t num, uint16_t size_in_bytes)
{
    
    uint8_t * ptr = (uint8_t*)&num; //endiannes independent
    uint16_t i,j;
    for (i = 0; i < size_in_bytes; i++,++ptr)
    {
        
        printf("%p -> %#x ",ptr,*ptr);    
        j = 7;

        do{
            (1<<j) & (*ptr) ? printf("1") : printf("0");
        }while(j-- != 0);

        printf("\n");

    }


    printf("\n");

    return;
}

void rawPrint(const void *_ptr, uint16_t size_in_bytes)
{
    
    const uint8_t * ptr = (uint8_t*)_ptr; //endiannes independent
    uint16_t i,j;
    for (i = 0; i < size_in_bytes; ++i,++ptr)
    {
        
        printf("%p -> %#x ",ptr,(uint8_t)*ptr);    
        j = 7;

        do{
            (1<<j) & (*ptr) ? printf("1") : printf("0");
        }while(j-- != 0);

        printf("\n");

    }


    printf("\n");

    return;
}


int main(int argc, char **argv)
{
    myvar.a = 0xABC;
    myvar.b = 1;
    rawPrintLiteral(0x12345678,sizeof(int));
    rawPrint(&myvar,sizeof(myvar));
}