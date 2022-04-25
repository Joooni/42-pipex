/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:07:42 by jsubel            #+#    #+#             */
/*   Updated: 2022/04/25 12:04:49 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

void		ft_close_pipes(t_pipex_b *pipex);
void		ft_free_process(t_pipex_b *pipex);
static void	ft_create_pipes(t_pipex_b *pipex);

int	main(int argc, char **argv, char **envp)
{
	t_pipex_b	pipex;
	int			status;

	status = 0;
	ft_detect_input(&pipex, argc, argv);
	ft_detect_output(&pipex, argc, argv);
	pipex.nbr_cmds = argc - 3 - pipex.heredoc;
	pipex.nbr_pipeends = 2 * (pipex.nbr_cmds - 1);
	pipex.pipefd = (int *)ft_calloc(pipex.nbr_pipeends, sizeof(int));
	if (!pipex.pipefd)
		ft_end_process(ERROR_PIPE);
	pipex.env_path = ft_find_envpath(envp);
	pipex.cmd_path = ft_split(pipex.env_path, ':');
	ft_create_pipes(&pipex);
	pipex.index = 0;
	while (pipex.index < pipex.nbr_cmds)
	{
		ft_childprocess(pipex, argv, envp);
		pipex.index++;
	}
	ft_close_pipes(&pipex);
	ft_free_process(&pipex);
	waitpid(-1, &status, 0);
	return (0);
}

static void	ft_create_pipes(t_pipex_b *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_cmds - 1)
	{
		if (pipe(pipex->pipefd + 2 * i) < 0)
			ft_free_process(pipex);
		i++;
	}
}
