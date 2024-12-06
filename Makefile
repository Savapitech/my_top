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

CFLAGS += -Wall -Wextra
CFLAGS += -iquote ./include
CFLAGS += -Wno-unused-parameter

include utils.mk

oui: $(NAME)

$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) -o $@ -c $<
	@ $(LOG_TIME) "$(C_GREEN) CC $(C_PURPLE) $(notdir $@) $(C_RESET)"

$(NAME): $(OBJ)
	@ $(CC) $(CFLAGS) $(OBJ) -lncurses -o $(NAME)
	@ $(LOG_TIME) "$(C_GREEN) CC $(C_PURPLE) $(notdir $@) $(C_RESET)"
	@ $(LOG_TIME) "$(C_GREEN) OK Compilation finished $(C_RESET)"

clean:
	@ $(RM) $(OBJ)
	@ $(LOG_TIME) "$(C_YELLOW) RM $(C_PURPLE) $(OBJ) $(C_RESET)"

fclean:
	@ $(RM) -r $(NAME) $(BUILD_DIR)
	@ $(LOG_TIME) "$(C_YELLOW) RM $(C_PURPLE) $(NAME) $(BUILD_DIR) $(C_RESET)"

.NOTPARALLEL: re
re:	fclean oui

test: $(NAME) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJ)

tests_run: test
	./$<

check: $(NAME)
	-@ valgrind               \
		--leak-check=full     \
		--track-origins=yes   \
		--error-limit=no --suppressions=ncurses.supp \
		./$(NAME)

.PHONY: all clean fclean re test tests_run check
