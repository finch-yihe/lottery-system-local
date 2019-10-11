DIR_INC = ./.
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./bin

SRC = $(wildcard $(DIR_SRC)/*.c)
OBJ = $(patsubst %.c, $(DIR_OBJ)/%.o, $(notdir $(SRC)))
CC = gcc   
INCLUDES = -I $(DIR_INC)
CCFLAGS = -g -Wall    
OUTPUT = bin/lottarysystem 

$(OUTPUT) : $(OBJ)
	$(CC) $^ -o $@ $(INCLUDES)

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c
	$(CC) -c $< $(INCLUDES) -o $@

.PHONY:clean
clean:
	-rm bin/*
	-rm obj/*
	-rm data/*
	-rm userdata/*
