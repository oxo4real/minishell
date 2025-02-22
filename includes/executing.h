/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 20:52:00 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/22 21:10:19 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

# include "parsing.h"

void	executor(t_node *head, t_env *env_lst);
void	exec_cmd(t_node *head, char **env, int *status);
void	exec_(t_node *head, char **env);
void	exec_pipe(t_node *head, char **env, int *status);
char	*get_path(char *cmd);
void	expand_cmds(t_node *head, t_env *env_lst);

#endif
