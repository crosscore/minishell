/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:59:06 by ysakahar          #+#    #+#             */
/*   Updated: 2023/07/01 19:12:41 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	prepare_executor(t_state *state)
{
	signal(SIGQUIT, sigquit_handler);
	g_global.in_cmd = 1;
	if (state->num_pipes == 0)
		single_cmd(state->cmd, state);
	else
	{
		state->pid = ft_calloc(sizeof(int), state->num_pipes + 2);
		if (!state->pid)
			return (ft_error(1, state));
		executor(state);
	}
	g_global.in_cmd = 0;
	return (EXIT_SUCCESS);
}

static int	read_and_trim_input_addhistory(t_state *state)
{
	char	*tmp;

	state->input_args = readline(READLINE_MSG);
	tmp = ft_strtrim(state->input_args, " ");
	free(state->input_args);
	state->input_args = tmp;
	if (!state->input_args)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (state->input_args[0] == '\0')
		return (reset_tools(state));
	add_history(state->input_args);
	return (1);
}

int	reset_tools(t_state *state)
{
	ft_cmd_clear(&state->cmd);
	free(state->input_args);
	if (state->pid)
		free(state->pid);
	free_array(state->paths);
	implement_tools(state);
	state->is_reset_completed = true;
	minishell_loop(state);
	return (1);
}

int	minishell_loop(t_state *state)
{
	if (!read_and_trim_input_addhistory(state))
		return (0);
	if (!ft_lexer(state))
		return (0);
	ft_parser(state);
	prepare_executor(state);
	reset_tools(state);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_state	state;

	if (argc != 1 || argv[1])
	{
		printf("No arguments allowed.\n");
		exit(0);
	}
	initialization(&state, envp);
	minishell_loop(&state);
	return (0);
}

/*
__attribute__((destructor)) static void	destructor(void)
{
	system("leaks -q minishell");
}
*/
