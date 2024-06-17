#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

struct{
    uint16_t a :15;
    uint32_t  b  :1;
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


typedef struct{
    uint16_t row,column;
}coordinates_t;


int matrix[100][100];
int vector[100],answer[100];

void * rowMul(void *data)
{
    coordinates_t *ptr = (coordinates_t *)data;
    vector[ptr->row] = 0;
    for (uint16_t i = 0; i < 100;i++)
    {
        answer[ptr->row] += vector[i] *  matrix[ptr->row][i];
    }
    printf("finished row %d\n",ptr->row);
    return NULL;
}




pthread_mutex_t mutex;

uint32_t counter = 0;

void * concurr1(void *_ptr)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        counter *= -1;
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    
}

void * concurr2(void *_ptr)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        counter++;
        printf("%d\n",counter);
        pthread_mutex_unlock(&mutex);
        
        usleep(100000);
    }
    
}

typedef struct{
    double x,y;
}POINT_T;

typedef struct{
    POINT_T p1,p2,p3;
}TRIANG_T;


#define ABS(x) ((x) > 0 ? (x) : (-(x)))

double maxDist3Points(double c1,double c2, double c3)
{
    double answer = ABS(c1 - c2);
    if (ABS(c1-c3) > answer)
    {
        answer = ABS(c1-c3);
    }
    if(ABS(c2-c3) > answer)
    {
        answer = ABS(c2-c3);
    }

    return answer;

}


double ptriang(const TRIANG_T * triang)
{
    return (maxDist3Points(triang->p1.x,triang->p2.x,triang->p3.x) * maxDist3Points(triang->p1.y,triang->p2.y,triang->p3.y) / 2);
}

int main(int argc, char **argv)
{

    TRIANG_T tri={.p1 = {0,0}, .p2 = {0,1},.p3 = {1,0}};
    printf("%lf\n",ptriang(&tri));
    
    return 0;
    
}