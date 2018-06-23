
SOURCES = main.cpp Interpreter.cpp Execution.cpp  ExternalFunctions.cpp Utils.cpp
OBJECTS = $(SOURCES:.cpp=.o)
SHARES  = $(SOURCES:.cpp=.so)
LIBPATH = /home/wang/Pictures/llvm-lib
LLVM_CONFIG = llvm-config
CXX = g++


llvm-goback: Makefile $(SHARES)
	ccache g++ -g $(SHARES) -o mdb -Wl,-rpath,/home/wang/Music/mdb  `llvm-config --ldflags --system-libs --libs interpreter asmparser`

$(OBJECTS): %.o: %.cpp Makefile Interpreter.h Film.h
	ccache $(CXX) -g -c $< -o $@ `$(LLVM_CONFIG) --cxxflags`
	
$(SHARES): %.so: %.o Makefile
	ccache $(CXX) -g -shared -fPIC $< -o $@

.PHONY: clean
clean:
	rm -rf mdb $(OBJECTS) $(SHARES)
