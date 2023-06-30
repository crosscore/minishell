/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:10:07 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 13:32:15 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	reset_tools(t_state *state)
{
	ft_simple_cmdsclear(&state->simple_cmds);
	free(state->args);
	if (state->pid)
		free(state->pid);
	free_array(state->paths);
	implement_tools(state);
	state->reset = true;
	minishell_loop(state);
	return (1);
}

int	prepare_executor(t_state *state)
{
	signal(SIGQUIT, sigquit_handler);
	g_global.in_cmd = 1;
	if (state->pipes == 0)
		single_cmd(state->simple_cmds, state);
	else
	{
		state->pid = ft_calloc(sizeof(int), state->pipes + 2);
		if (!state->pid)
			return (ft_error(1, state));
		executor(state);
	}
	g_global.in_cmd = 0;
	return (EXIT_SUCCESS);
}

int	minishell_loop(t_state *state)
{
	char	*tmp;

	state->args = readline(READLINE_MSG);
	tmp = ft_strtrim(state->args, " ");
	free(state->args);
	state->args = tmp;
	if (!state->args)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (state->args[0] == '\0')
		return (reset_tools(state));
	add_history(state->args);
	if (!count_quotes(state->args))
		return (ft_error(2, state));
	if (!token_reader(state))
		return (ft_error(1, state));
	ft_parser(state);
	prepare_executor(state);
	reset_tools(state);
	return (1);
}
