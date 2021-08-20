EXEC=main
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
CARGS= -fno-math-errno -ffast-math -march=native $(CFLAGS)
LDARGS= $(LDFLAGS)

all: $(EXEC)

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDARGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CARGS)

clean:
	@rm -rf *.o
	@rm -rf $(EXEC)
.PHONY: clean
