playlist_cpp:	main.cpp
	g++ -O3 -o playlist main.cpp ../../api/lib/libfmodex.so -pthread

playlist_c:	main.c
	g++ -O3 -o playlist main.c ../../api/lib/libfmodex.so -pthread

run:
	./playlist

clean:
	rm -f playlist
