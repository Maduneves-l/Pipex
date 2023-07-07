/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:03:07 by mneves-l          #+#    #+#             */
/*   Updated: 2023/07/05 15:24:49 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	problem(void)
{
	ft_putendl_fd("\033[31mError: Bad argument!", 2);
	ft_putendl_fd("Ex: ./pipex infile cmd1 cmd2 ... outfile", 2);
	ft_putendl_fd(\
		"./pipex here_doc LIMITER cmd1 cmd2 ... <outfile>\033[0m", 2);
	exit(EXIT_FAILURE);
}

int	open_files(char *av, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(av, O_RDONLY);
	else if (i == 1)
		file = open(av, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (file < 0)
	{
		perror("Error opening the infile/outfile");
		exit(EXIT_FAILURE);
	}
	return (file);
}

int	child_process(char *av, char **envp, int *pids)
{
	pid_t	child;
	int		pipefd[2];
	int		dupfd;

	if (pipe(pipefd) < 0)
		error();
	child = fork();
	if (child < 0)
		error();
	if (child == 0)
	{
		dupfd = dup2(pipefd[1], STDOUT_FILENO);
		(close(pipefd[1]), close(pipefd[0]));
		execute_cmd(av, envp, pids);
		close(dupfd);
		close(STDIN_FILENO);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(STDIN_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		(close(pipefd[0]), close(pipefd[1]));
	}
	return (child);
}

void	last_process(char *file, char *arg, char **envp, int *pids)
{
	int	outfile;
	int	dupfd;

	outfile = open_files(file, 1);
	dupfd = dup2(outfile, STDOUT_FILENO);
	execute_cmd(arg, envp, pids);
	close(outfile);
	close(dupfd);
	close(STDIN_FILENO);
	exit(EXIT_FAILURE);
}

void	process(int ac, char **av, char **envp, int i)
{
	int	j;
	int	*pids;

	pids = ft_calloc(sizeof(int), (ac - 2));
	j = 0;
	while (i < ac - 2)
		pids[j++] = child_process(av[i++], envp, pids);
	i = fork();
	if (i < 0)
		error();
	if (!i)
		last_process(av[ac - 1], av[ac - 2], envp, pids);
	else
	{
		j = 0;
		while (j < (ac - 2))
		{
			if (pids[j])
				waitpid(pids[j], NULL, 0);
			j++;
		}
		waitpid(i, NULL, 0);
	}
	close(STDIN_FILENO);
	free(pids);
}
