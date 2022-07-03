CC=g++ -Wall
CFLAGS=-c
OBJS=usbEvList.o
PROGS=tester gamepad

all: lib tester gamepad

gamepad: findGamepad.cpp usbEvList.o
	$(CC) $(OBJS) findGamepad.cpp -o gamepad 

tester: testMain.cpp usbEvList.o
	$(CC) $(OBJS) testMain.cpp -o tester

lib:
	$(CC) $(CFLAGS) usbEvList.cpp -o usbEvList.o

.PHONY: clean
clean:
	-rm $(OBJS)
	-rm $(PROGS)