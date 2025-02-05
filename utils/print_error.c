/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaghzal <aaghzal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:54:13 by aaghzal           #+#    #+#             */
/*   Updated: 2025/02/05 15:26:45 by aaghzal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	ft_putstr_fd(char const *s, int fd);

void	print_error(char *shell_name, char *command, char *details)
{
	ft_putstr_fd(shell_name, STDERR_FILENO);
	if (shell_name)
		ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	if (command)
		ft_putstr_fd(": ", STDERR_FILENO);
	perror(details);
}
