CS561A1.exe: CS561A1.o 
	g++ -g -o CS561A1.exe CS561A1.o 

# now define how each object file is a target and list dependencies and how
#  to build that object file if any dependencies change

CS561A1.o: CS561A1.cc 
	g++ -g -c CS561A1.cc 
clean:
	rm CS561A1.exe CS561A1.o
