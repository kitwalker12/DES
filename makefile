CC = g++
CFLAGS = -Wall -g

hw5 : hw5.o tablecheck.o encrypt.o encrypt3.o
	${CC} ${CFLAGS} hw5.o tablecheck.o encrypt.o encrypt3.o -o hw5

hw5.o: hw5.cpp
	${CC} ${CFLAGS} -c hw5.cpp

tablecheck.o: tablecheck.cpp tablecheck.h
	${CC} ${CFLAGS} -c tablecheck.cpp

encrypt.o: encrypt.cpp encrypt.h tablecheck.o
	${CC} ${CFLAGS} -c encrypt.cpp

encrypt3.o: encrypt3.cpp encrypt3.h encrypt.o tablecheck.o
	${CC} ${CFLAGS} -c encrypt3.cpp

clean:
	rm -rf *.o hw5

