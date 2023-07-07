/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:12:06 by mneves-l          #+#    #+#             */
/*   Updated: 2023/07/05 14:39:02 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

/* Mandatory part functions */
void	error(void);
char	*to_path(char *cmd, char **envp);
void	free_matrix(char **matrix);
char	*path_to_cmd(char *cmd, char **path);
void	execute_cmd(char *cmd, char **envp, int *pids);

/* Bonus part functions */
void	problem(void);
int		open_files(char *av, int i);
char	*get_next_line(int fd);
void	process(int ac, char **av, char **envp, int i);

#endif