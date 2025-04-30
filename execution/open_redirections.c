/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:38:02 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/30 10:54:25 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(char	*filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("open"), -1);
	dup2(fd, 0);
	close(fd);
	return (fd);
}

int open_outfile(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
		return (perror("open"), -1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	open_append_file(char *filename)
{
	int	fd;

	fd = open(filename, O_APPEND | O_TRUNC | O_CREAT);
	if (fd == -1)
		return (perror("open"), -1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	write_in_file(int fd, char *lim)
{
	char	*line;

	line = readline("heredoc> ");
	while (line && ft_strcmp(line, lim))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	free(line);
	return (fd);
}

int	open_heredoc(char *lim)
{
	int		fd[2];
	char	*filename_template;
	int		n;
	char	*filename;
	char	*num;

	filename_template = "/tmp/.tmp_minishell_";
	n = 0;
	num = ft_itoa(n);
	filename = ft_strjoin(filename_template, num);
	fd[0] = open(filename, O_RDWR | O_CREAT, 0777);
	while (fd[0] == -1)
	{
		(free(filename), free(num));
		n++;
		num = ft_itoa(n);
		filename = ft_strjoin(filename_template, num);
		if (!filename)
			return (free(num), -1);
		fd[0] = open(filename, O_RDWR | O_CREAT, 0777);
	}
	fd[1] = open(filename, O_RDONLY);
	unlink(filename);
	write_in_file(fd[0], lim);
	close(fd[0]);
	dup2(fd[1], 0);
	close(fd[1]);
	(free(filename), free(num));
	return (fd[1]);
}

int	redirect(t_cmd all_cmds)
{
	int	red;

	red = 0;
	while (all_cmds.redirection[red].file != NULL)
	{
		if (all_cmds.redirection[red].type == 0)
		{
			if (open_infile(all_cmds.redirection[red].file) == -1)
				return (-1);
		}
		else if (all_cmds.redirection[red].type == 1)
		{	
			if (open_outfile(all_cmds.redirection[red].file) == -1)
				return (-1);
		}
		else if (all_cmds.redirection[red].type == 2)
		{
			if (open_heredoc(all_cmds.redirection[red].file) == -1)
				return (-1);
		}
		else if (all_cmds.redirection[red].type == 3)
		{
			if (open_outfile(all_cmds.redirection[red].file) == -1)
				return (-1);
		}
		red++;
	}
	return (1);
}
