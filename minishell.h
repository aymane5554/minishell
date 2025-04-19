/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:12:13 by tibarike          #+#    #+#             */
/*   Updated: 2025/04/19 10:41:03 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct s_redr
{
	char	*file;
	char	type; //0 int, 1 out, 3 append, 4 herdoc
}	t_redr;

typedef struct s_cmd
{
	char	**cmd;
	t_redr	*redirection;
}	t_cmd;

int		valid_quotes(char	*str);
bool	validate_input(char *input);
char	**ft_split_input(char const *s, char c);
char	**ft_split_pipe(char const *s, char c);
char	*seperate_redirections(char *s);

#endif