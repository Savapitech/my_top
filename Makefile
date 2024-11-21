##
## EPITECH PROJECT, 2024
## my_ls
## File description:
## ./Makefile
##

MAKEFLAGS += -j

NAME := my_top

SRC := $(wildcard src/*.c)
SRC += $(wildcard src/flags/*.c)
SRC += $(wildcard src/utils/*.c)
SRC += $(wildcard src/getters/*.c)
SRC += $(wildcard src/render/*.c)

BUILD_DIR := .build

TEST_SRC := tests/main.c
TEST_OBJ := $(TEST_SRC:%.c=$(BUILD_DIR)/%.o)

OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)

CC := gcc

CFLAGS += -Wall -Wextra -g3
CFLAGS += -iquote ./include
CFLAGS += -Wno-unused-parameter -fsanitize=address

oui: $(NAME)

$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lncurses -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) -r $(NAME) $(BUILD_DIR)

.NOTPARALLEL: re
re:	fclean oui

test: $(NAME) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJ)

tests_run: test
	./$<

.PHONY: all clean fclean re test tests_run
