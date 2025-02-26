/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:10:44 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/26 18:06:43 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

static void	here_doc_helper(int fd[2], char *deli, t_exec *x)
{
	char	*line;
	char	*buff;

	signal(SIGINT, interrupt_herdoc);
	buff = NULL;
	rl_catch_signals = 1;
	if (write(fd[1], NULL, 0) < 0)
		(print_error("minishell", "here_doc", "write error"), exit(1));
	while (1337)
	{
		close(fd[0]);
		line = readline("> ");
		if (!line || ft_strcmp(line, deli) == 0)
			break ;
		replaceenvar(x->lst, &line, x);
		buff = ft_strjoin(line, "\n", "");
		if (!buff)
			(close(fd[0]), close(fd[1]), free(line), exit(1));
		write(fd[1], buff, ft_strlen(buff));
		free(line);
		free(buff);
	}
	free(line);
	exit(0);
}

int	here_doc(char *deli, t_exec *x)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) < 0)
		return (print_error("minishell", "here_doc", "pipe error"), -1);
	pid = fork();
	if (pid == 0)
		here_doc_helper(fd, deli, x);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
		return (close(fd[1]), close(fd[0]), x->status = 1, -1);
	return (close(fd[1]), fd[0]);
}

static bool	do_here_doc_helper(t_redir *redir, t_exec *x)
{
	char	*tmp;

	if (!redir)
		return (0);
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			tmp = polish_arg(redir->filename);
			if (!tmp)
				return (1);
			free(redir->filename);
			redir->filename = tmp;
			redir->fd = here_doc(tmp, x);
			if (redir->fd < 0)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

bool	do_here_doc(t_node *head, t_exec *x)
{
	t_node	*stack;
	t_node	*curr;

	stack = NULL;
	curr = head;
	if (!curr)
		return (0);
	nodeadd_front(&stack, curr);
	while (stack)
	{
		curr = pop(&stack);
		if (do_here_doc_helper(curr->redir, x))
			return (1);
		if (curr->r_child)
			nodeadd_front(&stack, curr->r_child);
		if (curr->l_child)
			nodeadd_front(&stack, curr->l_child);
	}
	return (0);
}
