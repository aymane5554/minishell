/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:57:49 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/23 15:55:03 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *env)
{
	t_env	*ret;
	char	*equal;

	ret = malloc(sizeof(t_env));
	if (env == NULL)
	{
		ret->key = NULL;
		ret->value = NULL;
		ret->next = NULL;
		return (ret);
	}
	equal = ft_strchr(env, '=');
	if (equal == NULL)
		equal = ft_strchr(env, '\0');
	ret->key = ft_substr(env, 0, equal - env);
	ret->value = ft_substr(env, equal - env, ft_strlen(equal));
	ret->next = NULL;
	return (ret);
}

void	push_env(t_env *head, t_env *new)
{
	while (head->next)
		head = head->next;
	head->next = new;
}

void	free_env(t_env *env)
{
	t_env	*last;

	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		free(env->key);
		free(env->value);
		last = env;
		env = env->next;
		free(last);
	}
}
