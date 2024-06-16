CC := gcc
CFLAGS := -Wall
OBJECT_FILES := main.o my_threads.o
EXECUTABLE_NAME := prog

${EXECUTABLE_NAME}: ${OBJECT_FILES}
	${CC} -o ${EXECUTABLE_NAME} ${OBJECT_FILES} ${CFLAGS}

all: ${OBJECT_FILES}
	${CC} -o ${EXECUTABLE_NAME} ${OBJECT_FILES} ${CFLAGS}


main.o: main.c my_threads.h
	${CC} -c main.c ${CFLAGS}

my_threads.o: my_threads.c my_threads.h
	${CC} -c my_threads.c ${CFLAGS}
clean:
	rm -f *.o ${EXECUTABLE_NAME}