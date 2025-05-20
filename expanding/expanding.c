/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:12:31 by tibarike          #+#    #+#             */
/*   Updated: 2025/05/20 20:23:31 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prompt_dollar(t_cmd *all_cmds, int *z, int i, t_env *envs)
{
	char	**ttmp;
	char	*tmp;
	char	**split;
	int		len;

	tmp = expand_parse(all_cmds[i].cmd[*z], envs);
	if (!(tmp))
		return (1);
	split = ft_split(tmp, ' ');
	len = ft_dstrlen(split);
	if (len == 1)
	{
		(free(all_cmds[i].cmd[*z]), all_cmds[i].cmd[*z] = split[0]);
		(*z)++;
		(free(tmp), free(split));
		return (2);
	}
	ttmp = insert2darray(all_cmds[i].cmd, split, *z);
	if (!ttmp)
		return (free(split), free(tmp), 1);
	(free(all_cmds[i].cmd), free(split), free(tmp));
	all_cmds[i].cmd = ttmp;
	*z += len - 1;
	return (0);
}

static int	file_dollar(t_cmd *all_cmds, int *z, int i, t_env *envs)
{
	char	*tmp;

	tmp = expand_parse(all_cmds[i].redirection[*z].file, envs);
	if (!tmp)
		return (all_cmds[i].redirection[*z].error = 1, 1);
	if (check_empty_string(tmp) || space_separated(tmp))
	{
		all_cmds[i].redirection[*z].error = 1;
		free(tmp);
		(*z)++;
		return (2);
	}
	free(all_cmds[i].redirection[*z].file);
	all_cmds[i].redirection[*z].file = tmp;
	return (0);
}

static int	file_dollar_loop(t_cmd *all_cmds, int *z, int i, t_env *envs)
{
	int	success;

	success = 0;
	while (all_cmds[i].redirection[*z].file)
	{
		if (ft_strchr(all_cmds[i].redirection[*z].file, '$')
			&& all_cmds[i].redirection[*z].type != 2)
		{
			success = file_dollar(all_cmds, z, i, envs);
			if (success == 2)
				continue ;
			else if (success == 1)
				return (1);
		}
		(*z)++;
	}
	return (0);
}

static int	prompt_dollar_loop(t_cmd *all_cmds, int *z, int i, t_env *envs)
{
	int	success;

	success = 0;
	while (all_cmds[i].cmd[*z])
	{
		if (ft_strchr(all_cmds[i].cmd[*z], '$'))
		{
			success = prompt_dollar(all_cmds, z, i, envs);
			if (success == 2)
				continue ;
			else if (success == 1)
				return (1);
		}
		(*z)++;
	}
	return (0);
}

int	expand(t_cmd *all_cmds, int i, int z, t_env *envs)
{
	int		success;

	success = 0;
	while (all_cmds[i].cmd)
	{
		z = 0;
		success = prompt_dollar_loop(all_cmds, &z, i, envs);
		if (success)
			return (1);
		z = 0;
		success = file_dollar_loop(all_cmds, &z, i, envs);
		if (success)
			return (1);
		i++;
	}
	return (0);
}
