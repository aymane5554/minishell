/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:30:40 by tibarike          #+#    #+#             */
/*   Updated: 2025/04/19 10:53:01 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_dstrlen(char **str)
{
	int	i;
	i = 0;

	while (str[i])
		i++;
	return (i);
}

int	exe_arg_len(char **cmd)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (cmd[i])
	{
		if (cmd[i][0] != '>' && cmd[i][0] != '<')
			counter++;
		else if (cmd[i][0] == '>' || cmd[i][0] == '<')
			i++;
		i++;
	}
	return (counter);
}

int	redirections_len(char **cmd)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>' || cmd[i][0] == '<')
		{
			counter++;
			i++;
		}
		i++;
	}
	return (counter);
}

void	extract_exe_arg_from_cmd(char **cmd, char **dst)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (cmd[i])
	{
		if (cmd[i][0] != '>' && cmd[i][0] != '<')
		{
			dst[counter] = cmd[i];
			counter++;
		}
		else if (cmd[i][0] == '>' || cmd[i][0] == '<')
			i++;
		i++;
	}
}

char	get_redirection_type(char *str)
{
	if (ft_strcmp(str, ">>"))
		return (3);
	else if (ft_strcmp(str, "<<"))
		return (4);
	else if (ft_strcmp(str, ">"))
		return (1);
	else if (ft_strcmp(str, "<"))
		return (0);
	return (-1);
}

void	extract_redirections_from_cmd(char **cmd, t_redr *redirections)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>' && cmd[i][0] == '<')
		{
			redirections[counter].file = cmd[i + 1];
			redirections[counter].type = get_redirection_type(cmd[i]);
			counter++;
			i++;
		}
		i++;
	}
}

int main(void)
{
	int		i;
	char	**cmds;
	char	**cmd;
	char	*tmp;
	t_cmd	*all_cmds;

	while (1)
	{
		char *line = readline("minishell> ");
		add_history(line);
		if (!validate_input(line))
			continue;
		cmds = ft_split_pipe(line, '|');
		i = ft_dstrlen(cmds) + 1;
		all_cmds = malloc(sizeof(t_cmd) * i);
		i = 0;
		while (cmds[i])
		{
			if (ft_strchr(cmds[i], '>') || ft_strchr(cmds[i], '<'))
			{
				tmp = cmds[i];
				cmds[i] = seperate_redirections(tmp);
				free(tmp);
			}
			cmd = ft_split_input(cmds[i], ' ');
			printf("cmd%i:", i);
			for (int j = 0; cmd[j]; j++)
			{
				printf("|%s|", cmd[j]);
			}
			printf("\n");
			all_cmds[i].cmd = malloc((exe_arg_len(cmd) + 1) * sizeof(char *));
			all_cmds[i].redirection = malloc((redirections_len(cmd) + 1) * sizeof(t_redr));
			extract_exe_arg_from_cmd(cmd, all_cmds[i].cmd);
			extract_redirections_from_cmd(cmd, all_cmds[i].redirection);
			i++;
		}
		all_cmds[i].cmd = NULL;
		all_cmds[i].redirection = NULL;
	}
	return 0;
}
