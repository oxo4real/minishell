/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:41:44 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/23 13:30:13 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_node	*nodenew(t_token type, char *cmd)
{
	t_node	*new;

	new = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new)
		return (NULL);
	new->type = type;
	new->cmd = cmd;
	new->fd[WR_END] = -42;
	new->fd[RD_END] = -42;
	return (new);
}

t_node	*nodelast(t_node *node)
{
	t_node	*tmp;

	if (!node)
		return (NULL);
	tmp = node;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

void	nodeadd_back(t_node **head, t_node *new_node)
{
	t_node	*last;

	if (!head || !new_node)
		return ;
	if (!*head)
		*head = new_node;
	else
	{
		last = nodelast(*head);
		last->next = new_node;
	}
}

void	nodeadd_front(t_node **node, t_node *new_node)
{
	if (!new_node)
		return ;
	new_node->next = *node;
	*node = new_node;
}

void	clear_nodes(t_node **head)
{
	t_node	*tmp;

	if (!*head)
		return ;
	while (*head)
	{
		tmp = (*head)->next;
		free_node(*head);
		*head = tmp;
	}
	*head = NULL;
}
