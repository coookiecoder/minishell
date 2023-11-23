NAME=minishell

FILES=main \
	builtins/pwd \
	utils/strlen utils/strdup utils/strncmp \
	core/environment

SRC=$(foreach f, $(FILES), src/$(f).c)
OBJ=$(foreach f, $(FILES), obj/$(f).o)

CCFLAGS=-Isrc -Wall -Wextra -Werror -Wunreachable-code -Wunreachable-code-aggressive -Wpedantic -g3
LNFLAGS=-lreadline -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LNFLAGS) -o $@ $^

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -o $@ -c $<

clean:
	$(RM) -r obj

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
.DEFAULT_GOAL:=$(NAME)

