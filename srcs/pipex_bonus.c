/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:13:40 by mneves-l          #+#    #+#             */
/*   Updated: 2023/07/05 16:13:10 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_here_doc(int *pipefd, char *limiter)
{
	char	*line;

	line = NULL;
	close(pipefd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (!ft_strncmp(line, limiter, ft_strlen(line) - 1) && \
			!ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipefd[1]);
	exit(0);
}

void	here_doc(char *limiter, int ac)
{
	pid_t	child;
	int		pipefd[2];

	if (ac < 6)
		problem();
	if (pipe(pipefd) < 0)
		error();
	child = fork();
	if (child < 0)
		error();
	if (child == 0)
		process_here_doc(pipefd, limiter);
	else
	{
		waitpid(-1, NULL, 0);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	infile;
	int	i;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 9) == 0)
		{
			i = 3;
			here_doc(av[2], ac);
		}
		else
		{
			i = 2;
			infile = open_files(av[1], 0);
			dup2(infile, STDIN_FILENO);
			close(infile);
		}
		process(ac, av, envp, i);
	}
	else
		problem();
}
