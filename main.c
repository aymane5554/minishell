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

int main(void)
{
	int		i;
	int		j;
	int		cmds_len;
	char	**cmds;
	char	**cmd;
	char	*tmp;
	t_cmd	**all_cmds;

	while (1)
	{
		char *line = readline("minishell> ");
		add_history(line);
		if (!validate_input(line))
			continue;
		cmds = ft_split_pipe(line, '|');
		cmds_len = ft_dstrlen(cmds);
		all_cmds = malloc(sizeof(t_cmd) * cmds_len);
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
			printf("%i:", i);
			j = 0;
			while (cmd[j])
			{
				printf("[%s]", cmd[j]);
				j++;
			}
			printf("\n");
			i++;
		}
		printf("\n");
	}
	return 0;
}
