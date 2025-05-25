/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrong_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 20:09:41 by ayel-arr          #+#    #+#             */
/*   Updated: 2025/05/25 11:42:25 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_last_dir(char *path)
{
	int		i;
	char	*ret;

	i = 0;
	while (path[i])
		i++;
	i--;
	if (path[i] == '/' && i != 0)
		i--;
	while (path[i] != '/' && i >= 0)
		i--;
	ret = ft_substr(path, 0, i);
	return (ret);
}

int	chdir_fail(char	*path)
{
	char	*str;
	char	*tmp;

	str = remove_last_dir(path);
	if (!str)
		return (free(path), 1);
	free(path);
	while (chdir(str) == -1)
	{
		tmp = str;
		str = remove_last_dir(str);
		free(tmp);
		if (!str)
			return (1);
	}
	free(str);
	return (0);
}
