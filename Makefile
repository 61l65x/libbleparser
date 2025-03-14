NAME = libbleparser.a

CC = gcc
CXX = g++
CFLAGS = -Wall -g -O2
CXXFLAGS = -Wall -g -O2 -std=c++11
INCLUDES = -I./srcs/includes -I./srcs/includes/parse_yaml
SRC_DIR = ./srcs/core

OBJ_DIR = ./build/obj
DEP_DIR = ./build/deps

LIBS = -lyaml

SRCS = $(shell find $(SRC_DIR) -name "*.c" -o -name "*.cpp" -not -name "main.c")
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS)))
DEPS = $(patsubst $(SRC_DIR)/%.c,$(DEP_DIR)/%.d,$(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$(SRCS)))

LIB_INSTALL_DIR = /usr/local/lib
INCLUDE_INSTALL_DIR = /usr/local/include/bleparser


all: update_deps create-archive

# LINKING

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@) $(dir $(DEP_DIR)/$*)
	@echo "\033[0;34mCompiling C... $<\033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c -o $@ $<
	@mv $(OBJ_DIR)/$*.d $(DEP_DIR)/$*.d

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@) $(dir $(DEP_DIR)/$*)
	@echo "\033[0;34mCompiling C++... $<\033[0m"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c -o $@ $<
	@mv $(OBJ_DIR)/$*.d $(DEP_DIR)/$*.d

-include $(DEPS)

# BUILDS

create-archive: $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@mv *.a ./build
	@echo "\033[0;32mLibrary created: build/$(NAME)\033[0m"

install: all
	@echo "\033[0;34mInstalling library with sudo...\033[0m"
	@sudo mkdir -p $(LIB_INSTALL_DIR) $(INCLUDE_INSTALL_DIR)
	@sudo cp ./build/$(NAME) $(LIB_INSTALL_DIR)
	@sudo cp -r ./srcs/includes/* $(INCLUDE_INSTALL_DIR)
	@echo "\033[0;32mLibrary installed to $(LIB_INSTALL_DIR)\033[0m"
	@echo "\033[0;32mHeaders installed to $(INCLUDE_INSTALL_DIR)\033[0m"

uninstall:
	@echo "\033[0;31mUninstalling library with sudo...\033[0m"
	@sudo rm -f $(LIB_INSTALL_DIR)/$(NAME)
	@sudo rm -rf $(INCLUDE_INSTALL_DIR)
	@echo "\033[0;32mLibrary uninstalled\033[0m"

# TESTS

cpp-test-executable: update_deps $(OBJS)
	@echo "\033[0;34mCompiling and linking... cpp-test \033[0m"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o build/cpp-test $(OBJS) srcs/tests/test.cpp $(LIBS)

c-test-executable: update_deps $(OBJS)
	@echo "\033[0;34mCompiling and linking... c-test \033[0m"
	$(CC) $(CFLAGS) $(INCLUDES) -o build/c-test $(OBJS) srcs/tests/test.c $(LIBS)

run-tests: cpp-test-executable c-test-executable
	@echo "\033[0;34mRunning tests...\033[0m"
	@./build/cpp-test && ./build/c-test
	

lib-function-tests:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o test srcs/tests/test.cpp -L./build -lbleparser -lyaml



# CLEANING & DEPENDENCIES

clean:
	@echo "\033[0;31mCleaning... libbleparser\033[0m"
	@rm -rf build/$(NAME) $(EXE)

fclean: clean
	@echo "\033[0;31mFull Cleaning...\033[0m"
	@rm -rf build

update_deps:
	@echo "\033[0;34mUpdating dependencies...\033[0m"
	@rm -rf srcs/repository
	@git submodule update --init --recursive
	@(cd srcs/repository && git fetch && git checkout main && git pull origin main || echo "Submodule checkout failed.")
	@echo "\033[0;32mDependencies updated\033[0m"


re: fclean all

rex: fclean executable

.PHONY: all clean fclean install uninstall re cpp-test-executable c-test-executable lib-function-tests update_deps
