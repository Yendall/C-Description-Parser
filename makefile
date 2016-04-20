#----------------------------------------------#
#	Name:		Max Yendall            #
#	Runnable:	description_parser     #
#	Version:	1.0                    #
#	File:		Makefile               #
#----------------------------------------------# 

CXX = clang++
STDSOURCE = -std=c++11 -stdlib=libc++ -lsndfile
CFLAGS = -W -lrt -I /usr/opt/local/include -L /usr/opt/local/lib -lboost_system -lboost_filesystem
OBJS = Include/csv_parser.o description_parser.o
HEADERS = Include/csv_parser.hpp Include/filter_vector.hpp

all: $(OBJS)
	$(CXX) $(OBJS) -o description_parser

%.o: %.cpp $(HEADERS)
	$(CXX) $(CFLAGS) $(STDSOURCE) -c $< -o $@

.PHONY:clean
clean:
	rm -f $(OBJS) description_parser csv_parser
