CC = gcc -g

all:clean_all bitmap_static lib_static build clean

static:clean_all bitmap_static lib_static build clean

dyn:clean_all bitmap_dyn lib_dyn build clean

build: mine.o 
	$(CC) main.o -o main -L. -lbitmap
	
inter: inter.o
	$(CC) main_inter.c -o inter -L. -lbitmap -lm

RIGHT: bitmap_left_static lib_static build clean

lib_static: 
	ar rc libbitmap.a bitmap.o
	
lib_dyn:
	$(CC) -shared bitmap.o -o libbitmap.so

bitmap_static:
	$(CC) bitmap.c -c 

bitmap_left_static:
	$(CC) bitmap.c -c -DRIGHT_TO_LEFT
	
bitmap_dyn:
	$(CC) bitmap.c -fPIC -c	
	
mine.o:
	$(CC) main.c -c

inter.o:
	$(CC) main_inter.c -c
	
clean:
	rm -rf *.o
	
clean_all:
	rm -rf *.o *.a *.so main inter

run:  
	LD_LIBRARY_PATH=$PWD: ./main
	

run_inter: inter
	LD_LIBRARY_PATH=$PWD: ./inter
