useplugins_cpp:	main.cpp
	g++ -O3 -o useplugins main.cpp ../../api/lib/libfmodex.so -pthread

useplugins_c:	main.c
	g++ -O3 -o useplugins main.c ../../api/lib/libfmodex.so -pthread

run:
	./useplugins

clean:
	rm -f useplugins
