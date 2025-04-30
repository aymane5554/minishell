/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:27:21 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/29 13:39:12 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_cmd *all_cmds, t_env *env, t_env *exprt, int no_cmds, char **o_env)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (all_cmds[i].cmd)
	{
		if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "export"))
			export(env, exprt, all_cmds[i].cmd);
		else if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "echo"))
			builtin_echo(all_cmds[i].cmd);
		else if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "cd"))
			builtin_cd(all_cmds[i].cmd, no_cmds);
		else if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "pwd"))
			builtin_pwd();
		else if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "exit"))
			builtin_exit(all_cmds[i].cmd, no_cmds);
		else if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "unset"))
			unset(all_cmds[i].cmd, env);
		else if (all_cmds[i].cmd[0] && !ft_strcmp(all_cmds[i].cmd[0], "env"))
			display_env(env);
		else
		{
			if (!fork())
			{
				if (redirect(all_cmds[i]) == -1)
				{
					(freencmds(all_cmds, no_cmds), free_env(env), free_env(exprt));
					exit(1);
				}
				if (!all_cmds[i].cmd[0])
				{
					(freencmds(all_cmds, no_cmds), free_env(env), free_env(exprt));
					exit(1);
				}
				cmd_path = check_commands(env, all_cmds[i].cmd[0]);
				if (!cmd_path)
				{
					(freencmds(all_cmds, no_cmds), free_env(env), free_env(exprt));
					exit(1);
				}
				execve(cmd_path, all_cmds[i].cmd, o_env);
				perror("execve");
				(freencmds(all_cmds, no_cmds), free_env(env), free_env(exprt));
				exit(1);
			}
		}
		i++;
	}
	while (wait(NULL) >= 0)
		continue ;
}
