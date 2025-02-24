/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtoav.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:59:26 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/24 20:20:05 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**cmdtoav(char **cmd, t_env *env_lst)
{
	replaceenvar(env_lst, cmd);
	sptobel(*cmd);
	replacewildcards(cmd);
	return (ft_split(*cmd, SEP));
}
