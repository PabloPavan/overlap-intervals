CC = g++
CFLAGS = -c -g -O2 -DDUMP
LIBS = #-L ../include/ -llogger
SOURCES =  $(shell find -type f -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = intervals.x

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
		$(CC) $(OBJECTS) $(LIBS) -o $@ 

.cpp.o: *.h
	$(CC) $(CFLAGS) $< -o $@

clean :
	-rm -f $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

rundebug: $(EXECUTABLE)
	valgrind --leak-check=full ./$(EXECUTABLE)

	
.PHONY: all clean