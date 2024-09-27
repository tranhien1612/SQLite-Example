CXX=g++
CXXFLAGS = -g -Wall

main:
	$(CXX) $(CXXFLAGS) -o main main.cpp -lsqlite3

clean:
	rm -rf main 
