/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-arr <ayel-arr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:12:13 by tibarike          #+#    #+#             */
/*   Updated: 2025/04/23 14:44:43 by ayel-arr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
	char	type;
}	t_redr;

typedef struct s_cmd
{
	char			**cmd;
	struct s_redr	*redirection;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		valid_quotes(char	*str);
bool	validate_input(char *input);
char	**ft_split_input(char const *s, char c);
char	**ft_split_pipe(char const *s, char c);
char	*seperate_redirections(char *s, int i, int j, char c);
void	expand(t_cmd *all_cmds, int i, int z, t_env *envs);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	pwd(void);
int		cd(char **args);
void	echo(char **args);
t_env	*new_env(char *env);
void	push_env(t_env *head, t_env *new);
char	*ft_getenv(t_env *envs, char *key);
t_env	*duplicate_env(char **env);
void	free_env(t_env *env);

#endif