CC=gcc
CFLAGS=-std=c99 -Wall -Wpedantic -o3
all: nmeatogpx.exe clean

nmeatogpx.exe: main.o pruebadelwhile.o nmea.o nmea.h fecha.o fecha.h status.o status.h gpx.o gpx.h geopos.o geopos.h list.o list.h files.h
	$(CC) $(CFLAGS) -o nmeatogpx.exe main.o pruebadelwhile.o nmea.o fecha.o status.o gpx.o geopos.o list.o
	
main.o: prueba.c pruebadelwhile.o fecha.o fecha.h status.o status.h gpx.o gpx.h files.h
	$(CC) $(CFLAGS) -o main.o -c prueba.c pruebadelwhile.o fecha.o status.o gpx.o

pruebadelwhile.o: pruebadelwhile.c fecha.o fecha.h status.o status.h gpx.o gpx.h nmea.o nmea.h list.o list.h files.h
	$(CC) $(CFLAGS) -o pruebadelwhile.o -c pruebadelwhile.c fecha.o status.o gpx.o nmea.o list.o
	
nmea.o: nmea.c nmea.h fecha.o fecha.h status.o status.h gpx.o gpx.h geopos.o geopos.h
	$(CC) $(CFLAGS) -o nmea.o -c nmea.c fecha.o status.o gpx.o geopos.o

gpx.o: gpx.c gpx.h fecha.o fecha.h status.o status.h
	$(CC) $(CFLAGS) -o gpx.o -c gpx.c fecha.o status.o

geopos.o: geopos.c geopos.h status.o status.h
	$(CC) $(CFLAGS) -o geopos.o -c geopos.c status.o

list.o: list.c list.h status.o status.h
	$(CC) $(CFLAGS) -o list.o -c list.c status.o
	
fecha.o: fecha.c fecha.h status.o status.h
	$(CC) $(CFLAGS) -o fecha.o -c fecha.c status.o
	
status.o: status.c status.h
	$(CC) $(CFLAGS) -o status.o -c status.c	

clean:
	rm -v *.o