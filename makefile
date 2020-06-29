CFLAGS = -O
CC = g++

pca_driver: pca_driver.o
	$(CC) $(CFLAGS) -o pca_driver pca_driver.o pca.o --std=c++11

pca_driver.o: pca.o pca_driver.cpp
	$(CC) $(CFLAGS) -c pca_driver.cpp --std=c++11

pca.o: pca.h pca.cpp
	$(CC) $(CFLAGS) -c pca.cpp --std=c++11

run:
	./pca_driver

clean:
	rm -f core *.o
