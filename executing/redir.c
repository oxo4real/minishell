/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:55:48 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/25 20:51:16 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

static bool	handle_redir_helper_more(t_token tk, t_node *head, t_redir *r)
{
	if (tk == IN || tk == HEREDOC)
	{
		close(head->fd[RD_END]);
		if (tk == HEREDOC)
			head->fd[RD_END] = r->fd;
		else
			head->fd[RD_END] = open(r->filename, O_RDONLY);
		if (head->fd[RD_END] < 0)
		{
			print_error(SH_NAME, NULL, r->filename);
			return (1);
		}
	}
	return (0);
}

static bool	handle_redir_helper(t_token tk, t_node *head, t_redir *r)
{
	if (tk == OUT || tk == APPEND)
	{
		close(head->fd[WR_END]);
		if (tk == APPEND)
			head->fd[WR_END] = open(r->filename, APPNED_MODE, 0644);
		else
			head->fd[WR_END] = open(r->filename, IN_MODE, 0644);
		if (head->fd[WR_END] < 0)
		{
			print_error(SH_NAME, NULL, r->filename);
			return (1);
		}
	}
	if (handle_redir_helper_more(tk, head, r))
		return (1);
	return (0);
}

int	av_len(char **av)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (av && av[i])
	{
		if (*av[i])
			count++;
		i++;
	}
	return (count);
}

char	*handle_redir_name(t_exec *x, t_redir *r)
{
	char	*tmp;
	char	**new;

	tmp = ft_strdup(r->filename);
	if (!tmp)
		return (NULL);
	new = cmdtoav(&r->filename, x->lst, x);
	if (!new)
		return (free(tmp), NULL);
	if (av_len(new) != 1)
	{
		print_error2(SH_NAME, tmp, "ambiguous redirect", 0);
		x->status = 1;
		(free(tmp), freestrarr(&new));
		return (NULL);
	}
	free(tmp);
	tmp = ft_strdup(new[0]);
	(freestrarr(&new), free(r->filename), r->filename = NULL);
	if (!tmp)
		return (NULL);
	return (tmp);
}

bool	handle_redir(t_node *head, t_exec *x)
{
	t_redir	*r;

	if (!head || !head->redir)
		return (0);
	x->status = 1;
	r = head->redir;
	while (r)
	{
		r->filename = handle_redir_name(x, r);
		if (!r->filename)
			return (1);
		if (handle_redir_helper(r->type, head, r))
			return (1);
		r = r->next;
	}
	x->status = 0;
	return (0);
}
