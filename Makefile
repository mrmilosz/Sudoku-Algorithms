    BIN= sudoku
    LIB= sudoku

  SHELL= /bin/bash
     CC= /usr/bin/g++
     AR= /usr/bin/ar
    SRC= src
INCLUDE= include
    OBJ= obj
 CFLAGS= -Wall -I$(INCLUDE)
LDFLAGS= -L. -l$(LIB)

(BIN): lib$(LIB).a $(INCLUDE)/Grid.hpp $(INCLUDE)/Exception.hpp main.cpp
	$(CC) $(CFLAGS) main.cpp $(LDFLAGS) -o $(BIN)

lib$(LIB).a: $(OBJ)/Grid.o
	$(AR) r lib$(LIB).a $(OBJ)/Grid.o

$(OBJ)/Grid.o: $(OBJ)
	$(CC) $(CFLAGS) -c $(SRC)/Grid.cpp
	mv Grid.o $(OBJ)/

$(OBJ):
	mkdir $(OBJ)

clean:
	rm -f $(OBJ)/* lib$(LIB).a $(BIN) && rmdir $(OBJ)
