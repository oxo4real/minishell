/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:53:01 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/10 13:12:17 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	checkallstars(const char *p);

int	match_wildcard(char *s, char *p)
{
	char	*last_star;
	char	*tmp;

	last_star = NULL;
	while (*s)
	{
		if (*p == *s && p++ && s++)
			;
		else if (*p == '*')
		{
			last_star = p;
			tmp = s;
			p++;
		}
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
