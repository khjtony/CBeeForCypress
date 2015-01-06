all: CBeeTest

CBeeTest: CBeeTest.o CBeeArduinoLib.o
	gcc CBeeTest.o CBeeArduinoLib.o -o CBeeTest

CBeeTest.o: CBeeTest.c
	gcc -c CBeeTest.c

CBeeArduinoLib.o: CBeeArduinoLib.h CBeeArduinoLib.c
	gcc -c CBeeArduinoLib.c


clean:
	rm -rf *o CBeeTest