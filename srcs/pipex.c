/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 19:10:42 by mneves-l          #+#    #+#             */
/*   Updated: 2023/07/05 15:04:24 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// pipe - fd[0] = outfile - so posso ler fd[1] = infile - so posso escrever

#include "pipex.h"

void	child1_process(char **av, int *pipefd, char **envp)
{
	int	infile;
	int	dups[2];

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
	{
		perror("Error opening the infile");
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	dups[0] = dup2(infile, STDIN_FILENO);
	dups[1] = dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	execute_cmd(av[2], envp, NULL);
	close(infile);
	close(dups[0]);
	close(dups[1]);
	exit(EXIT_FAILURE);
}

void	child2_process(char **av, int *pipefd, char **envp)
{
	int	outfile;
	int	dups[2];

	outfile = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (outfile < 0)
	{
		perror("Error opening the outfile");
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	dups[0] = dup2(pipefd[0], STDIN_FILENO);
	dups[1] = dup2(outfile, STDOUT_FILENO);
	close(pipefd[0]);
	execute_cmd(av[3], envp, NULL);
	close(outfile);
	close(dups[0]);
	close(dups[1]);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
{
	int		pipefd[2];
	pid_t	child1;
	pid_t	child2;

	if (ac != 5)
	{
		ft_putendl_fd("Syntax should be: ./pipex infile cmd1 cmd2 outfile", 2);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) < 0)
		error();
	child1 = fork();
	if (child1 < 0)
		error();
	if (child1 == 0)
		child1_process(av, pipefd, envp);
	child2 = fork();
	if (child2 < 0)
		error();
	if (child2 == 0)
		child2_process(av, pipefd, envp);
	waitpid(child1, NULL, 0);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
