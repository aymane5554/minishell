/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:21:14 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/05/20 15:05:44 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_herdoc_signal = 0;

char	**get_cmds(t_env *envs, t_env *s_env)
{
	char	*line;
	int		status;
	char	**cmds;

	line = readline("minishell> ");
	if (!line)
	{
		status = get_status(NULL, NULL, 1);
		(free_env(envs), free_env(s_env));
		(printf("exit\n"), get_pwd(2), exit(status));
	}
	add_history(line);
	if (!validate_input(line))
		return (free(line), NULL);
	cmds = ft_split_pipe(line, '|');
	if (!cmds)
	{
		(get_pwd(2), free(line));
		(free_env(envs), free_env(s_env));
		(perror("error\n"), exit (1));
	}
	free(line);
	return (cmds);
}

int	redirections(char	**cmds, int i, t_cmd *all_cmds)
{
	char	*tmp;

	if (ft_strchr(cmds[i], '>') || ft_strchr(cmds[i], '<'))
	{
		tmp = cmds[i];
		cmds[i] = seperate_redirections(tmp, 0, 0, 0);
		if (!cmds[i])
		{
			cmds[i] = tmp;
			freencmds(all_cmds, i);
			freedbl((void **)cmds);
			get_pwd(2);
			perror("error\n");
			return (1);
		}
		free(tmp);
	}
	return (0);
}

void	fail(char	**cmds, char **cmd, int i, t_cmd *all_cmds)
{
	free(cmd);
	freencmds(all_cmds, i);
	freedbl((void **)cmds);
	freedbl((void **)cmd);
	get_pwd(2);
	perror("error\n");
}

int	get_t_cmd_arr(char	**cmds, int i, t_cmd *all_cmds)
{
	char	**cmd;

	cmd = ft_split_input(cmds[i]);
	if (!cmd)
		return (fail(cmds, cmd, i, all_cmds), 1);
	all_cmds[i].cmd = malloc((exe_arg_len(cmd) + 1) * sizeof(char *));
	if (!all_cmds[i].cmd)
		return (fail(cmds, cmd, i, all_cmds), 1);
	all_cmds[i].redirection
		= malloc((redirections_len(cmd) + 1) * sizeof(t_redr));
	if (!all_cmds[i].redirection)
	{
		freedbl((void **)all_cmds[i].cmd);
		return (fail(cmds, cmd, i, all_cmds), 1);
	}
	extract_exe_arg_from_cmd(cmd, all_cmds[i].cmd);
	extract_redirections_from_cmd(cmd, all_cmds[i].redirection);
	all_cmds[i].fd = 0;
	free(cmd);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	**cmds;
	t_cmd	*all_cmds;
	t_env	*envs;
	t_env	*s_env;

	(void)argv;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		exit(1);
	envs = duplicate_env(env);
	if (!envs)
		return (perror("env"), 1);
	s_env = sort_lst(envs);
	if (!s_env)
		return (free_env(envs), 1);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	get_pwd(0);
	get_status(envs, s_env, 0);
	while (1)
	{
		cmds = get_cmds(envs, s_env);
		if (!cmds)
			continue ;
		i = ft_dstrlen(cmds) + 1;
		all_cmds = malloc(sizeof(t_cmd) * i);
		i = 0;
		while (cmds[i])
		{
			if (redirections(cmds, i, all_cmds))
				(free_env(envs), free_env(s_env), exit(1));
			if (get_t_cmd_arr(cmds, i, all_cmds))
				(free_env(envs), free_env(s_env), exit(1));
			i++;
		}
		freedbl((void **)cmds);
		all_cmds[i].cmd = NULL;
		all_cmds[i].redirection = NULL;
		if (expand(all_cmds, 0, 0, envs) || remove_quotes_main(all_cmds))
		{
			freencmds(all_cmds, i);
			continue ;
		}
		argc = execute(all_cmds, envs, s_env);
		g_herdoc_signal = 0;
		chexitstatus(argc, envs, s_env);
		freencmds(all_cmds, i);
	}
	return (0);
}
