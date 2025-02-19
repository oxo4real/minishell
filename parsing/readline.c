/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:50:53 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/19 17:38:33 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <readline/history.h>
#include <readline/readline.h>

void	print_unexpected(char *msg)
{
	printf("%s: %s `%s'\n", SH_NAME, UNEXPECTED_TK, msg);
}

void	print_syntax_error(char *msg)
{
	printf("%s: %s: %s\n", SH_NAME, SYNTAX_ERR, msg);
}

// void	leaks(void)
// {
// 	system("leaks -q a.out");
// }

int	main(void)
{
	char	*line;
	int		fd;

	// atexit(leaks);
	while (1337)
	{
		fd = dup(1);
		dup2(2, 1);
		line = readline(BOLD_RED SH_NAME " > " RESET);
		dup2(fd, 1);
		if (!line)
		{
			rl_clear_history();
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		parser(line);
	}
	return (0);
}
