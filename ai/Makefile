a: a.o 
	g++ -o a a.o 

# now define how each object file is a target and list dependencies and how
#  to build that object file if any dependencies change

account.o: account.cc 
	g++ -c account.cc
clean:
	rm a a.o
