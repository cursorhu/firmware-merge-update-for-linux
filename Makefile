CC = g++ 
CFLAGS = -Wall -g

TARGET = mergeheader

all : $(TARGET)

$(TARGET) : main.o merge.o parameter.o ini.o
	$(CC) $(CFLAGS) -o $@ $^

main.o : main.cpp
	$(CC) $(CFLAGS) -c main.cpp

merge.o : merge.cpp merge.h 
	$(CC) $(CFLAGS) -c merge.cpp

parameter.o : parameter.cpp parameter.h
	$(CC) $(CFLAGS) -c parameter.cpp

ini.o : ini.cpp ini.h
	$(CC) $(CFLAGS) -c ini.cpp

clean:
	rm -f *.o