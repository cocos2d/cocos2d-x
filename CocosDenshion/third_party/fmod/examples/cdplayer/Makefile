cdplayer_cpp:	main.cpp
	g++ -O3 -o cdplayer main.cpp ../../api/lib/libfmodex.so -pthread

cdplayer_c:	main.c
	g++ -O3 -o cdplayer main.c ../../api/lib/libfmodex.so -pthread

run:
	./cdplayer

clean:
	rm -f cdplayer
