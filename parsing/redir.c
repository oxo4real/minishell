/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:52:28 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/19 13:04:39 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redir	*redirnew(t_token type, char *filename)
{
	t_redir	*new;

	new = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = type;
	new->filename = filename;
	new->next = NULL;
	return (new);
}

t_redir	*redirlast(t_redir *redir)
{
	t_redir	*tmp;

	if (!redir)
		return (NULL);
	tmp = redir;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void	rediradd_back(t_redir **head, t_redir *new_redir)
{
	t_redir	*last;

	if (!head || !new_redir)
		return ;
	if (!*head)
		*head = new_redir;
	else
	{
		last = redirlast(*head);
		last->next = new_redir;
	}
}

void	free_redir(t_redir *redir)
{
	if (!redir)
		return ;
	if (redir->filename)
		(free(redir->filename), redir->filename = NULL);
	free(redir);
}

void	clear_redir(t_redir **head)
{
	t_redir	*tmp;

	if (!*head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		free_redir(*head);
		*head = tmp;
	}
	*head = NULL;
}
