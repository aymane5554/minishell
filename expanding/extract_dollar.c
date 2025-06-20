/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:38:24 by tibarike          #+#    #+#             */
/*   Updated: 2025/05/21 16:42:37 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*push_char2(char *s, char c)
{
	char	temp[2];

	temp[0] = c;
	temp[1] = '\0';
	s = ft_strjoin(s, temp);
	return (s);
}

static char	*replace_expand_quotes(char *s)
{
	int		i;

	if (!s)
		return (ft_strdup(""));
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			s[i] = 1;
		if (s[i] == '\"')
			s[i] = 2;
		i++;
	}
	return (s);
}

char	*question_mark(t_env *envs, char *res, int *i)
{
	char	*val;
	char	*var;

	val = ft_getenv(envs, "?");
	if (!val)
		return (NULL);
	var = ft_strjoin(res, val);
	if (!var)
		return (perror("malloc"), free(res), free(val), NULL);
	(free(res), free(val));
	(*i)++;
	return (var);
}

static char	*normal_var(char *str, int *i, char *res, t_env *envs)
{
	int		start;
	int		len;
	char	*val;
	char	*var;

	start = *i;
	len = 0;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
	{
		len++;
		(*i)++;
	}
	var = ft_substr(str, start, len);
	if (!var)
		return (perror("malloc"), NULL);
	val = replace_expand_quotes(ft_getenv(envs, var));
	if (!val)
		return (free(var), NULL);
	free(var);
	var = ft_strjoin(res, val);
	free(val);
	return (var);
}

char	*exctract_dollar(char *str, int *i, char *res, t_env *envs)
{
	char	*var;

	var = normal_var(str, i, res, envs);
	if (!var)
		return (free(res), NULL);
	free(res);
	return (var);
}
