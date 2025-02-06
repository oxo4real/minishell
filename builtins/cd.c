/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:10:52 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/06 10:54:20 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_error(char *shell_name, char *command, char *details);

void	cd(char **av)
{
	if (!av)
		return ;
	if (chdir(av[1]) != 0)
		print_error("minishell", "cd", av[1]);
}
