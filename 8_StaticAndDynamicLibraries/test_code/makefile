testcode.o: test_code.c encrypt.h checksum.h
	gcc -c test_code.c -I. -o testcode.o
encrypt.o: encrypt.c encrypt.h
	gcc -c encrypt.c -o encrypt.o
checksum.o: checksum.c checksum.h
	gcc -c checksum.c -o checksum.o
libhfsecurity.a: encrypt.o checksum.o
	ar -rcs libhfsecurity.a encrypt.o checksum.o
test_code: testcode.o libhfsecurity.a
	gcc testcode.o -I. -L. -lhfsecurity -o test_code
