CC = g++
FLAGS = -shared -fPIC
SOURCES =  $(shell find -type f -name '*.cpp')
OBJECTS = $(SOURCES:.cpp=.so)

all: $(OBJECTS) mv

$(OBJECTS): $(SOURCES)	
	$(CC) $(FLAGS) -o $@ $<

mv: $(OBJECTS)
	-$@ $< lib$<

clean :
	-rm -f  *.so

.PHONY: all clean