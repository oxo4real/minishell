/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 21:02:49 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:31:15 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

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

void	exec_cmd_helper(t_node *head, t_exec *x)
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
	reset_in_out(x);
}

void	exec_cmd(t_node *head, t_exec *x)
{
	if (handle_redir(head, x))
		return ;
	if (!head->cmd)
		return ;
	head->args = cmdtoav(&head->cmd, x->lst, x);
	if (!head->args || !head->args[0])
		return ;
	if (head->fd[WR_END] != -42)
	{
		if (dup2(head->fd[WR_END], 1) < 0)
			return ;
		close(head->fd[WR_END]);
	}
	if (head->fd[RD_END] != -42)
	{
		if (dup2(head->fd[RD_END], 0) < 0)
			return ;
		close(head->fd[RD_END]);
	}
	if (builtins(head, x))
		return ;
	head->args[0] = get_path(head->args[0], x);
	if (!head->args[0])
		return ;
	exec_cmd_helper(head, x);
}

bool	if_fork(int pid)
{
	if (pid < 0)
	{
		print_error2(SH_NAME, "fork", "Resource temporarily unavailable", 0);
		return (1);
	}
	return (0);
}

void	exec_(t_node *head, t_exec *x)
{
	if (!head)
		return ;
	if (head->type == STR)
		exec_cmd(head, x);
	if (head->type == PIPE)
		exec_pipe(head, x);
}
