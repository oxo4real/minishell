/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:12:42 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/03/02 11:16:53 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H
# include "utils_bonus.h"
# include <dirent.h>
# include <stdbool.h>
# include <sys/wait.h>

# define SH_NAME "minishell"
# define UNEXPECTED_TK "syntax error near unexpected token"
# define SYNTAX_ERR "syntax error"
# define BOLD_RED "\033[1;31m"
# define RESET "\033[0m"
# define WR_END 1
# define RD_END 0
# define IN_MODE 0x601
# define APPNED_MODE 0x209
# define SEP 0x07

typedef enum e_token
{
	PIPE,
	HEREDOC,
	LPR,
	RPR,
	AND,
	OR,
	APPEND,
	OUT,
	IN,
	STR,
	END
}					t_token;

extern int			g_sig;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_slist
{
	char			*str;
	struct s_slist	*next;
}					t_slist;

typedef struct s_redir
{
	char			*filename;
	struct s_redir	*next;
	t_token			type;
	int				fd;
}					t_redir;

typedef struct s_node
{
	t_token			type;
	char			*cmd;
	char			**args;
	t_redir			*redir;
	int				fd[2];
	struct s_node	*r_child;
	struct s_node	*next;
	struct s_node	*l_child;
}					t_node;

typedef struct s_exec
{
	t_env			*lst;
	char			**env;
	t_node			*head;
	int				fds[2];
	int				status;
}					t_exec;

void				print_unexpected(char *msg);
void				print_syntax_error(char *msg);

// ########################## - NODE - ###########################
t_node				*nodenew(t_token type, char *cmd);
t_node				*nodelast(t_node *node);
void				nodeadd_back(t_node **head, t_node *new_node);
void				nodeadd_front(t_node **node, t_node *new_node);
void				free_node(t_node *node);
void				clear_nodes(t_node **head);
// ########################## - NODE - ###########################

// ########################## - REDIR - ###########################
t_redir				*redirnew(t_token type, char *filename);
t_redir				*redirlast(t_redir *redir);
void				rediradd_back(t_redir **head, t_redir *new_redir);
void				free_redir(t_redir *redir);
void				clear_redir(t_redir **head);
// ########################## - REDIR - ###########################

// ########################## - TOKEN - ##########################
t_token				match_tk(char *s);
char				*match_tk_str(t_token type);
char				*match_tk_name(t_token type);
bool				is_cmd(char *s);
bool				is_redir(char *s);
bool				is_valid_filename_end(char *s, char q);
t_token				next_token(char *s);
bool				is_space(char c);
void				toggle_q(char c, char *q);
int					tk_prec(t_token type);
bool				check_begining(char *s, t_exec *x);
char				*strdup_to(const char *str, size_t size);
// ########################## - TOKEN - ##########################

// ####################### - TOKENIZER - #########################
bool				tokenizer(char *s, t_exec *x);
int					handle_node(char *s, int *i, t_exec *x);
int					handle_par(char *s, int *i, int *par, t_exec *x);
t_node				*handle_cmd(char *s, int *i, t_exec *x);
bool				look_for_redir(t_node *node);
// ####################### - TOKENIZER - #########################

// ######################## - PARSING - ##########################
t_node				*parser(char *line, t_exec *x);
char				*polish_arg(char *s);
char				**cmdtoav(char **cmd, t_env *env_lst, t_exec *x);
char				*getenv_(char *key, t_env *env_lst);
// ######################## - PARSING - ##########################

// ########################## - TREE - ###########################
void				free_tree(t_node *head);
// ########################## - TREE - ###########################

// ##################### - SHUNTING YARD - #######################
t_node				*shunting_yard(t_node *head);
void				move_and_convrt(t_node **polished, t_node **op);
t_node				*pop_node(t_node **head);
// ##################### - SHUNTING YARD - #######################

// ######################### - ENV - #############################
char				**envlsttoenv(t_env *env_lst);
t_env				*envtoenvlst(char **env);
void				envlstclear(t_env **env_lst);
void				freestrarr(char ***arr);
char				**split_var(char *var);
int					expandenvlst(t_env **env_lst, char **splited);
int					envlstlen(t_env *env_lst);
void				replaceenvar(t_env *env_lst, char **str, t_exec *x, bool skip_quotes);
void				sptobel(char *str);
void				rm_06(char *str);
// ######################### - ENV - #############################

// ####################### - WILDCARD - ##########################
void				*free_slist(t_slist *slist);
char				*joinslist(t_slist *slist, char *sep);
int					match_wildcard(char *s, char *p);
t_slist				*insert_sorted(t_slist **head, char *str);
char				*getsortedwildcard(char *wildcard);
void				replacewildcards(char **str);
// ####################### - WILDCARD - ##########################

t_node				*pop(t_node **head);

#endif
