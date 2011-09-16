netstream_cpp:	main.cpp
	g++ -O3 -o netstream main.cpp ../../api/lib/libfmodex.so -pthread

netstream_c:	main.c
	g++ -O3 -o netstream main.c ../../api/lib/libfmodex.so -pthread

run:
	./netstream

clean:
	rm -f netstream
