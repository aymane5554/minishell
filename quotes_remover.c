/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:20:40 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/04/26 11:39:03 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_without_quotes(char *s)
{
	int		i;
	char	quote;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			if (s[i] == '\'' && quote == 0)
				quote = 1;
			else if (s[i] == '\'' && quote == 1)
				quote = 0;
			else if (s[i] == '\"' && quote == 0)
				quote = 2;
			else if (s[i] == '\"' && quote == 2)
				quote = 0;
			i++;
			continue ;
		}
		i++;
		j++;
	}
}

void remove_quotes(t_cmd *cmds)
{
}
