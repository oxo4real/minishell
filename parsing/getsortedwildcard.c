/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getsortedwildcard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:42:17 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/24 18:49:13 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

static int		staroutquotes(char *wildcard);
static void		skipquote(int *i, char *str);
static t_slist	*getslist(char *wildcard);

char	*getsortedwildcard(char *wildcard)
{
	t_slist	*slist;

	if (!staroutquotes(wildcard))
		return (NULL);
	slist = getslist(wildcard);
	if (!slist)
		return (NULL);
	return (joinslist(slist, "\x07"));
}

static int	staroutquotes(char *wildcard)
{
	int	i;

	i = 0;
	while (wildcard[i] && wildcard[i] != '\x07')
	{
		if (wildcard[i] == '*')
			return (1);
		else if (wildcard[i] == '\'' && wildcard[i] == '"')
		{
			skipquote(&i, wildcard);
			if (!(wildcard[i] && wildcard[i] != '\x07'))
				return (0);
		}
		i++;
	}
	return (0);
}

static void	skipquote(int *i, char *str)
{
	char	quote;

	quote = str[(*i)++];
	while (str[*i] && str[*i] != quote && str[*i] != '\x07')
		(*i)++;
}

static t_slist	*getslist(char *wildcard)
{
	DIR				*dir;
	struct dirent	*file;
	t_slist			*slist;

	slist = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	while (1337)
	{
		file = readdir(dir);
		if (!file)
			return (closedir(dir), slist);
		if (!(file->d_name[0] == '.' && wildcard[0] != '.')
			&& match_wildcard(file->d_name, wildcard))
			insert_sorted(&slist, file->d_name);
	}
}

t_slist	*insert_sorted(t_slist **head, char *str)
{
	t_slist	*new_node;
	t_slist	*current;

	new_node = (t_slist *)malloc(sizeof(t_slist));
	if (!new_node)
		return (free_slist((*head)));
	new_node->str = ft_strdup(str);
	if (!new_node->str)
		return (free_slist((*head)));
	if ((*head) == NULL || ft_strcmp((*head)->str, str) >= 0)
	{
		new_node->next = (*head);
		(*head) = new_node;
	}
	else
	{
		current = (*head);
		while (current->next != NULL && ft_strcmp(current->next->str, str) < 0)
			current = current->next;
		new_node->next = current->next;
		current->next = new_node;
	}
	return ((*head));
}
