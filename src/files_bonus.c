/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsubel <jsubel@student.42wolfsburg.de >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:30:05 by jsubel            #+#    #+#             */
/*   Updated: 2022/04/25 11:20:08 by jsubel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

static void	ft_here_doc(t_pipex_b *pipex, char **argv);

void	ft_detect_input(t_pipex_b *pipex, int argc, char **argv)
{
	if (argc < 5)
		ft_end_process(ERROR_INPUT);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		ft_here_doc(pipex, argv);
	else
	{
		pipex->heredoc = 0;
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
			ft_end_process(ERROR_INFILE);
	}
}

void	ft_detect_output(t_pipex_b *pipex, int argc, char **argv)
{
	if (pipex->heredoc == 1)
		pipex->outfile = open(argv[argc - 1], O_APPEND \
		| O_CREAT | O_WRONLY, 0000644);
	else
		pipex->outfile = open(argv[argc - 1], O_TRUNC \
		| O_CREAT | O_RDWR, 0000644);
	if (pipex->outfile < 0)
		ft_end_process(ERROR_OUTFILE);
}

char	*ft_find_envpath(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
}

static void	ft_here_doc(t_pipex_b *pipex, char **argv)
{
	int		new_doc;
	char	*buffer;

	pipex->heredoc = 1;
	new_doc = open(".heredoc", O_TRUNC | O_CREAT | O_WRONLY, 0000644);
	if (new_doc < 0)
		ft_end_process(ERROR_HEREDOC);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buffer = get_next_line(STDIN_FILENO);
		if (ft_strncmp(argv[2], buffer, ft_strlen(argv[2])) == 0)
			break ;
		ft_putstr_fd(buffer, new_doc);
		free(buffer);
	}
	free(buffer);
	close(new_doc);
	pipex->infile = open(".heredoc", O_RDONLY);
	if (pipex->infile < 0)
	{
		unlink(".heredoc");
		ft_end_process(ERROR_HEREDOC);
	}
}
