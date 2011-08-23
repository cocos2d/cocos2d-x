all: main.cpp
	g++ -O3 -o simple_event -I../../../api/inc main.cpp ../../api/lib/libfmodevent.so -Wl,-rpath ../../../api/lib

run:
	./simple_event

clean:
	rm -f simple_event
