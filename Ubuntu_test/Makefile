exefile : Draw.o test.o
	gcc -o exefile Draw.o test.o

Draw.o : Draw.cpp
	gcc -c -o Draw.o Draw.cpp

test.o : test.cpp
	gcc -c -o test.o test.cpp

clean:
	rm *.o exefile 
