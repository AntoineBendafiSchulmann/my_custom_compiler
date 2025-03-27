CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Isrc -Isrc/lexer -Isrc/parser -Isrc/codegen -Isrc/utils

SRC = \
	src/main.c \
	src/compiler.c \
	src/lexer/lexer.c \
	src/parser/parser.c \
	src/parser/ast.c \
	src/codegen/codegen.c \
	src/utils/utils.c

OBJ = $(SRC:.c=.o)
BIN = mycc

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(BIN)