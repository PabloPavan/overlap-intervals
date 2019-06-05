CC = g++
CFLAGS = -c
SOURCES =  $(shell find -type f -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = intervals.x

all: $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
		$(CC) $(OBJECTS) -o $@  

.cpp.o: *.h
	$(CC) $(CFLAGS) $< -o $@

clean :
	-rm -f $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)
	
.PHONY: all clean