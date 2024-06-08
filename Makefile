NAME = libbleparser.a
EXE = ble_parser

CC = gcc
CFLAGS = -Wall -g -O2
INCLUDES = -I./includes
SRC_DIR = ./srcs
OBJ_DIR = ./build/obj
DEP_DIR = ./build/deps

LIBS = -lyaml

SRCS = $(shell find $(SRC_DIR) -name "*.c" -not -name "main.c")
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(patsubst $(SRC_DIR)/%.c,$(DEP_DIR)/%.d,$(SRCS))

all: $(NAME)

# Create necessary directories and compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@) $(dir $(DEP_DIR)/$*)
	@echo "\033[0;34mCompiling... $<\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c -o $@ $<
	@mv $(OBJ_DIR)/$*.d $(DEP_DIR)/$*.d

-include $(DEPS)

$(NAME): $(OBJS)
	@ar rcs $@ $(OBJS)
	@echo "\033[0;32mLibrary created: $(NAME)\033[0m"

executable: $(OBJS)
	@echo "\033[0;34mCompiling and linking... $(EXE)\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXE) $(OBJS) $(SRC_DIR)/main.c $(LIBS)

clean:
	@echo "\033[0;31mCleaning...\033[0m"
	@rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	@echo "\033[0;31mFull Cleaning...\033[0m"
	@rm -f $(NAME) $(EXE)

re: fclean all

rex: fclean executable

.PHONY: all clean fclean re executable
