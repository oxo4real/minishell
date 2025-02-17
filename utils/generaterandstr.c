/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generaterandstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 12:07:29 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/17 13:01:12 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#define MAX_SIZE 50
#define MIN_SIZE 10

char	*ft_strjoin(char const *s1, char const *s2, char const *sep);

char	*generaterandstr(void)
{
	void				*allocated;
	unsigned long long	rand;
	int					length;
	char				*rendu;

	allocated = malloc(1);
	if (!allocated)
		return (NULL);
	rand = (unsigned long long)allocated;
	free(allocated);
	length = MIN_SIZE + (rand % (MAX_SIZE - MIN_SIZE + 1));
	rendu = (char *)malloc(sizeof(char) * (length + 1));
	if (!rendu)
		return (NULL);
	rendu[--length] = '\0';
	while (length--)
	{
		allocated = malloc(1);
		if (!allocated)
			return (free(rendu), NULL);
		rand = (unsigned long long)allocated + rand * 7;
		free(allocated);
		rendu[length] = 97 + (rand % (122 - 97 + 1));
	}
	return (ft_strjoin(".", rendu, ""));
}
