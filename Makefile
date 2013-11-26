CCFLAGS = -Wall -pedantic -ansi -g -l pthread
CC = gcc

all: Queue.o customer.o customerDB.o main.o radix.o prefixTree.o pa5

pa5: main.o Queue.o customer.o customerDB.o radix.o prefixTree.o linkedList.o producer.o ThreadLL.o book.o
	${CC} ${CCFLAGS} -o pa5 main.o customer.o customerDB.o Queue.o radix.o prefixTree.o linkedList.o producer.o ThreadLL.o book.o

main.o: main.c
	${CC} ${CCFLAGS} -c main.c

producer.o: producer.c
	${CC} ${CCFLAGS} -c producer.c

book.o: book.c
	${CC} ${CCFLAGS} -c book.c


linkedList.o: linkedList.c
	${CC} ${CCFLAGS} -c linkedList.c

customer.o: customer.c
	${CC} ${CCFLAGS} -c customer.c

customerDB.o: customerDB.c
	${CC} ${CCFLAGS} -c customerDB.c

ThreadLL.o: ThreadLL.c
	${CC} ${CCFLAGS} -c ThreadLL.c

radix.o: radix.c
	${CC} ${CCFLAGS} -c radix.c

prefixTree.o: prefixTree.c
	${CC} ${CCFLAGS} -c prefixTree.c

Queue.o: Queue.c
	${CC} ${CCFLAGS} -c Queue.c

clean:
	rm -f *.o *.gch pa5
