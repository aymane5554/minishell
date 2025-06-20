/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:18:46 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/05/20 09:53:15 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_export(t_env *env, t_env *new)
{
	t_env	*last;

	if (!new)
		return (perror("export"));
	last = env;
	while (env)
	{
		if (env->key && !ft_strcmp(env->key, new->key))
		{
			if (new->empty)
				return (free(new->key), free(new->value), free(new));
			(free(env->value), env->value = new->value);
			return (env->empty = new->empty, free(new->key), free(new));
		}
		else if ((!env->key || ft_strcmp(env->key, new->key) < 0)
			&& (!env->next || ft_strcmp(env->next->key, new->key) > 0))
		{
			new->next = env->next;
			env->next = new;
			return ;
		}
		last = env;
		env = env->next;
	}
	last->next = new;
}

static void	append(t_env *env, t_env *new)
{
	char	*tmp;

	if (new->empty)
		return (free(new->key), free(new->value), free(new));
	tmp = env->value;
	env->value = ft_strjoin(env->value, new->value);
	if (!env->value)
	{
		env->value = tmp;
		return (free(new->value), free(new->key), free(new));
	}
	env->empty = new->empty;
	(free(new->value), free(new->key), free(tmp), free(new));
}

void	append_export(t_env *env, t_env *new)
{
	t_env	*last;

	if (!new)
		return (perror("export"));
	last = env;
	while (env)
	{
		if (env->key && !ft_strcmp(env->key, new->key))
		{
			append(env, new);
			return ;
		}
		if ((!env->key || ft_strcmp(env->key, new->key) < 0)
			&& (!env->next || ft_strcmp(env->next->key, new->key) > 0))
		{
			new->next = env->next;
			env->next = new;
			return ;
		}
		last = env;
		env = env->next;
	}
	last->next = new;
}

char	*get_pwd(char option)
{
	static char	*pwd;

	if (option == 0)
	{
		free(pwd);
		pwd = getcwd(NULL, 0);
		if (!pwd)
			perror("pwd");
		return (pwd);
	}
	if (option == 1)
		return (pwd);
	if (option == 2)
		return (free(pwd), NULL);
	return (pwd);
}

void	display_env(t_env *env)
{
	env = env->next;
	while (env)
	{
		if (!env->empty && ft_strcmp(env->key, "?"))
		{
			printf("%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}
}
