APPS = Final Project

#Change to your own student number
STUDENT_NUMBER = 301226977
STUDENT_NUMBER = 301150253

OBJECTS = lexemesTypes.o parserClasses.o assignment3.o advancerParserClasses.o
HEADERS = lexemesTypes.h parserClasses.h advancerParserClasses.h

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


