/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarike <tibarike@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:51:37 by tibarike          #+#    #+#             */
/*   Updated: 2025/05/06 17:42:23 by tibarike         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	if (g_herdoc_signal == 2)
	{
		close(0);
		dup2(2, 0);
		printf("\n");
		// printf("%d", g_herdoc_signal);
	}
	else if (g_herdoc_signal == 0)
	{
		printf("\n");
		// printf("%d", g_herdoc_signal);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	child_sigint(int sig)
{
	(void) sig;
	printf("\n");
	exit(130);
}
