/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec__bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:02:49 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/03/02 13:42:57 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing_bonus.h"

static void	exec_child(t_node *head, t_exec *x)
{
	execve(head->args[0], head->args, x->env);
	if (x->status == 126 && errno == ENOENT)
		(print_error(SH_NAME, 0, head->args[0]), x->status = 127);
	else if (x->status == 126)
		print_error2(SH_NAME, head->args[0], "is a directory", 0);
	else if (x->status == 127)
		print_error2(SH_NAME, head->args[0], "command not found", 0);
	else
		exit(1);
	exit(x->status);
}

void	exec_cmd_helper(t_node *head, t_exec *x, int prev[2])
{
	int	pid;

	pid = fork();
	if (if_fork(pid))
		return ;
	if (pid == 0)
		exec_child(head, x);
	close(head->fd[WR_END]);
	close(head->fd[RD_END]);
	waitpid(pid, &x->status, 0);
	if (WIFEXITED(x->status))
	{
		x->status = WEXITSTATUS(x->status);
		g_sig = 0;
	}
	else if (WIFSIGNALED(x->status))
		x->status = WTERMSIG(x->status) + 128;
	if (prev[WR_END] != -42)
		dup2(prev[WR_END], 1);
	if (prev[RD_END] != -42)
		dup2(prev[RD_END], 0);
}

static void	redir_help(t_node *head, int prev[2])
{
	if (head->fd[WR_END] != -42)
	{
		prev[WR_END] = dup(STDOUT_FILENO);
		if (dup2(head->fd[WR_END], 1) < 0)
			return ;
		close(head->fd[WR_END]);
	}
	if (head->fd[RD_END] != -42)
	{
		prev[RD_END] = dup(STDIN_FILENO);
		if (dup2(head->fd[RD_END], 0) < 0)
			return ;
		close(head->fd[RD_END]);
	}
}

void	exec_cmd(t_node *head, t_exec *x)
{
	int	prev[2];

	prev[0] = -42;
	prev[1] = -42;
	if (handle_redir(head, x))
		return ;
	if (!head->cmd)
		return ;
	head->args = cmdtoav(&head->cmd, x->lst, x);
	if (!head->args || !head->args[0])
		return ;
	redir_help(head, prev);
	if (builtins(head, x))
	{
		if (prev[WR_END] != -42)
			dup2(prev[WR_END], 1);
		if (prev[RD_END] != -42)
			dup2(prev[RD_END], 0);
		return ;
	}
	head->args[0] = get_path(head->args[0], x);
	if (!head->args[0])
		return ;
	exec_cmd_helper(head, x, prev);
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
