# Universidad de La Laguna
 # Escuela Superior de Ingeniería y Tecnología
 # Grado en Ingeniería Informática
 # CyA
 #
 # @author Esther M. Quintero
 # @date 24 Oct 2022

CXX = g++						             # The C++ compiler command
CXXFLAGS = -std=c++14 -g -Wall	 # The C++ compiler options (C++14, preserve debug symbols and warn all)
LDFLAGS =						             # The linker options (if any)

# The all target builds all of the programs handled by the makefile.
all: p04_code_analyzer

p04_code_analyzer: main_p04codeanalyzer.o main_p04codeanalyzer.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Indicate that the all and clean targets do not
# correspond to actual files.
.PHONY: all clean

# The following rule is effectively built into make and
# therefore need not be explicitly specified:
# hello_world.o: hello_world.cc
	$(CXX) $(CXXFLAGS) -c $<

# The clean target removes all of the executable files
# and object files produced by the build process
# We can use it for additional housekeeping purposes
clean :
	rm -f *.o p04_code_analyzer doc
	rm -rf a.out
	find . -name '*~' -exec rm {} \;