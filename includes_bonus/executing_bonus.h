/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:52:00 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:57:12 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_BONUS_H
# define EXECUTING_BONUS_H

# include "parsing_bonus.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/errno.h>

void	executor(t_node *head, t_exec *x);
void	exec_cmd(t_node *head, t_exec *x);
void	exec_(t_node *head, t_exec *x);
void	exec_pipe(t_node *head, t_exec *x);
char	*get_path(char *cmd, t_exec *x);
void	expand_cmds(t_node *head, t_exec *x);
bool	builtins(t_node *head, t_exec *x);
bool	handle_redir(t_node *head, t_exec *x);
void	set_shlvl(t_env **env_lst, t_exec *x);
void	init_env(t_env **env_lst, t_exec *x);
void	interrupt(int sig);
void	interrupt_herdoc(int sig);
void	quit(int sig);
void	reset_in_out(t_exec *x);
bool	if_fork(int pid);
bool	do_here_doc(t_node *head, t_exec *x);
bool	expander(t_exec *x, t_redir *r);

#endif
