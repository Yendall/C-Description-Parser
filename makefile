#----------------------------------------------#
#	Name:		Max Yendall                    #
#	Runnable:	data_parser                    #
#	Version:	1.0                            #
#	File:		Makefile                       #
#----------------------------------------------# 

CXX = clang++
STDSOURCE = -std=c++11 -stdlib=libc++
CFLAGS = -w -lrt -I/usr/opt/local/include -L/usr/opt/local/lib -lboost_system -lboost_filesystem
OBJS = include/csv_parser.o pre-processing_algorithms/data_analyser.o categorisation_algorithms/data_mapper.o main.o
HEADERS = include/csv_parser.hpp

all: $(OBJS)
	$(CXX) $(OBJS) -o data_parser

%.o: %.cpp $(HEADERS)
	$(CXX) $(CFLAGS) $(STDSOURCE) -c $< -o $@

.PHONY:clean
clean:
	rm -f $(OBJS) data_parser
