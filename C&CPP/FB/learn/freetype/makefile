all : getbitmap
getbitmap.o : getbitmap.c
	gcc $(CXXFLAGS) -c `pkg-config freetype2 --cflags` $< -o $@
getbitmap : getbitmap.o
	gcc $(CXXFLAGS) `pkg-config freetype2 --libs` -lm $< -o $@
clean :
	rm -f *.o getbitmap
