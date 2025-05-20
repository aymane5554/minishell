/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:39:06 by tibarike          #+#    #+#             */
/*   Updated: 2025/05/20 17:48:06 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_char(char **s, char c)
{
	char	temp[2];
	char	*tmp;

	temp[0] = c;
	temp[1] = '\0';
	tmp = *s;
	*s = ft_strjoin(*s, temp);
	free(tmp);
}

char	*expand_parse_heredoc(char *str, t_env *envs)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (perror("malloc"), NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			result = exctract_dollar(str, &i, result, envs);
			if (!result)
				return (NULL);
		}
		else
		{
			push_char(&result, str[i]);
			if (!result)
				return (perror("malloc"), NULL);
			i++;
		}
	}
	return (result);
}
