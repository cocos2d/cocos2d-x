channelgroups_cpp:	main.cpp
	g++ -O3 -o channelgroups main.cpp ../../api/lib/libfmodex.so -pthread

channelgroups_c:	main.c
	g++ -O3 -o channelgroups main.c ../../api/lib/libfmodex.so -pthread

run:
	./channelgroups

clean:
	rm -f channelgroups
