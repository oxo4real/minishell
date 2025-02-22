/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:02:49 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/22 21:14:02 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	exec_cmd(t_node *head, char **env, int *status)
{
	int	pid;

	if (!head->cmd)
		return ;
	head->args = extract_args(head->cmd);
	if (!head->args)
		return ;
	head->args[0] = get_path(head->args[0]);
	if (!head->args[0])
		return ;
	pid = fork();
	if (pid == 0)
	{
		execve(head->args[0], head->args, env);
		printf(SH_NAME ": %s: command not found\n", head->args[0]);
		exit(127);
	}
	waitpid(pid, status, 0);
	g_gb.ex_code = WEXITSTATUS(*status);
}

void	exec_pipe(t_node *head, char **env, int *status)
{
	int	fds[2];
	int	pid1;
	int	pid2;

	pipe(fds);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fds[WR_END], 1);
		(close(fds[WR_END]), close(fds[RD_END]));
		exec_(head->l_child, env);
		exit(g_gb.ex_code);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fds[RD_END], 0);
		(close(fds[WR_END]), close(fds[RD_END]));
		exec_(head->r_child, env);
		exit(g_gb.ex_code);
	}
	(close(fds[WR_END]), close(fds[RD_END]));
	waitpid(pid1, status, 0);
	waitpid(pid2, status, 0);
	g_gb.ex_code = *status;
}

void	exec_(t_node *head, char **env)
{
	int	status;

	if (!head)
		return ;
	if (head->type == STR)
		exec_cmd(head, env, &status);
	if (head->type == OR)
	{
		exec_(head->l_child, env);
		if (g_gb.ex_code != 0)
			exec_(head->r_child, env);
	}
	if (head->type == AND)
	{
		exec_(head->l_child, env);
		if (g_gb.ex_code == 0)
			exec_(head->r_child, env);
	}
	if (head->type == PIPE)
		exec_pipe(head, env, &status);
}
