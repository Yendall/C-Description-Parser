#----------------------------------------------	#
#	Name:		Max Yendall		#
#	Runnable:	description_parser	#
#	Version:	1.0  			#
#	File:		Makefile	       	#
#---------------------------------------------- #

CXX = clang++
STDSOURCE = -std=c++11 -stdlib=libc++
CFLAGS = -W -lrt -I/user/local/include -L/user/local/lib -lboost_system
OBJS = csv_parser.o description_parser.o
HEADERS = csv_parser.hpp filter_vector.hpp

all: $(OBJS)
	$(CXX) $(OBJS) -o description_parser

%.o: %.cpp $(HEADERS)
	$(CXX) $(CFLAGS) $(STDSOURCE) -c $< -o $@

.PHONY:clean
clean:
	rm -f $(OBJS) description_parser
