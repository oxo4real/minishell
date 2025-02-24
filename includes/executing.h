/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:52:00 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/24 14:54:23 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

# include "parsing.h"
# include <fcntl.h>

typedef struct s_exec
{
	t_env	*lst;
	char	**env;
	int		status;
}			t_exec;

void		executor(t_node *head, t_exec *x);
void		exec_cmd(t_node *head, t_exec *x);
void		exec_(t_node *head, t_exec *x);
void		exec_pipe(t_node *head, t_exec *x);
char		*get_path(char *cmd);
void		expand_cmds(t_node *head, t_exec *x);
bool		builtins(t_node *head, t_exec *x);
bool		handle_redir(t_node *head, t_env *env_lst);
void		set_shlvl(t_env **env_lst);

#endif
