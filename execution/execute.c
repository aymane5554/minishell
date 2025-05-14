/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:27:21 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/05/14 15:41:54 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].cmd)
		i++;
	return (i);
}

void	close_heredocs(t_arg *arg)
{
	int	i;

	i = 0;
	while (arg->all_cmds[i].cmd)
	{
		if (arg->all_cmds[i].fd)
			close(arg->all_cmds[i].fd);
		i++;
	}
}

int	here_doc(t_arg *arg, int p_fd[3], int no_cmds)
{
	int	i;
	int	red;
	int	args[2];
	int	tmp;

	i = 0;
	red = 0;
	while (arg->all_cmds[i].cmd)
	{
		red = 0;
		while (arg->all_cmds[i].redirection[red].file != NULL)
		{
			if (arg->all_cmds[i].redirection[red].type == 2)
			{
				if (arg->all_cmds[i].fd != 0)
					close(arg->all_cmds[i].fd);
				args[0] = no_cmds;
				args[1] = arg->all_cmds[i].redirection[red].expandable;
				arg->all_cmds[i].fd = open_heredoc(arg->all_cmds[i].redirection[red].file,
						p_fd, args, arg);
				tmp = arg->all_cmds[i].fd;
				if (arg->all_cmds[i].fd < 0)
					return (arg->all_cmds[i].fd = 0, tmp);
			}
			red++;
		}
		i++;
	}
	return (0);
}

int	execute(t_cmd *all_cmds, t_env *env, t_env *exprt)
{
	int		i;
	int		no_cmds;
	int		p_fd[3];
	int		status;
	t_arg	arg;

	arg.env = env;
	arg.export = exprt;
	arg.all_cmds = all_cmds;
	status = 0;
	p_fd[2] = 0;
	no_cmds = count_cmds(all_cmds);
	if (no_cmds != 1)
		pipe(p_fd);
	i = here_doc(&arg, p_fd, no_cmds);
	if (i < 0)
	{
		close_heredocs(&arg);
		if (no_cmds > 1)
			(close(p_fd[0]), close(p_fd[1]));
		if (i == -1)
			return (130);
		return (1);
	}
	i = 0;
	while (all_cmds[i].cmd)
	{
		if (i != 0 && i != no_cmds -1)
		{
			close(p_fd[1]);
			if (p_fd[2])
				close(p_fd[2]);
			p_fd[2] = p_fd[0];
			pipe(p_fd);
		}
		else if (i == no_cmds - 1 && no_cmds != 1)
			close(p_fd[1]);
		if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "export"))
			status = execute_export(&arg, i, p_fd);
		else if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "echo"))
			execute_echo(&arg, i, no_cmds, p_fd);
		else if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "cd"))
			status = execute_cd(&arg, i, p_fd);
		else if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "pwd"))
			execute_pwd(&arg, i, no_cmds, p_fd);
		else if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "exit"))
			status = execute_exit(&arg, i, no_cmds, p_fd);
		else if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "unset"))
			status = execute_unset(&arg, i, p_fd);
		else if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "env"))
			execute_env(&arg, i, p_fd);
		else
			execute_others_main(&arg, i, p_fd);
		i++;
	}
	if (no_cmds != 1)
		(close(p_fd[0]), close(p_fd[1]));
	if (p_fd[2])
		close(p_fd[2]);
	while (wait(&status) >= 0)
		continue ;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGPIPE)
			printf("\n");
	}
	return (WEXITSTATUS(status));
}
