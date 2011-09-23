multispeakeroutput_cpp:	main.cpp
	g++ -O3 -o multispeakeroutput main.cpp ../../api/lib/libfmodex.so -pthread

multispeakeroutput_c:	main.c
	g++ -O3 -o multispeakeroutput main.c ../../api/lib/libfmodex.so -pthread

run:
	./multispeakeroutput

clean:
	rm -f multispeakeroutput
