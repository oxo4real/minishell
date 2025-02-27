/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv__bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 10:06:59 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/27 11:11:17 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

char	*getenv_(char *key, t_env *env_lst)
{
	while (env_lst)
	{
		if (ft_strcmp(env_lst->key, key) == 0)
			return (ft_strdup(env_lst->value));
		env_lst = env_lst->next;
	}
	return (NULL);
}
