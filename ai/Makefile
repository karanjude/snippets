a: a.o 
	g++ -o a a.o 

# now define how each object file is a target and list dependencies and how
#  to build that object file if any dependencies change

a.o: a.cc 
	g++ -c a.cc util.h strategy.h dfs.h bfs.h astar.h
clean:
	rm a a.o
