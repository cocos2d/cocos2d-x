generatetone_cpp:	main.cpp
	g++ -O3 -o generatetone main.cpp ../../api/lib/libfmodex.so

generatetone_c:	main.c
	g++ -O3 -o generatetone main.c ../../api/lib/libfmodex.so

run:
	./generatetone

clean:
	rm -f generatetone
