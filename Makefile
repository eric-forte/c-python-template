all: test

setup:
	pip install -r requirements.txt

clean:
	rm -f *.o *.so

mynum.so: mynum.o
	gcc -shared -o libmynum.so mynum.o

mynum.o: mynum.c
	gcc -c -Wall -Werror -fpic mynum.c

test: mynum.so
	python3 test.py
