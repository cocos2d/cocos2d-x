dsp_custom_cpp:	main.cpp
	g++ -O3 -o dsp_custom main.cpp ../../api/lib/libfmodex.so -pthread

dsp_custom_c: main.c
	g++ -O3 -o dsp_custom main.c ../../api/lib/libfmodex.so -pthread

run:
	./dsp_custom

clean:
	rm -f dsp_custom
