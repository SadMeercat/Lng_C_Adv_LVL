CC = gcc
CFLAGS = -Wall -Wextra -pedantic -I"C:/MinGW/include"
LDFLAGS = -L"C:/MinGW/lib" -lpdcurses

OBJS = main.o drone_control.o ai_control.o draw.o input.o object_interaction.o

drone_program: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

main.o: main.c drone_control.h ai_control.h draw.h input.h object_interaction.h
	$(CC) $(CFLAGS) -c main.c -o main.o

drone_control.o: drone_control.c drone_control.h
	$(CC) $(CFLAGS) -c drone_control.c -o drone_control.o

ai_control.o: ai_control.c ai_control.h drone_control.h
	$(CC) $(CFLAGS) -c ai_control.c -o ai_control.o

draw.o: draw.c draw.h drone_control.h
	$(CC) $(CFLAGS) -c draw.c -o draw.o

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c -o input.o

object_interaction.o: object_interaction.c object_interaction.h drone_control.h
	$(CC) $(CFLAGS) -c object_interaction.c -o object_interaction.o

clean:
	rm -f $(OBJS) drone_program
