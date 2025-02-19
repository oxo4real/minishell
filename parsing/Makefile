CC = cc
CFLAGS = -Wextra -Wall -Werror
SRCS = ft_calloc.c ft_memcpy.c ft_strtrim.c node.c parser.c readline.c redir.c shunting_yard.c\
		tk_match.c tk_types.c tk_utils.c tokenizer.c tokenizer_handle_cmd.c \
		tokenizer_handle_par.c tokenizer_handle_redir.c tree_utils.c \
		../utils/ft_strlen.c ../utils/ft_strdup.c

BUILD = build
OBJS = $(addprefix $(BUILD)/, $(notdir $(SRCS:.c=.o)))
INCS = .
HEADER = parser.h
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lreadline $^ -o $(NAME)

$(BUILD)/%.o: %.c $(HEADER) | $(BUILD)
	$(CC) $(CFLAGS) -I$(INCS) -c $< -o $@
$(BUILD)/%.o: ../utils/%.c $(HEADER) | $(BUILD)
	$(CC) $(CFLAGS) -I$(INCS) -c $< -o $@

$(BUILD):
	@mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all
