# optional flags
CXXFLAGS += -std=c++11

# recommended flags
CXXFLAGS += -Wall -Wextra -pedantic-errors

# required for SFML
LDLIBS := $(shell pkg-config sfml-all --libs)

SOURCES := $(wildcard *.cpp)
PROGRAMS := $(patsubst %.cpp,%,$(SOURCES))

all: $(PROGRAMS)

clean:
	$(RM) $(PROGRAMS)
