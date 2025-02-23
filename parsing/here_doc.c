/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:10:44 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/23 14:57:55 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>

int	here_doc(t_env *env_lst, char *deli)
{
	char	*line;
	char	*buff;
	int		fd[2];

	if (pipe(fd) < 0)
		return (-1);
	buff = NULL;
	while (1337)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, deli) == 0)
			break ;
		replaceenvar(env_lst, &line);
		buff = ft_strjoin(line, "\n", "");
		if (!buff)
			return (close(fd[0]), close(fd[1]), free(line), 1);
		write(fd[1], buff, ft_strlen(buff));
		free(line);
		free(buff);
	}
	free(line);
	return (close(fd[1]), fd[0]);
}

static bool	do_here_doc_helper(t_redir *redir, t_env *env_lst)
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
			redir->fd = here_doc(env_lst, tmp);
			if (redir->fd < 0)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

bool	do_here_doc(t_node *head, t_env *env_lst)
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
		if (do_here_doc_helper(curr->redir, env_lst))
			return (1);
		if (curr->r_child)
			nodeadd_front(&stack, curr->r_child);
		if (curr->l_child)
			nodeadd_front(&stack, curr->l_child);
	}
	return (0);
}
