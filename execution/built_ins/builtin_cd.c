/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:26:18 by tibarike          #+#    #+#             */
/*   Updated: 2025/05/26 16:23:02 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	chdir_fail(char	*path);

static int	init_oldpwd(char **old_pwd, t_env *env, t_env *exprt)
{
	*old_pwd = ft_strdup(get_pwd(1));
	if (*old_pwd == NULL)
	{
		chdir("/");
		chpwd(env, exprt, getcwd(NULL, 0));
		return (0);
	}
	return (1);
}

static int	is_absolute(char **args, char **path, char *old_pwd)
{
	char	*tmp;

	if (args[1][0] == '/')
	{
		free(old_pwd);
		*path = ft_strdup(args[1]);
		if (!*path)
			return (1);
		return (0);
	}
	tmp = ft_strjoin(old_pwd, "/");
	if (!tmp)
		return (free(old_pwd), 1);
	free(old_pwd);
	*path = ft_strjoin(tmp, args[1]);
	free(tmp);
	if (!*path)
		return (1);
	return (0);
}

static int	change_dir(char *path, t_env *env, t_env *exprt)
{
	struct stat	info;

	if (stat(path, &info))
		return (perror("cd"), free(path), 1);
	if (!S_ISDIR(info.st_mode))
		return (perror("cd"), free(path), 1);
	choldpwd(env, exprt, getcwd(NULL, 0));
	if (chdir(path) == -1)
	{
		if (chdir_fail(path))
			chdir("/");
		chpwd(env, exprt, getcwd(NULL, 0));
		perror("cd");
		return (1);
	}
	free(path);
	chpwd(env, exprt, getcwd(NULL, 0));
	return (0);
}

int	builtin_cd(char **args, t_env *env, t_env *exprt)
{
	char		*old_pwd;
	char		*path;

	if (!args[1])
	{
		path = ft_getenv(env, "HOME");
		if (!path)
			return (ft_putstr_fd("cd: HOME is not set\n", 2), 1);
	}
	else if (args[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	else
	{
		if (init_oldpwd(&old_pwd, env, exprt) == 0)
			return (0);
		if (is_absolute(args, &path, old_pwd) != 0)
			return (1);
	}
	if (change_dir(path, env, exprt) != 0)
		return (1);
	return (0);
}
