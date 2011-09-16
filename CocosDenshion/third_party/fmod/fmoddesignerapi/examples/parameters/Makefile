all: main.cpp
	g++ -O3 -o parameters -I../../../api/inc main.cpp ../../api/lib/libfmodevent.so -Wl,-rpath ../../../api/lib

run:
	./parameters

clean:
	rm -f parameters
