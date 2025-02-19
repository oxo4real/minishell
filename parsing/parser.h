/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:39:42 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/19 13:58:59 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define UNEXPECTED_TK "syntax error near unexpected token"
# define SYNTAX_ERR "syntax error"
# define SH_NAME "minishell"
# define BOLD_RED "\033[1;31m"
# define RESET "\033[0m"

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

typedef struct s_redir
{
	t_token			type;
	char			*filename;
	struct s_redir	*next;
}					t_redir;

typedef struct s_node
{
	t_token			type;
	char			*cmd;
	t_redir			*redir;
	struct s_node	*r_child;
	struct s_node	*next;
	struct s_node	*l_child;
}					t_node;

void				*ft_memcpy(void *dst, const void *src, size_t n);
char				*ft_strdup(const char *str);
size_t				ft_strlen(const char *s);
char				*ft_strtrim(char const *s1, char const *set);
void				*ft_calloc(size_t count, size_t size);
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
bool				check_begining(char *s);
char				*strdup_to(const char *str, size_t size);
// ########################## - TOKEN - ##########################

// ####################### - TOKENIZER - #########################
bool				tokenizer(char *s, t_node **nodes);
int					handle_node(t_node **head, char *s, int *i);
bool				handle_par(char *s, int *i, t_node **nodes, int *par);
t_node				*handle_cmd(char *s, int *i);
bool				look_for_redir(t_node *node);
// ####################### - TOKENIZER - #########################

// ######################### - PARSER - ##########################
bool				parser(char *line);
// ######################### - PARSER - ##########################

// ########################## - TREE - ###########################
void				free_tree(t_node *head);
void				print_tree(t_node *head);
// ########################## - TREE - ###########################

// ##################### - SHUNTING YARD - #######################
t_node				*shunting_yard(t_node *head);
void				move_and_convrt(t_node **polished, t_node **op);
t_node				*pop_node(t_node **head);
// ##################### - SHUNTING YARD - #######################

#endif
