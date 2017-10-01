test_code.o: test_code.c encrypt.h checksum.h
	gcc -c test_code.c
encrypt.o: encrypt.c encrypt.h
	gcc -c encrypt.c
checksum.o: checksum.c checksum.h
	gcc -c checksum.c
test_code: test_code.o encrypt.o checksum.o
	gcc *.o -o test_code
