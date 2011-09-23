all: main.cpp
	g++ -O3 -o max_playbacks -I../../../api/inc main.cpp ../../api/lib/libfmodevent.so -Wl,-rpath ../../../api/lib

run:
	./max_playbacks

clean:
	rm -f max_playbacks
