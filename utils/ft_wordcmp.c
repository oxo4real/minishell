/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 16:33:52 by aaghzal           #+#    #+#             */
/*   Updated: 2024/12/25 16:34:20 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_wordcmp(char *w1, char *w2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((w1[i] != '\0' && w1[i] != ' ')
		|| (w2[j] != '\0' && w2[j] != ' '))
	{
		if (w1[i] != w2[j])
			return (w1[i] - w2[j]);
		i++;
		j++;
	}
	return (0);
}
