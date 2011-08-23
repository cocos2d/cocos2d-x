all: main.cpp
	g++ -O3 -o programmer_sound -I../../../api/inc main.cpp ../../api/lib/libfmodevent.so -Wl,-rpath ../../../api/lib

run:
	./programmer_sound

clean:
	rm -f programmer_sound
