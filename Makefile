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

B_SRCS =

#UTILS
B_SRCS += utils_bonus/free2darr_bonus.c utils_bonus/ft_atoi_bonus.c utils_bonus/ft_calloc_bonus.c utils_bonus/ft_isalnum_bonus.c utils_bonus/ft_isalpha_bonus.c \
		utils_bonus/ft_isdigit_bonus.c utils_bonus/ft_itoa_bonus.c utils_bonus/ft_memcpy_bonus.c utils_bonus/ft_putchar_fd_bonus.c utils_bonus/ft_putnbr_fd_bonus.c \
		utils_bonus/ft_putstr_fd_bonus.c utils_bonus/ft_split_bonus.c utils_bonus/ft_strchr_bonus.c utils_bonus/ft_strcmp_bonus.c utils_bonus/ft_strdup_bonus.c \
		utils_bonus/ft_strjoin_bonus.c utils_bonus/ft_strlen_bonus.c utils_bonus/ft_strncmp_bonus.c utils_bonus/ft_strtrim_bonus.c utils_bonus/ft_wordcmp_bonus.c \
		utils_bonus/generaterandstr_bonus.c utils_bonus/is_long_bonus.c utils_bonus/print_error_bonus.c utils_bonus/print_error2_bonus.c utils_bonus/print_error3_bonus.c \
		utils_bonus/get_next_line_bonus.c utils_bonus/get_next_line_utils_bonus.c
#UTILS

#PARSING
B_SRCS += parsing_bonus/envlstclear_bonus.c parsing_bonus/envlsttoenv_bonus.c parsing_bonus/envtoenvlst_bonus.c parsing_bonus/expandenvlst_bonus.c \
		parsing_bonus/getsortedwildcard_bonus.c parsing_bonus/getsortedwildcard_utils_bonus.c parsing_bonus/print_syntax_error_bonus.c \
		parsing_bonus/match_wildcard_bonus.c parsing_bonus/node_bonus.c parsing_bonus/parser_bonus.c parsing_bonus/readline_bonus.c parsing_bonus/tree_utils_bonus.c \
		parsing_bonus/replaceenvvar_bonus.c parsing_bonus/replacewildcards_bonus.c parsing_bonus/shunting_yard_bonus.c parsing_bonus/splitvar_bonus.c \
		parsing_bonus/sptobel_bonus.c parsing_bonus/tk_match_bonus.c parsing_bonus/tk_types_bonus.c parsing_bonus/tk_utils_bonus.c parsing_bonus/tokenizer_bonus.c \
		parsing_bonus/tokenizer_handle_cmd_bonus.c parsing_bonus/tokenizer_handle_par_bonus.c parsing_bonus/tokenizer_handle_redir_bonus.c \
		parsing_bonus/extract_args_bonus.c parsing_bonus/cmdtoav_bonus.c parsing_bonus/getenv__bonus.c parsing_bonus/print_unexpected_bonus.c \
		parsing_bonus/redir_bonus.c
		
#PARSING

#BUILTINS
B_SRCS += builtins_bonus/cd_bonus.c builtins_bonus/echo_bonus.c builtins_bonus/env__bonus.c builtins_bonus/exit__bonus.c builtins_bonus/export_bonus.c builtins_bonus/pexport_bonus.c \
		builtins_bonus/pwd_bonus.c builtins_bonus/unset_bonus.c
#BUILTINS

#EXECUTING
B_SRCS += executing_bonus/cmd_bonus.c executing_bonus/exec__bonus.c executing_bonus/executor_bonus.c executing_bonus/get_path_bonus.c executing_bonus/redir_bonus.c \
		executing_bonus/builtins_bonus.c executing_bonus/set_shlvl_bonus.c executing_bonus/init_env_bonus.c executing_bonus/signals_bonus.c executing_bonus/exec_pipe_bonus.c \
		executing_bonus/here_doc_bonus.c executing_bonus/expander_bonus.c
#EXECUTING


BUILD = build
BUILD_BONUS = build_bonus
BONUSDIR = $(BUILD_BONUS)/.bonus
OBJS = $(patsubst %.c, $(BUILD)/%.o, $(SRCS))
BOBJS = $(patsubst %.c, $(BUILD_BONUS)/%.o, $(B_SRCS))
INCS = includes
INCS_BONUS = includes_bonus
HEADERS = $(INCS)/parsing.h $(INCS)/utils.h $(INCS)/builtins.h $(INCS)/executing.h
HEADERS_BONUS = $(INCS_BONUS)/parsing_bonus.h $(INCS_BONUS)/utils_bonus.h $(INCS_BONUS)/builtins_bonus.h $(INCS_BONUS)/executing_bonus.h
NAME = minishell
TOTAL := $(words $(OBJS))
COUNT := 0

all: $(NAME)

$(NAME): $(OBJS)
	@rm -f $(BONUSDIR)
	@$(CC) $(CFLAGS) $^ -o $(NAME) -lreadline
	@echo "compiled ✅"

bonus: $(BONUSDIR)
$(BONUSDIR): $(BOBJS)
	@rm -rf $(BUILD)
	@$(CC) $(CFLAGS) $^ -o $(NAME) -lreadline
	@touch $(BONUSDIR)

$(BUILD)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(call progress)
	@$(CC) $(CFLAGS) -I$(INCS) -c $< -o $@
	@printf "\33c\e[3J"

$(BUILD_BONUS)/%.o: %.c $(HEADERS_BONUS)
	@mkdir -p $(dir $@)
	$(call progress)
	@$(CC) $(CFLAGS) -I$(INCS_BONUS) -c $< -o $@
	@printf "\33c\e[3J"

clean:
	@rm -rf $(BUILD)
	@rm -rf $(BUILD_BONUS)
	@echo "Cleaned up 🧹"

fclean: clean
	@rm -f $(NAME)

re: fclean all

define progress
	$(eval COUNT=$(shell echo $$(($(COUNT) + 1))))
	@echo "[ $(COUNT)/$(TOTAL) ] [$(CFLAGS)] Compiling: $<\r"
endef
