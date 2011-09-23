all: main.cpp
	g++ -O3 -o programmer_selected -I../../../api/inc main.cpp ../../api/lib/libfmodevent.so -Wl,-rpath ../../../api/lib

run:
	./programmer_selected

clean:
	rm -f programmer_selected
