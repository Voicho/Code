main: main.o function.o info.o
	gcc -o main main.o function.o info.o
	make clean
	./main

main.o: main.c function.h info.h
	gcc -c main.c

function.o: function.c function.h info.h
	gcc -c function.c

info.o: info.c info.h
	gcc -c info.c

clean: 
	del function.o info.o main.o
	