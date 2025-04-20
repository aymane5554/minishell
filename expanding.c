/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:12:31 by tibarike          #+#    #+#             */
/*   Updated: 2025/04/20 13:48:20 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*exctract_dollar(char *str, int *i, char *res)
{
	char	*var;
	char	*val;
	int		start;
	int		len;

	(*i)++;
	val = NULL;
	len = 0;
	if (ft_isalpha(str[*i]) || str[*i] == '_')
	{
		start = *i;
		while (ft_isalnum(str[*i]) || str[*i] == '_')
		{
			len++;
			(*i)++;
		}
		var = ft_substr(str, start, len);
		val = getenv(var);
		free(var);
	}
	if (!val)
		val = ft_strdup("");
	return (ft_strjoin(res, val));
}

static char	*expand_parse(char *str)
{
	int		i;
	bool	in_single;
	bool	in_double;
	char	*result;

	i = 0;
	in_double = false;
	in_single = false;
	result = ft_calloc(1, 1);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
		}
		else if (str[i] == '"' && !in_single)
		{
			in_double = !in_double;
			i++;
		}
		else if (str[i] == '$' && !in_single)
			result = exctract_dollar(str, &i, result);
		else
		{
			char	temp[2] = {str[i++], 0};
			result = ft_strjoin(result, temp);
		}
	}
	return(result);
}

void	expand(t_cmd *all_cmds, int i, int z)
{
	char *tmp;

	while(all_cmds[i].cmd)
	{
		z = 0;
		while (all_cmds[i].cmd[z])
		{
			if (ft_strchr(all_cmds[i].cmd[z], '$'))
				(tmp = expand_parse(all_cmds[i].cmd[z]), free(tmp));
			z++;
		}
		z = 0;
		while (all_cmds[i].redirection[z].file)
		{
			if (ft_strchr(all_cmds[i].redirection[z].file, '$'))
			{
				tmp = expand_parse(all_cmds[i].redirection[z].file);
				free(all_cmds[i].redirection[z].file);
				all_cmds[i].redirection[z].file = tmp;
			}
			z++;
		}
		i++;
	}
}
