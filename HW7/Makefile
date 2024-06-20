TARGET=drone

ARGS=-lncursesw -lm

all: $(TARGET).exe
	./$(TARGET).exe

$(TARGET).exe: $(TARGET).o ai.o checks.o colors.o help.o inits.o maps.o menu.o moves.o prints.o queue.o 
	gcc -o $(TARGET).exe $(TARGET).o  ai.o checks.o colors.o help.o inits.o maps.o menu.o moves.o prints.o queue.o $(ARGS)

ai.o: ai.c
	gcc -c ai.c -o ai.o

checks.o: checks.c 
	gcc -c checks.c -o checks.o 
	
colors.o: colors.c  
	gcc -c colors.c -o colors.o

help.o: help.c 
	gcc -c help.c -o help.o 

inits.o: inits.c 
	gcc -c inits.c -o inits.o 

maps.o: maps.c 
	gcc -c maps.c -o maps.o 

menu.o: menu.c 
	gcc -c menu.c -o menu.o 

moves.o: moves.c 
	gcc -c moves.c -o moves.o 
	
prints.o: prints.c 
	gcc -c prints.c -o prints.o 

quue.o: quue.c 
	gcc -c quue.c -o quue.o 

$(TARGET).o: $(TARGET).c  
	gcc -c $(TARGET).c -o $(TARGET).o

clean:
	rm -fr *.o $(TARGET).exe


