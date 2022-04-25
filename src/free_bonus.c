/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:09:21 by jsubel            #+#    #+#             */
/*   Updated: 2022/04/22 14:12:45 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

void	ft_free_process(t_pipex_b *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	free(pipex->pipefd);
	free(pipex->env_path);
	while (pipex->cmd_path[i])
	{
		free(pipex->cmd_path[i]);
		i++;
	}
	if (pipex->heredoc)
		unlink(".heredoc");
	free(pipex->cmd_path);
}

void	ft_free_child(t_pipex_b *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
}

/* close all opened pipes */
void	ft_close_pipes(t_pipex_b *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_pipeends)
	{
		close(pipex->pipefd[i]);
		i++;
	}
}
