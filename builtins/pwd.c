/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:09:36 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/24 12:22:41 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd(void)
{
	char	*cwd;

	if (write(1, NULL, 0) < 0)
		return (print_error("minishell", "pwd", "write error"));
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (print_error("minishell", "pwd", NULL));
	else
		return (printf("%s\n", cwd), free(cwd));
}
