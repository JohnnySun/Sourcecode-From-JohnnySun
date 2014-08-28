TGT = roboert.out
SRC = main.c
LIC = kernel.c mmis.c
LIB = librobotkernel.so
LID = /lib
CIB = $(LID)/librobotkernel.so
GIB = -l robotkernel

all: $(LIB)
	$(CC) $(SRC) -L . $(GIB) -o $(TGT)

$(LIB): $(LIC)
	$(CC) $(LIC) $(LIBS) -fPIC -shared -o $@
	cp $@ $(LID)

clean:
	rm $(TGT) $(CIB) $(LIB)
