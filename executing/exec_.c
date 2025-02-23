/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:02:49 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/23 19:45:20 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	exec_cmd_helper(t_node *head, t_exec *x)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (head->fd[WR_END] != -42)
		{
			dup2(head->fd[WR_END], 1);
			close(head->fd[WR_END]);
		}
		if (head->fd[RD_END] != -42)
		{
			dup2(head->fd[RD_END], 0);
			close(head->fd[RD_END]);
		}
		execve(head->args[0], head->args, x->env);
		dprintf(2, SH_NAME ": %s: command not found\n", head->args[0]);
		exit(127);
	}
	close(head->fd[WR_END]);
	close(head->fd[RD_END]);
	waitpid(pid, &x->status, 0);
	x->status = WEXITSTATUS(x->status);
}

void	exec_cmd(t_node *head, t_exec *x)
{
	handle_redir(head, x->lst);
	if (!head->cmd)
		return ;
	replaceenvar(x->lst, &head->cmd);
	head->args = extract_args(head->cmd);
	if (!head->args)
		return ;
	head->args[0] = get_path(head->args[0]);
	if (!head->args[0])
		return ;
	if (builtins(head, x))
		return ;
	exec_cmd_helper(head, x);
}

void	exec_pipe(t_node *head, t_exec *x)
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
		exec_(head->l_child, x);
		exit(x->status);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fds[RD_END], 0);
		(close(fds[WR_END]), close(fds[RD_END]));
		exec_(head->r_child, x);
		exit(x->status);
	}
	(close(fds[WR_END]), close(fds[RD_END]));
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &x->status, 0);
	x->status = WEXITSTATUS(x->status);
}

void	exec_(t_node *head, t_exec *x)
{
	if (!head)
		return ;
	if (head->type == STR)
		exec_cmd(head, x);
	if (head->type == OR)
	{
		exec_(head->l_child, x);
		if (x->status != 0)
			exec_(head->r_child, x);
	}
	if (head->type == AND)
	{
		exec_(head->l_child, x);
		if (x->status == 0)
			exec_(head->r_child, x);
	}
	if (head->type == PIPE)
		exec_pipe(head, x);
}
