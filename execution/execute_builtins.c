/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:43:56 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/05/14 14:22:11 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_echo(t_arg *arg, int i, int no_cmds, int p_fd[3])
{
	if (!fork())
	{
		if (arg->all_cmds[i].fd)
		{
			close(arg->all_cmds[i].fd);
			arg->all_cmds[i].fd = 0;
		}
		if (redirect(arg->all_cmds[i], p_fd, i, no_cmds) == -1)
			exit(errno_to_estatus());
		builtin_echo(arg->all_cmds[i].cmd);
		exit(0);
	}
	return (0);
}

int	execute_pwd(t_arg *arg, int i, int no_cmds, int p_fd[3])
{
	if (!fork())
	{
		if (arg->all_cmds[i].fd)
		{
			close(arg->all_cmds[i].fd);
			arg->all_cmds[i].fd = 0;
		}
		if (redirect(arg->all_cmds[i], p_fd, i, no_cmds) == -1)
			exit(errno_to_estatus());
		builtin_pwd();
		exit(0);
	}
	return (0);
}

int	execute_exit(t_arg *arg, int i, int no_cmds, int p_fd[3])
{
	if (no_cmds == 1)
	{
		if (arg->all_cmds[i].fd)
		{
			close(arg->all_cmds[i].fd);
			arg->all_cmds[i].fd = 0;
		}
		if (redirect(arg->all_cmds[i], p_fd, i, no_cmds) == -1)
			return (errno_to_estatus());
		builtin_exit(arg->all_cmds[i].cmd, no_cmds);
		return (0);
	}
	if (!fork())
	{
		if (arg->all_cmds[i].fd)
		{
			close(arg->all_cmds[i].fd);
			arg->all_cmds[i].fd = 0;
		}
		if (redirect(arg->all_cmds[i], p_fd, i, no_cmds) == -1)
			exit(errno_to_estatus());
		builtin_exit(arg->all_cmds[i].cmd, no_cmds);
		exit(0);
	}
	return (0);
}

int	execute_unset(t_arg *arg, int i, int p_fd[3])
{
	int	no_cmds;
	int	tmp;

	no_cmds = count_cmds(arg->all_cmds);
	if (no_cmds == 1)
	{
		tmp = dup(1);
		if (redirect(arg->all_cmds[i], p_fd, i, no_cmds) == -1)
			return (close(tmp), errno_to_estatus());
		unset(arg->all_cmds[i].cmd, arg->env, arg->export);
		dup2(tmp, 1);
		close(tmp);
		return (0);
	}
	if (!fork())
	{
		if (arg->all_cmds[i].fd)
		{
			close(arg->all_cmds[i].fd);
			arg->all_cmds[i].fd = 0;
		}
		if (redirect(arg->all_cmds[i], p_fd, i, no_cmds) == -1)
			exit(errno_to_estatus());
		unset(arg->all_cmds[i].cmd, arg->env, arg->export);
		exit(0);
	}
	return (0);
}

int	execute_env(t_arg *arg, int i, int p_fd[3])
{
	int	no_cmds;

	no_cmds = count_cmds(arg->all_cmds);
	if (!fork())
	{
		if (arg->all_cmds[i].fd)
		{
			close(arg->all_cmds[i].fd);
			arg->all_cmds[i].fd = 0;
		}
		if (redirect(arg->all_cmds[i], p_fd, i, no_cmds) == -1)
			exit(errno_to_estatus());
		display_env(arg->env);
		exit(0);
	}
	return (0);
}

int	execute_cd(t_arg *arg, int i, int p_fd[3])
{
	int	tmp;
	int	no_cmds;
	int	status;

	no_cmds = count_cmds(arg->all_cmds);
	tmp = dup(1);
	if (arg->all_cmds[i].fd)
	{
		close(arg->all_cmds[i].fd);
		arg->all_cmds[i].fd = 0;
	}
	if (redirect(arg->all_cmds[i], p_fd, i, no_cmds) == -1)
		return (errno_to_estatus());
	status = builtin_cd(arg->all_cmds[i].cmd, no_cmds, arg->env, arg->export);
	get_pwd(0);
	(dup2(tmp, 1), close(tmp));
	return (status);
}

int	execute_export(t_arg *arg, int i, int p_fd[3])
{
	int	tmp;
	int	no_cmds;

	no_cmds = count_cmds(arg->all_cmds);
	if (no_cmds != 1)
	{
		if (!fork())
		{
			if (redirect(arg->all_cmds[i], p_fd, i, no_cmds) == -1)
			{
				(freencmds(arg->all_cmds, no_cmds),
					free_env(arg->env), free_env(arg->export));
				exit(errno_to_estatus());
			}
			export(arg->env, arg->export, arg->all_cmds[i].cmd);
			(close(p_fd[0]), close(p_fd[1]));
			exit(0);
		}
		return (0);
	}
	tmp = dup(1);
	if (arg->all_cmds[i].fd)
	{
		close(arg->all_cmds[i].fd);
		arg->all_cmds[i].fd = 0;
	}
	if (redirect(arg->all_cmds[i], p_fd, i, no_cmds) == -1)
	{
		close(tmp);
		return (errno_to_estatus());
	}
	export(arg->env, arg->export, arg->all_cmds[i].cmd);
	dup2(tmp, 1);
	close(tmp);
	return (0);
}
