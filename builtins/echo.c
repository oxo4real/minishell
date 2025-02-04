/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:58:42 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/04 15:08:54 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strcmp(const char *s1, const char *s2);

void	echo(char **av)
{
	int	newline = 1;
	int	start = 1;
	int	i;
	
	if (av[1] && ft_strcmp(av[1], "-n") == 0)
	{
		newline = 0;
		start = 2;
	}
	i = start;
	while (av[i])
	{
		printf("%s", av[i]);
		if (av[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
