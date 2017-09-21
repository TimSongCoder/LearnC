pwd_generator.o: pwd_generator.c encrypt.h
	gcc -c pwd_generator.c

encrypt.o: encrypt.c encrypt.h
	gcc -c encrypt.c

pwd_generator: pwd_generator.o encrypt.o
	gcc pwd_generator.o encrypt.o -o pwd_generator
