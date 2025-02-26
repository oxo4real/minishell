CC = cc
CFLAGS = -Werror -Wextra -Wall# -g -fsanitize=address,undefined
SRCS =

#UTILS
SRCS += utils/free2darr.c utils/ft_atoi.c utils/ft_calloc.c utils/ft_isalnum.c utils/ft_isalpha.c \
		utils/ft_isdigit.c utils/ft_itoa.c utils/ft_memcpy.c utils/ft_putchar_fd.c utils/ft_putnbr_fd.c \
		utils/ft_putstr_fd.c utils/ft_split.c utils/ft_strchr.c utils/ft_strcmp.c utils/ft_strdup.c \
		utils/ft_strjoin.c utils/ft_strlen.c utils/ft_strncmp.c utils/ft_strtrim.c utils/ft_wordcmp.c \
		utils/generaterandstr.c utils/is_long.c utils/print_error.c utils/print_error2.c utils/print_error3.c \
		utils/get_next_line.c utils/get_next_line_utils.c
#UTILS

#PARSING
SRCS += parsing/envlstclear.c parsing/envlsttoenv.c parsing/envtoenvlst.c parsing/expandenvlst.c \
		parsing/getsortedwildcard.c parsing/getsortedwildcard_utils.c parsing/print_syntax_error.c \
		parsing/match_wildcard.c parsing/node.c parsing/parser.c parsing/readline.c parsing/tree_utils.c \
		parsing/replaceenvvar.c parsing/replacewildcards.c parsing/shunting_yard.c parsing/splitvar.c \
		parsing/sptobel.c parsing/tk_match.c parsing/tk_types.c parsing/tk_utils.c parsing/tokenizer.c \
		parsing/tokenizer_handle_cmd.c parsing/tokenizer_handle_par.c parsing/tokenizer_handle_redir.c \
		parsing/extract_args.c parsing/cmdtoav.c parsing/getenv_.c parsing/print_unexpected.c \
		parsing/redir.c
		
#PARSING

#BUILTINS
SRCS += builtins/cd.c builtins/echo.c builtins/env_.c builtins/exit_.c builtins/export.c builtins/pexport.c \
		builtins/pwd.c builtins/unset.c
#BUILTINS

#EXECUTING
SRCS += executing/cmd.c executing/exec_.c executing/executor.c executing/get_path.c executing/redir.c \
		executing/builtins.c executing/set_shlvl.c executing/init_env.c executing/signals.c executing/exec_pipe.c \
		executing/here_doc.c executing/expander.c
#EXECUTING


BUILD = build
OBJS = $(patsubst %.c, $(BUILD)/%.o, $(SRCS))
INCS = includes
HEADERS = $(INCS)/parsing.h $(INCS)/utils.h $(INCS)/builtins.h $(INCS)/executing.h
NAME = minishell
TOTAL := $(words $(OBJS))
COUNT := 0

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $(NAME) -lreadline
	@echo "compiled ✅"

$(BUILD)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(call progress)
	@$(CC) $(CFLAGS) -I$(INCS) -c $< -o $@
	@printf "\33c\e[3J"

clean:
	@rm -rf $(BUILD)
	@echo "Cleaned up 🧹"

fclean: clean
	@rm -f $(NAME)

re: fclean all

define progress
	$(eval COUNT=$(shell echo $$(($(COUNT) + 1))))
	@echo "[ $(COUNT)/$(TOTAL) ] [$(CFLAGS)] Compiling: $<\r"
endef
