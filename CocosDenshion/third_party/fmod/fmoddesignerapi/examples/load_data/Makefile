all: main.cpp
	g++ -O3 -o load_data -I../../../api/inc main.cpp ../../api/lib/libfmodevent.so -Wl,-rpath ../../../api/lib

run:
	./load_data

clean:
	rm -f load_data
