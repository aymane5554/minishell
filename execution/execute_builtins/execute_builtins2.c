/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:32:58 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/05/18 17:35:07 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		tmp;
	int		no_cmds;
	pid_t	pid;

	no_cmds = count_cmds(arg->all_cmds);
	if (no_cmds != 1)
	{
		pid = execute_export_pipe(arg, i, p_fd, no_cmds);
		if (arg->all_cmds[i].fd)
			close(arg->all_cmds[i].fd);
		if (pid == -1)
			perror("fork");
		if (i == no_cmds - 1)
			return (pid);
		return (0);
	}
	tmp = dup(1);
	if (arg->all_cmds[i].fd)
		(close(arg->all_cmds[i].fd), arg->all_cmds[i].fd = 0);
	if (redirect(arg->all_cmds[i], p_fd, i, no_cmds) == -1)
		return (close(tmp), errno_to_estatus());
	export(arg->env, arg->export, arg->all_cmds[i].cmd);
	return (dup2(tmp, 1), close(tmp));
}
