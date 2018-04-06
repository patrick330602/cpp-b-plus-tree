TARGET=$(shell basename $(PWD))
create:
	g++ -g -o $(TARGET) *.cpp *.h

clean:
	/bin/rm -f $(TARGET)
	clear