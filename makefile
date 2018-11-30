CC=gcc
CFLAGS=-std=c99 -Wall -Wpedantic -o3
all: nmeatogpx.exe clean

nmeatogpx.exe: main.o args.o fecha.o geopos.o gpx.o help.o list.o logs.o nmea.o split.o
	$(CC) $(CFLAGS) -o nmeatogpx.exe main.o args.o fecha.o geopos.o gpx.o help.o list.o logs.o nmea.o split.o
	
main.o: main.c nmea.o ./nmea/nmea.h fecha.o ./fecha/fecha.h gpx.o ./gpx/gpx.h args.o ./args/args.h logs.o ./logs/logs.h help.o ./help/help.h ./status/status.h ./files/files.h
	$(CC) $(CFLAGS) -o main.o -c main.c nmea.o fecha.o gpx.o args.o logs.o  help.o
	
nmea.o: ./nmea/nmea.c ./nmea/nmea.h fecha.o ./fecha/fecha.h gpx.o ./gpx/gpx.h geopos.o ./geopos/geopos.h split.o ./split/split.h list.o ./list/list.h  logs.o ./logs/logs.h ./status/status.h ./files/files.h
	$(CC) $(CFLAGS) -o nmea.o -c ./nmea/nmea.c fecha.o gpx.o geopos.o split.o list.o logs.o

gpx.o: ./gpx/gpx.c ./gpx/gpx.h fecha.o ./fecha/fecha.h ./status/status.h
	$(CC) $(CFLAGS) -o gpx.o -c ./gpx/gpx.c fecha.o

geopos.o: ./geopos/geopos.c ./geopos/geopos.h ./status/status.h
	$(CC) $(CFLAGS) -o geopos.o -c ./geopos/geopos.c

list.o: ./list/list.c ./list/list.h ./status/status.h
	$(CC) $(CFLAGS) -o list.o -c ./list/list.c 
	
fecha.o: ./fecha/fecha.c ./fecha/fecha.h ./status/status.h
	$(CC) $(CFLAGS) -o fecha.o -c ./fecha/fecha.c

logs.o: ./logs/logs.c ./logs/logs.h ./status/status.h
	$(CC) $(CFLAGS) -o logs.o -c ./logs/logs.c

args.o: ./args/args.c ./args/args.h ./status/status.h
	$(CC) $(CFLAGS) -o args.o -c ./args/args.c
	
split.o: ./split/split.c ./split/split.h
	$(CC) $(CFLAGS) -o split.o -c ./split/split.c

help.o: ./help/help.c ./help/help.h
	$(CC) $(CFLAGS) -o help.o -c ./help/help.c

clean:
	rm -v *.o