/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:43:56 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/05/05 12:16:49 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_echo(t_cmd *all_cmds, int i, int no_cmds, int p_fd[3])
{
	int tmp;

	tmp = dup(1);
	if (all_cmds[i].fd)
	{
		close(all_cmds[i].fd);
		all_cmds[i].fd = 0;
	}
	if (redirect(all_cmds[i], p_fd, i, no_cmds) == -1)
		return (1);
	builtin_echo(all_cmds[i].cmd);
	dup2(tmp, 1);
	close(tmp);
	return (0);
}

int execute_pwd(t_cmd *all_cmds, int i, int no_cmds, int p_fd[3])
{
	int	tmp;

	tmp = dup(1);
	if (all_cmds[i].fd)
	{
		close(all_cmds[i].fd);
		all_cmds[i].fd = 0;
	}
	if (redirect(all_cmds[i], p_fd, i, no_cmds) == -1)
		return (1);
	builtin_pwd();
	dup2(tmp, 1);
	close(tmp);
	return (0);
}

int	execute_exit(t_cmd *all_cmds, int i, int no_cmds, int p_fd[3])
{
	if (all_cmds[i].fd)
	{
		close(all_cmds[i].fd);
		all_cmds[i].fd = 0;
	}
	if (redirect(all_cmds[i], p_fd, i, no_cmds) == -1)
		return (1);
	builtin_exit(all_cmds[i].cmd, no_cmds);
	return (0);
}

int	execute_unset(t_cmd *all_cmds, int i, t_env *env, int p_fd[3])
{
	int	tmp;
	int	no_cmds;

	no_cmds = count_cmds(all_cmds);
	tmp = dup(1);
	if (all_cmds[i].fd)
	{
		close(all_cmds[i].fd);
		all_cmds[i].fd = 0;
	}
	if (redirect(all_cmds[i], p_fd, i, no_cmds) == -1)
		return (0);
	unset(all_cmds[i].cmd, env);
	dup2(tmp, 1);
	close(tmp);
	return (0);
}

int execute_env(t_cmd *all_cmds, int i, t_env *env, int p_fd[3])
{
	int	tmp;
	int	no_cmds;

	no_cmds = count_cmds(all_cmds);
	tmp = dup(1);
	if (all_cmds[i].fd)
	{
		close(all_cmds[i].fd);
		all_cmds[i].fd = 0;
	}
	if (redirect(all_cmds[i], p_fd, i, no_cmds) == -1)
		return (0);
	display_env(env);
	dup2(tmp, 1);
	close(tmp);
	return (1);
}
