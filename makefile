serial:
	gcc bruteserial.c -o bruteserial -lcrypto -fopenmp

omp:
	gcc bruteomp.c -o bruteomp -lcrypto -fopenmp
	
clean:
	rm bruteomp
	rm bruteserial	