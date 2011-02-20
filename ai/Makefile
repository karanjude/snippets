CS561A1.exe: CS561A1.o 
	g++ -o CS561A1.exe CS561A1.o 

# now define how each object file is a target and list dependencies and how
#  to build that object file if any dependencies change

CS561A1.o: CS561A1.cc 
	g++ -c CS561A1.cc util.h strategy.h dfs.h bfs.h astar.h
clean:
	rm CS561A1.exe CS561A1.o
