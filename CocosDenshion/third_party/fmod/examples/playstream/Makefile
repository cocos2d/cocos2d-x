playstream_cpp:	main.cpp
	g++ -O3 -o playstream main.cpp ../../api/lib/libfmodex.so -pthread

playstream_c:	main.c
	g++ -O3 -o playstream main.c ../../api/lib/libfmodex.so -pthread

run:
	./playstream

clean:
	rm -f playstream
