CC     = gcc
CCLINK = $(CC)
CFLAGS = -Wall -g -std=c99
OBJS   = ransom.o
EXEC   = prog.exe
RM     = rm -rf *.o *.exe

prog.exe: $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)
	
ransom.o: ransom.c
	$(CC) $(CFLAGS) -c ransom.c

clean:
	$(RM)