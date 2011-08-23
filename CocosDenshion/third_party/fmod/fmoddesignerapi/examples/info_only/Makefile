all: main.cpp
	g++ -O3 -o info_only -I../../../api/inc main.cpp ../../api/lib/libfmodevent.so -Wl,-rpath ../../../api/lib

run:
	./info_only

clean:
	rm -f info_only
