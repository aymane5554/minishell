/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:35:48 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/25 11:01:17 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_env(t_env *env)
{
	env = env->next;
	while (env)
	{
		printf("%s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
}

void	append_env(t_env *head, t_env *new)
{
	t_env	*last;
	char	*tmp;

	while (head)
	{
		if (head->key && !ft_strcmp(head->key, new->key))
		{
			free(new->key);
			tmp = head->value;
			head->value = ft_strjoin(head->value, new->value);
			free(tmp);
			free(new->value);
			free(new);
			return ;
		}
		last = head;
		head = head->next;
	}
	last->next = new;
}

int	export(t_env *env, char **cmd)
{
	int i;
	int j;

	j = 1;
	if (ft_dstrlen(cmd) == 1)
		return (display_env(env), 0);
	while (cmd[j])
	{
		i = 1;
		if (!isalpha(cmd[j][0]) && cmd[j][0] != '_')
			return (perror("syntax error"), -1);
		while (cmd[j][i] != '=' && cmd[j][i] != '\0' && cmd[j][i] != '+')
		{
			if (!isalnum(cmd[j][i]) && cmd[j][i] != '_')
				return (perror("syntax error"), -1);
			i++;
		}
		if (cmd[j][i] == '=' || cmd[j][i] == '\0') 
			push_env(env, new_env(cmd[j]));
		else if (cmd[j][i] == '+' && cmd[j][i + 1] == '=')
			append_env(env, new_env(cmd[j]));
		else
			perror("syntax error");
		j++;
	}
	return (0);
}
