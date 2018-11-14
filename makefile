CC = g++
CFLAGS = -g -c -Wall -std=c++0x 
OBJS = main.o Tester.o Resolve.o SymbolList.o FileHandler.o

.C.o:
	$(CC) $(CFLAGS) $< -o $@

resolve: $(OBJS)
	$(CC) $(OBJS) -o resolve

tester: $(OBJS)
	$(CC) $(OBJS) -o tester

Resolve.o: SymbolList.h FileHandler.h Resolve.h

Tester.o: SymbolList.h FileHandler.h Tester.h

FileHandler.o: SymbolList.h FileHandler.h

SymbolList.o: SymbolList.h

main.o: SymbolList.h Resolve.h FileHandler.h

clean:
	rm *.o resolve

submit:
	make clean
	submit efb 3482-lab5 *.C *.h makefile
