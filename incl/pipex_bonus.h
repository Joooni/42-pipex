/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 09:28:40 by jsubel            #+#    #+#             */
/*   Updated: 2022/04/25 14:28:12 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include "../42_libft/libft.h"
# include "../42_get_next_line/get_next_line.h"

# define ERROR_INFILE		"Error - Infile"
# define ERROR_OUTFILE		"Error - Outfile"
# define ERROR_INPUT		"Error - Invalid number of arguments"
# define ERROR_PIPE			"Error - Pipe"
# define ERROR_CMD			"Error - Command not found: "
# define ERROR_CHILD1		"Error - Child process 1"
# define ERROR_CHILD2		"Error - Child process 2"
# define ERROR_PARENT		"Error - Parent process"
# define ERROR_FORK			"Error - Fork"
# define ERROR_HEREDOC		"Error - Heredoc"

/* 
Structure to house all the important things for pipex
pid				- process ID of the two cmd processes
pipefd			- pipe ends
nbr_pipeends	- nbr of pipe ends needed
infile			- the file from which to read the input for cmd1
outfile			- the file to write the output of cmd2 to
env_path		- environmental path
cmd_path		- path of command
cmd_args		- arguments for cmds
cmd				- actual cmd
nbr_cmd			- nbr of commands to execute
index			- index of current command
heredoc			- if heredoc is used, 1; else 0
 */
typedef struct s_pipex_b
{
	pid_t	pid;
	int		*pipefd;
	int		nbr_pipeends;
	int		infile;
	int		outfile;
	char	*env_path;
	char	**cmd_path;
	char	**cmd_args;
	char	*cmd;
	int		nbr_cmds;
	int		index;
	int		heredoc;
}	t_pipex_b;

//		child processes

void	ft_childprocess(t_pipex_b pipex, char **argv, char **envp);

//		close and free functions

void	ft_close_pipes(t_pipex_b *pipex);
void	ft_free_process(t_pipex_b *pipex);
void	ft_free_child(t_pipex_b *pipex);

//		input detection

void	ft_detect_input(t_pipex_b *pipex, int argc, char **argv);
void	ft_detect_output(t_pipex_b *pipex, int argc, char **argv);
char	*ft_find_envpath(char **envp);
#endif