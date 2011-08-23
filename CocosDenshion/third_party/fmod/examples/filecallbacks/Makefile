filecallbacks_cpp:	main.cpp
	g++ -O3 -o filecallbacks main.cpp ../../api/lib/libfmodex.so -pthread

filecallbacks_c:	main.c
	g++ -O3 -o filecallbacks main.c ../../api/lib/libfmodex.so -pthread

run:
	./filecallbacks

clean:
	rm -f filecallbacks
