submixing_cpp:	main.cpp
	g++ -O3 -o submixing main.cpp ../../api/lib/libfmodex.so -pthread

submixing_c:	main.c
	g++ -O3 -o submixing main.c ../../api/lib/libfmodex.so -pthread

run:
	./submixing

clean:
	rm -f submixing
