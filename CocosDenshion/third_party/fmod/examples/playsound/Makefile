playsound_cpp:	main.cpp
	g++ -O3 -o playsound main.cpp ../../api/lib/libfmodex.so -pthread

playsound_c:	main.c
	gcc -O3 -o playsound main.c ../../api/lib/libfmodex.so -pthread

run:
	./playsound

clean:
	rm -f playsound
