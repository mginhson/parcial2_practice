/* TEST OF THREADS */

//Compile  gcc -o th2 th2.c -lpthread

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


#define  ONE_MS    	1000	   // One mseg
#define  time_delay(x)  (x/100)    // x in ms , minvalue 100mseg



// ============ Colored Text ===========

#define BLACK_TEXT		   "\e[30;1m"
#define RED_TEXT		   "\e[31;1m"
#define GREEN_TEXT 		   "\e[32;1m"
#define YELLOW_TEXT 	   "\e[33;1m"
#define BLUE_TEXT 		   "\e[34;1m"
#define MAGENTA_TEXT 	   "\e[35;1m"
#define CYAN_TEXT 	   	   "\e[36;1m"
#define WHITE_TEXT 		   "\e[37m"

// ============ Colored Text End ===========

	
//http://linuxprograms.wordpress.com/2007/12/29/threads-programming-in-linux-examples/


enum{
    WAITING,
    TIMEOUT,

}status_t = WAITING;

unsigned int timerTick;

void * th1(void *ptr)
{
    while(1)
    {
        usleep(ONE_MS * 100);
        if(timerTick)
            timerTick--;     
    }
}

void * th2(void * ptr)
{
    static int r=0;
    while(1)
    {
        if(!timerTick)
        {
            timerTick = time_delay(500);
            printf("r = %d\n",r++);
            
        }
    }
}

int main(int argc, char **argv)
{
    pthread_t thread1,thread2,thread3;
    srand(time(NULL));
    pthread_create(&thread1,NULL,th1,NULL);
    pthread_create(&thread2,NULL,th2,NULL);
    
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    return 0;
}