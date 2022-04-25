/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:18:49 by jsubel            #+#    #+#             */
/*   Updated: 2022/04/25 12:24:01 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

static void	ft_dup2(int to_in, int to_out);
static char	*ft_find_cmd_path(char **paths, char *cmd);

void	ft_childprocess(t_pipex_b pipex, char **argv, char **envp)
{
	int	i;

	i = 0;
	pipex.pid = fork();
	if (pipex.pid == 0)
	{
		if (pipex.index == 0)
			ft_dup2(pipex.infile, pipex.pipefd[1]);
		else if (pipex.index == pipex.nbr_cmds - 1)
			ft_dup2(pipex.pipefd[2 * pipex.index - 2], pipex.outfile);
		else
			ft_dup2(pipex.pipefd[2 * pipex.index - 2], \
			pipex.pipefd[2 * pipex.index + 1]);
		ft_close_pipes(&pipex);
		pipex.cmd_args = ft_split(argv[2 + pipex.index + pipex.heredoc], ' ');
		pipex.cmd = ft_find_cmd_path(pipex.cmd_path, pipex.cmd_args[0]);
		if (!pipex.cmd)
		{
			ft_putstr_fd(ERROR_CMD, STDERR_FILENO);
			ft_putendl_fd(pipex.cmd_args[0], STDERR_FILENO);
			ft_free_child(&pipex);
			exit(1);
		}
		execve(pipex.cmd, pipex.cmd_args, envp);
	}
}

static char	*ft_find_cmd_path(char **paths, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp = ft_strjoin(tmp, cmd);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (0);
}

// use dup2 to redirect to_in to STDIN and to_out to STDOUT
static void	ft_dup2(int to_in, int to_out)
{
	dup2(to_in, STDIN_FILENO);
	dup2(to_out, STDOUT_FILENO);
}
