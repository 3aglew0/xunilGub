appname := xunilGub

CXX := g++
CXXFLAGS := -std=c++11
LDLIBS := -lboost_system -lboost_filesystem

srcfiles := $(shell find . -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))	

all: $(appname)

$(appname): debugmenot $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

debugmenot : 
	rm -rf ./debugmenot
	git clone https://github.com/kirschju/debugmenot.git
	make -C ./debugmenot/src

depend: .depend

.depend: $(srcfiles)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	rm -f $(objects)

dist-clean: clean
	rm -f *~ .depend

help:
	@echo "---------------HELP-----------------"
	@echo "To install xunilGub type `make`"
	@echo "To run xunilGub type `make run`"
	@echo "------------------------------------"

run:
	./xunilGub

include .depend