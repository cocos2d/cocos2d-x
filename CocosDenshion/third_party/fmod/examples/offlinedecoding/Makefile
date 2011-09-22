offlinedecoding_cpp:	main.cpp
	g++ -O3 -o offlinedecoding main.cpp ../../api/lib/libfmodex.so -pthread

offlinedecoding_c:	main.c
	g++ -O3 -o offlinedecoding main.c ../../api/lib/libfmodex.so -pthread

run:
	./offlinedecoding

clean:
	rm -f offlinedecoding
