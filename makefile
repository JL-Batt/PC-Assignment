serial:
	gcc bruteserial.c -o bruteserial -lcrypto -fopenmp

omp:
	gcc bruteomp.c -o bruteomp -lcrypto -fopenmp
	
clean:
	rm bruteomp
	gcc bruteomp.c -o bruteomp -lcrypto -fopenmp
	rm bruteserial
	gcc bruteserial.c -o bruteserial -lcrypto -fopenmp
