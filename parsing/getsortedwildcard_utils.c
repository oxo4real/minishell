/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getsortedwildcard_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:24:23 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/22 20:18:26 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	*free_slist(t_slist *slist)
{
	t_slist	*next;

	while (slist)
	{
		next = slist->next;
		free(slist->str);
		free(slist);
		slist = next;
	}
	return (NULL);
}

char	*joinslist(t_slist *slist, char *sep)
{
	t_slist	*head;
	char	*rendu;
	char	*tmp;

	rendu = ft_strdup("");
	head = slist;
	if (!head || !rendu)
		return (free(rendu), free_slist(slist));
	if (!head->next)
	{
		free(rendu);
		rendu = ft_strdup(slist->str);
		return (free_slist(slist), rendu);
	}
	while (head)
	{
		tmp = ft_strjoin(rendu, head->str, sep);
		free(rendu);
		if (!tmp)
			return (free_slist(slist));
		rendu = tmp;
		head = head->next;
	}
	return (free_slist(slist), rendu);
}
