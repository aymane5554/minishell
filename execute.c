/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:27:21 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/28 15:24:24 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_cmd *all_cmds, t_env *env, t_env *exprt, int no_cmds)
{
	int	i;
	int	pid;

	i = 0;
	while (all_cmds[i].cmd)
	{
		if (!ft_strcmp(all_cmds[i].cmd[0], "export"))
			export(env, exprt, all_cmds[i].cmd);
		else if (!ft_strcmp(all_cmds[i].cmd[0], "echo"))
			builtin_echo(all_cmds[i].cmd);
		else if (!ft_strcmp(all_cmds[i].cmd[0], "cd"))
			builtin_cd(all_cmds[i].cmd, env);
		else if (!ft_strcmp(all_cmds[i].cmd[0], "pwd"))
			builtin_pwd();
		else if (!ft_strcmp(all_cmds[i].cmd[0], "exit"))
			builtin_exit(all_cmds[i].cmd);
		else if (!ft_strcmp(all_cmds[i].cmd[0], "unset"))
			unset(all_cmds[i].cmd, env);
		else if (!ft_strcmp(all_cmds[i].cmd[0], "env"))
			display_env(env);
		else
		{
			pid  = fork();
			if (pid == 0)
			{
				if (redirect(all_cmds[i]) == -1)
				{
					(freencmds(all_cmds, no_cmds), free_env(env), free_env(exprt));
					exit(1);
				}
				(freencmds(all_cmds, no_cmds), free_env(env), free_env(exprt));
				exit(0);
			}
		}
		i++;
	}
	while (wait(NULL) != -1)
		continue ;
}
