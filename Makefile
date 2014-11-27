APPS = Final Project

#Change to your own student number
STUDENT_NUMBER = 301226977

OBJECTS = lexemesTypes.o parserClasses.o project.o
HEADERS = lexemesTypes.h parserClasses.h

#Debug flag
CXXFLAGS += -g

all: $(APPS)

$(OBJECTS): $(HEADERS)
$(APPS): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	$(RM) *.o $(APPS)

tar:
	tar -czf $(STUDENT_NUMBER).tar.gz Makefile *.cpp *.h


