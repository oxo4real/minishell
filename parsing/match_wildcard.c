/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:53:01 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/16 19:05:53 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	checkallstars(const char *p);
static int	the_damn_qotes(char **p, char **s);

int	match_wildcard(char *s, char *p)
{
	char	*last_star;
	char	*tmp;

	last_star = NULL;
	while (*s)
	{
		if (*p == '*')
		{
			last_star = p++;
			tmp = s;
		}
		else if ((*p == '"' || *p == '\'') && the_damn_qotes(&p, &s))
			continue ;
		else if (*p == *s && p++ && s++)
			continue ;
		else if (!last_star)
			return (0);
		else
		{
			p = last_star + 1;
			s = tmp + 1;
			tmp = s;
		}
	}
	return (checkallstars(p));
}

static int	checkallstars(const char *p)
{
	while (*p)
	{
		if (*p != '*')
			return (0);
		p++;
	}
	return (1);
}

static int	the_damn_qotes(char **p, char **s)
{
	char	delim;
	char	*pcp;
	char	*scp;
	int		increment;

	increment = 0;
	pcp = *p;
	scp = *s;
	delim = *pcp;
	pcp++;
	while (*pcp != delim)
	{
		if (*(pcp++) != *(scp++))
			return (0);
		increment++;
	}
	(*p) += increment + 2;
	(*s) += increment;
	return (1);
}
