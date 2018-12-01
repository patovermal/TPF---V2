CC=gcc
CFLAGS=-std=c99 -Wall -Wpedantic -o3
all: gpxprint.exe clean

gpxprint.exe: main.o args.o fecha.o geopos.o gpx.o help.o list.o logs.o nmea.o split.o ubx.o bits.o
	$(CC) $(CFLAGS) -o gpxprint.exe main.o args.o fecha.o geopos.o gpx.o help.o list.o logs.o nmea.o split.o ubx.o bits.o -lm
	
main.o: main.c ./nmea/nmea.h ./fecha/fecha.h ./gpx/gpx.h ./args/args.h ./logs/logs.h ./help/help.h ./status/status.h ./files/files.h ./ubx/ubx.h
	$(CC) $(CFLAGS) -o main.o -c main.c -lm
	
nmea.o: ./nmea/nmea.c ./nmea/nmea.h ./fecha/fecha.h ./gpx/gpx.h ./geopos/geopos.h ./split/split.h ./list/list.h ./logs/logs.h ./status/status.h ./files/files.h
	$(CC) $(CFLAGS) -o nmea.o -c ./nmea/nmea.c -lm

ubx.o: ./ubx/ubx.c ./ubx/ubx.h ./fecha/fecha.h ./gpx/gpx.h ./bits/bits.h ./split/split.h ./list/list.h ./logs/logs.h ./status/status.h ./files/files.h
	$(CC) $(CFLAGS) -o ubx.o -c ./ubx/ubx.c -lm

gpx.o: ./gpx/gpx.c ./gpx/gpx.h fecha.o ./fecha/fecha.h ./status/status.h
	$(CC) $(CFLAGS) -o gpx.o -c ./gpx/gpx.c -lm

geopos.o: ./geopos/geopos.c ./geopos/geopos.h ./status/status.h
	$(CC) $(CFLAGS) -o geopos.o -c ./geopos/geopos.c -lm

list.o: ./list/list.c ./list/list.h ./status/status.h
	$(CC) $(CFLAGS) -o list.o -c ./list/list.c -lm 
	
fecha.o: ./fecha/fecha.c ./fecha/fecha.h ./status/status.h
	$(CC) $(CFLAGS) -o fecha.o -c ./fecha/fecha.c -lm

logs.o: ./logs/logs.c ./logs/logs.h ./status/status.h
	$(CC) $(CFLAGS) -o logs.o -c ./logs/logs.c -lm

args.o: ./args/args.c ./args/args.h ./status/status.h
	$(CC) $(CFLAGS) -o args.o -c ./args/args.c -lm
	
split.o: ./split/split.c ./split/split.h
	$(CC) $(CFLAGS) -o split.o -c ./split/split.c -lm

help.o: ./help/help.c ./help/help.h
	$(CC) $(CFLAGS) -o help.o -c ./help/help.c -lm

bits.o: ./bits/bits.c ./bits/bits.h
	$(CC) $(CFLAGS) -o bits.o -c ./bits/bits.c -lm

clean:
	rm -v *.o