recording_cpp:	main.cpp
	g++ -O3 -o recording main.cpp ../../api/lib/libfmodex.so -pthread

recording_c:	main.c
	g++ -O3 -o recording main.c ../../api/lib/libfmodex.so -pthread

run:
	./recording

clean:
	rm -f recording
