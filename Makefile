NAME=minishell

FILES=main \
	builtins/pwd builtins/cd builtins/echo builtins/exit builtins/env builtins/export builtins/unset builtins/builtins \
	core/environment core/format_command core/make_command core/cleanup core/raw_parse core/syntax_parse \
	core/signal core/piping core/redirects core/pipe_parse \
	utils/strlen utils/strdup utils/strncmp utils/atolli utils/strjoin utils/is_space utils/itoa utils/list utils/parse_path utils/split utils/put_in_tab utils/is_bin

SRC=$(foreach f, $(FILES), src/$(f).c)
OBJ=$(foreach f, $(FILES), obj/$(f).o)

CCFLAGS=-Isrc -Wall -Wextra -Werror -g3 -lreadline
LNFLAGS=$(CCFLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $^ $(LNFLAGS)

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
