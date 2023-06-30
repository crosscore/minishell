/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:11:30 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 13:37:51 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_simple_cmds	*call_expander(t_state *state, t_simple_cmds *cmd)
{
	t_lexer	*start;

	cmd->str = expander(state, cmd->str);
	start = cmd->redirections;
	while (cmd->redirections)
	{
		if (cmd->redirections->op != HEREDOC)
			cmd->redirections->str
				= expander_str(state, cmd->redirections->str);
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (cmd);
}

int	pipe_wait(int *pid, int amount)
{
	int	i;
	int	status;

	i = 0;
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		g_global.error_num = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}

int	ft_fork(t_state *state, int end[2], int fd_in, t_simple_cmds *cmd)
{
	static int	i = 0;

	if (state->reset == true)
	{
		i = 0;
		state->reset = false;
	}
	state->pid[i] = fork();
	if (state->pid[i] < 0)
		ft_error(5, state);
	if (state->pid[i] == 0)
		dup_cmd(cmd, state, end, fd_in);
	i++;
	return (EXIT_SUCCESS);
}

int	check_fd_heredoc(t_state *state, int end[2], t_simple_cmds *cmd)
{
	int	fd_in;

	if (state->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd->hd_file_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}

int	executor(t_state *state)
{
	int		end[2];
	int		fd_in;

	fd_in = STDIN_FILENO;
	while (state->simple_cmds)
	{
		state->simple_cmds = call_expander(state, state->simple_cmds);
		if (state->simple_cmds->next)
			pipe(end);
		send_heredoc(state, state->simple_cmds);
		ft_fork(state, end, fd_in, state->simple_cmds);
		close(end[1]);
		if (state->simple_cmds->prev)
			close(fd_in);
		fd_in = check_fd_heredoc(state, end, state->simple_cmds);
		if (state->simple_cmds->next)
			state->simple_cmds = state->simple_cmds->next;
		else
			break ;
	}
	pipe_wait(state->pid, state->pipes);
	state->simple_cmds = ft_simple_cmdsfirst(state->simple_cmds);
	return (0);
}
