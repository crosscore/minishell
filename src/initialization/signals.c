/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: komatsud <komatsud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:58:57 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/29 18:44:19 by komatsud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	if (g_global.in_heredoc == 1)
	{
		g_global.stop_heredoc = 1;
		ft_putchar_fd(4, STDOUT_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	sigquit_handler(int sig)
{
	if (g_global.in_heredoc != 1)
	{
		ft_putstr_fd("Quit: ", STDOUT_FILENO);
		ft_putnbr_fd(sig, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

// SIGINT - Ctrl+C
// SIGQUIT - Ctrl+\
// EOF(character) - Ctrl+D
void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
