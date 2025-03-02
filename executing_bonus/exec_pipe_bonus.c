/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:38:21 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/03/02 13:41:42 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing_bonus.h"

bool	if_fork(int pid)
{
	if (pid < 0)
	{
		print_error2(SH_NAME, "fork", "Resource temporarily unavailable", 0);
		return (1);
	}
	return (0);
}

int	exec_lpipe(t_node *head, t_exec *x, int fds[2])
{
	int	pid;

	pid = fork();
	if (if_fork(pid))
		return (-1);
	if (pid == 0)
	{
		if (dup2(fds[WR_END], 1) < 0)
			return (1);
		(close(fds[WR_END]), close(fds[RD_END]));
		exec_(head->l_child, x);
		exit(x->status);
	}
	return (pid);
}

int	exec_rpipe(t_node *head, t_exec *x, int fds[2])
{
	int	pid;

	pid = fork();
	if (if_fork(pid))
		return (-1);
	if (pid == 0)
	{
		if (dup2(fds[RD_END], 0) < 0)
			return (1);
		(close(fds[WR_END]), close(fds[RD_END]));
		exec_(head->r_child, x);
		exit(x->status);
	}
	return (pid);
}

void	exec_pipe(t_node *head, t_exec *x)
{
	int	fds[2];
	int	pid1;
	int	pid2;

	if (pipe(fds) < 0)
	{
		print_error2(SH_NAME, "pipe", "Resource temporarily unavailable", 0);
		return ;
	}
	pid1 = exec_lpipe(head, x, fds);
	pid2 = exec_rpipe(head, x, fds);
	(close(fds[WR_END]), close(fds[RD_END]));
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &x->status, 0);
	x->status = WEXITSTATUS(x->status);
}
