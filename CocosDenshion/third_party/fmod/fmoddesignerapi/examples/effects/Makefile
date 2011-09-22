all: main.cpp
	g++ -O3 -o effects -I../../../api/inc main.cpp ../../api/lib/libfmodevent.so -Wl,-rpath ../../../api/lib

run:
	./effects

clean:
	rm -f effects
