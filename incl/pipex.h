/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 09:28:40 by jsubel            #+#    #+#             */
/*   Updated: 2022/04/11 12:18:10 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include "../libft/libft.h"

# define ERROR_INFILE		"Error - Infile"
# define ERROR_OUTFILE		"Error - Outfile"
# define ERROR_INPUT		"Error - Invalid number of arguments"
# define ERROR_PIPE			"Error - Pipe"
# define ERROR_CMD			"Error - Command not found"
# define ERROR_CHILD1		"Error - Child process 1"
# define ERROR_CHILD2		"Error - Child process 2"
# define ERROR_PARENT		"Error - Parent process"
# define ERROR_FORK			"Error - Fork"

/* 
Structure to house all the important things for pipex
pidX		- process ID of the two cmd processes
pipefd		- two ends of the pipe
infile		- the file from which to read the input for cmd1
outfile		- the file to write the output of cmd2 to
env_path	- environmental path
cmd_path	- path of command
cmd_args	- arguments for cmds
cmd			- actual cmd
 */
typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
	int		infile;
	int		outfile;
	char	*env_path;
	char	**cmd_path;
	char	**cmd_args;
	char	*cmd;
}	t_pipex;

//		child processes
void	ft_childprocess_one(t_pipex pipex, char **argv, char **envp);
void	ft_childprocess_two(t_pipex pipex, char **argv, char **envp);
#endif