CC = gcc
CFLAG = -Wall -Wextra -g
EXE = tema1
OBJ = tema1.o utils.o

build: $(EXE)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAG)

$(EXE): $(OBJ)
	$(CC) $^ $(CFLAG) $(LDFLAGS) -utils.h -o $(EXE)

run:
	./$(EXE)

.PHONY: clean 

clean:
	rm -f *.o $(EXE)