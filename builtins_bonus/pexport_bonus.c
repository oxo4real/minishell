/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pexport_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:49:12 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/27 11:10:49 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins_bonus.h"

void	pexport(t_env *env_lst)
{
	while (env_lst)
	{
		printf("declare -x %s", env_lst->key);
		if (env_lst->value)
			printf("=\"%s\"", env_lst->value);
		printf("\n");
		env_lst = env_lst->next;
	}
}
