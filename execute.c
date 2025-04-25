/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:27:21 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/24 14:23:08 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_cmd *all_cmds, t_env *env)
{
	int	i;

	i = 0;
	while (all_cmds[i].cmd)
	{
		if (!ft_strcmp(all_cmds[i].cmd[0], "export"))
			export(env, all_cmds[i].cmd);
		// else if (!ft_strcmp(all_cmds[i].cmd[0], "echo"))
		// 	echo(all_cmds[i].cmd);
		// else if (!ft_strcmp(all_cmds[i].cmd[0], "cd"))
		// 	cd(all_cmds[i].cmd);
		// else if (!ft_strcmp(all_cmds[i].cmd[0], "pwd"))
		// 	pwd();
		/*
		else:
			find path and execute.
			then store exit status.
		*/
		i++;
	}
}
