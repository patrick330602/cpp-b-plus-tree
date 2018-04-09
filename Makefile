TARGET=$(shell basename $(PWD))
create:
	g++ -g -Wall -std=c++11 -o $(TARGET) *.cpp *.h

clean:
	/bin/rm -f $(TARGET)
	clear