/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhayyoun <mhayyoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 21:50:53 by mhayyoun          #+#    #+#             */
/*   Updated: 2025/02/27 09:40:22 by mhayyoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int		g_sig = 0;

char	*get_line(void)
{
	char	*line;
	int		fd;
	char	*prompt;

	if (isatty(STDIN_FILENO))
	{
		prompt = BOLD_RED SH_NAME " > " RESET;
		if (g_sig)
		{
			if (g_sig == 130)
				write(STDERR_FILENO, "\n", 1);
			g_sig = 0;
		}
		fd = dup(1);
		dup2(2, 1);
		line = readline(prompt);
		dup2(fd, 1);
		close(fd);
	}
	else
		line = get_next_line(0);
	return (line);
}

void	init(int fds[2], char *env[], t_exec *x)
{
	fds[1] = dup(STDOUT_FILENO);
	fds[0] = dup(STDIN_FILENO);
	signal(SIGINT, interrupt);
	signal(SIGQUIT, quit);
	x->lst = envtoenvlst(env);
	x->status = 0;
	rl_catch_signals = 0;
	init_env(&x->lst, x);
}

void	reset_in_out(t_exec *x)
{
	dup2(x->fds[1], 1);
	dup2(x->fds[0], 0);
}

int	main(int ac, char *av[], char *env[])
{
	char	*line;
	t_exec	x;

	((void)ac, (void)av);
	init(x.fds, env, &x);
	while (1337)
	{
		line = get_line();
		if (!line)
		{
			rl_clear_history();
			if (isatty(STDIN_FILENO))
				printf("exit\n");
			break ;
		}
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		(executor(parser(line, &x), &x), reset_in_out(&x));
	}
	envlstclear(&x.lst);
	return (x.status);
}
