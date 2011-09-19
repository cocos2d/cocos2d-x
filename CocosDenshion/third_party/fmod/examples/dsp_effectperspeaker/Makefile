dsp_effectperspeaker_cpp:	main.cpp
	g++ -O3 -o dsp_effectperspeaker main.cpp ../../api/lib/libfmodex.so -pthread

dsp_effectperspeaker_c:	main.c
	g++ -O3 -o dsp_effectperspeaker main.c ../../api/lib/libfmodex.so -pthread

run:
	./dsp_effectperspeaker

clean:
	rm -f dsp_effectperspeaker
