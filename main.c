/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:30:40 by tibarike          #+#    #+#             */
/*   Updated: 2025/04/15 13:51:44 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(void)
{
	int		i;
	char	**words;

	while (1)
	{
		char *line = readline("minishell> ");
		if (!validate_input(line))
			continue;
		add_history(line);
		words = ft_split_input(line, ' ');
		i = 0;
		while (words[i])
		{
			printf("[%s]", words[i]);
			i++;
		}
		printf("\n");
	}
	return 0;
}
