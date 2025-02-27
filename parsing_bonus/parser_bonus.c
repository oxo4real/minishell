/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:15:44 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 11:39:17 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

t_node	*pop(t_node **head)
{
	t_node	*poped;

	poped = NULL;
	if (!*head)
		return (NULL);
	poped = *head;
	*head = poped->next;
	poped->next = NULL;
	return (poped);
}

t_node	*parser(char *line, t_exec *x)
{
	char	*s;

	x->head = NULL;
	s = ft_strtrim(line, " \t\v\n\f\r");
	free(line);
	if (!s)
		return (NULL);
	if (check_begining(s, x))
		return (free(s), NULL);
	if (tokenizer(s, x))
		return (free(s), clear_nodes(&x->head), NULL);
	free(s);
	return (shunting_yard(x->head));
}
