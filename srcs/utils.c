/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 18:00:45 by mneves-l          #+#    #+#             */
/*   Updated: 2023/07/05 19:07:25 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	perror("Problem with execution");
	exit(EXIT_FAILURE);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

char	*to_path(char *cmd, char **envp)
{
	int		i;
	char	*paths;
	char	**path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	path = ft_split(paths, ':');
	free(paths);
	if (!path || !*path)
		return (NULL);
	return (path_to_cmd(cmd, path));
}

char	*path_to_cmd(char *cmd, char **path)
{
	int		i;
	char	*tmp;
	char	*final;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		final = ft_strjoin(tmp, cmd);
		if (access(final, F_OK & X_OK) != -1)
		{
			free_matrix(path);
			return (final);
		}
		free(tmp);
		free(final);
		i++;
	}
	free_matrix(path);
	return (cmd);
}

void	execute_cmd(char *cmd, char **envp, int *pids)
{
	char	*path;
	char	**execute_cmd;

	execute_cmd = ft_split(cmd, ' ');
	if (!execute_cmd || !*execute_cmd)
	{
		if (execute_cmd)
			free_matrix(execute_cmd);
		free(pids);
		return ;
	}
	cmd = *execute_cmd;
	path = to_path(cmd, envp);
	if (!path)
	{
		free(pids);
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(execute_cmd[0], 2);
		free_matrix(execute_cmd);
		return ;
	}
	if (execve(path, execute_cmd, envp) == -1)
		free(pids);
}
