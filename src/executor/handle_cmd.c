/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:11:23 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 13:59:08 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_split_str(char **split_str, char *new_str);
char	**resplit_str(char **double_arr);

int	find_cmd(t_cmd *cmd, t_state *state)
{
	int		i;
	char	*mycmd;

	i = 0;
	cmd->str = resplit_str(cmd->str);
	if (!access(cmd->str[0], F_OK))
		execve(cmd->str[0], cmd->str, state->envp);
	while (state->paths[i])
	{
		mycmd = ft_strjoin(state->paths[i], cmd->str[0]);
		if (!access(mycmd, F_OK))
			execve(mycmd, cmd->str, state->envp);
		free(mycmd);
		i++;
	}
	return (cmd_not_found(cmd->str[0]));
}

void	handle_cmd(t_cmd *cmd, t_state *state)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redirections)
		if (check_redirections(cmd))
			exit(1);
	if (cmd->builtin != NULL)
	{
		exit_code = cmd->builtin(state, cmd);
		exit(exit_code);
	}
	else if (cmd->str[0][0] != '\0')
		exit_code = find_cmd(cmd, state);
	exit(exit_code);
}

void	dup_cmd(t_cmd *cmd, t_state *state, int end[2], int fd_in)
{
	if (cmd->prev && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error(4, state);
	close(end[0]);
	if (cmd->next && dup2(end[1], STDOUT_FILENO) < 0)
		ft_error(4, state);
	close(end[1]);
	if (cmd->prev)
		close(fd_in);
	handle_cmd(cmd, state);
}

void	single_cmd(t_cmd *cmd, t_state *state)
{
	int	pid;
	int	status;

	state->cmd = call_expander(state, state->cmd);
	if (cmd->builtin == cmd_cd || cmd->builtin == cmd_exit
		|| cmd->builtin == cmd_export || cmd->builtin == cmd_unset)
	{
		g_global.error_num = cmd->builtin(state, cmd);
		return ;
	}
	send_heredoc(state, cmd);
	pid = fork();
	if (pid < 0)
		ft_error(5, state);
	if (pid == 0)
		handle_cmd(cmd, state);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_global.error_num = WEXITSTATUS(status);
}
