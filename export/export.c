/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:35:48 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/23 15:21:13 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*duplicate_env(char **env)
{
	int		i;
	t_env	*head;

	i = 0;
	head = new_env(NULL);
	while (env[i])
		(push_env(head, new_env(env[i])), i++);
	return (head);
}

char	*ft_getenv(t_env *envs, char *key)
{
	envs = envs->next;
	while (envs->next)
	{
		if (!strcmp(key, envs->key))
			return (ft_strdup(envs->value));
		envs = envs->next;
	}
	return (NULL);
}
