SRCS =accumulator.cpp alu.cpp flagreg.cpp idb.cpp instreg.cpp  MDR.cpp  register.cpp temp.cpp  ctrlunit.cpp main8085.cpp Intersplitter.cpp  ram.cpp
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(SRCS:%.cpp=%.d)

SYSTEMC         = /usr/local/systemc231

CXX = g++
CXXFLAGS = -Wall -ansi -g -O0 -Di386

INCLUDES = -I $(SYSTEMC)/include

LD = $(CXX)
LDFLAGS = $(CXXFLAGS)

LIBS = -L/usr/local/systemc231/lib-linux64 -lsystemc -Wl,-rpath,/usr/local/systemc231/lib-linux64

PROGRAM = dp8085

default = $(PROGRAM)

$(PROGRAM):	$(OBJS) $(DEPS)
		$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o ./$@
                
test:		$(PROGRAM)
		./$<
                
clean:;		rm -rf $(PROGRAM) *.o core* *.d *.vcd *.dump

# Cancel implicit rule
%.o: 		%.cpp

%.o:		%.cpp %.d
		$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.d:		%.cpp
		@ echo Making dependencies for $<
		@ g++ -MM $(INCLUDES) $< | sed 's#: # $*.d : #1' > $@

# Include dependency files .d
ifneq ("$(wildcard *.d)","")
	include $(wildcard *.d)
endif
