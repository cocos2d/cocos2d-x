all: main.cpp
	g++ -O3 -o realtime_tweaking -I../../../api/inc main.cpp ../../api/lib/libfmodeventnet.so -Wl,-rpath ../../../api/lib -Wl,-rpath ../../api/lib

run:
	./realtime_tweaking

clean:
	rm -f realtime_tweaking
