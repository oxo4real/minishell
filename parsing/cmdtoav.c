/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdtoav.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:59:26 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/24 19:03:59 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**cmdtoav(char *cmd, t_env *env_lst)
{
	replaceenvar(env_lst, &cmd);
	sptobel(cmd);
	replacewildcards(&cmd);
	return (ft_split(cmd, '\x07'));
}
