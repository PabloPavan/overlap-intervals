CC = g++
CFLAGS = -c -g3 -O2 -DLOG   #-DDUMP
LIBS = #-L ../include/ -llogger
SOURCES =  $(shell find src -type f -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = bin/intervals.x

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
		$(CC) $(OBJECTS) $(LIBS) -o $@ 

.cpp.o: *.h
	$(CC) $(CFLAGS) $< -o $@

clean :
	-rm -f $(OBJECTS) $(EXECUTABLE)

	
.PHONY: all clean
