NAME = libbleparser.a
EXE = ble_parser

CC = gcc
CFLAGS = -Wall -g -O2

INCLUDES = -I./includes
SRC_DIR = ./srcs
OBJ_DIR = ./obj

LIBS = -lyaml

SRCS = $(shell find $(SRC_DIR) -name "*.c" -not -name "main.c")
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/init_data_structs
	@mkdir -p $(OBJ_DIR)/free

$(NAME): $(OBJ_DIR) $(OBJS)
	@ar rcs $@ $(OBJS)
	@echo "\033[0;32mLibrary created: $(NAME)\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "\033[0;34mCompiling... $<\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

executable: $(OBJ_DIR) $(OBJS)
	@echo "\033[0;34mCompiling and linking... $(EXE)\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXE) $(shell find $(OBJ_DIR) -name "*.o") $(SRC_DIR)/main.c $(LIBS)

clean:
	@echo "\033[0;31mCleaning...\033[0m"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "\033[0;31mFull Cleaning...\033[0m"
	@rm -f $(NAME) $(EXE)

re: fclean all

.PHONY: all clean fclean re executable
