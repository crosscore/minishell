/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:02:46 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 13:59:08 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_array(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

int	implement_tools(t_state *state)
{
	state->cmd = NULL;
	state->lexer = NULL;
	state->reset = false;
	state->pid = NULL;
	state->heredoc = false;
	g_global.stop_heredoc = 0;
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
	parse_envp(state);
	init_signals();
	return (1);
}

static int	find_pwd(t_state *state)
{
	int	i;

	i = 0;
	while (state->envp[i])
	{
		if (!ft_strncmp(state->envp[i], "PWD=", 4))
			state->pwd = ft_substr(state->envp[i],
					4, ft_strlen(state->envp[i]) - 4);
		if (!ft_strncmp(state->envp[i], "OLDPWD=", 7))
			state->old_pwd = ft_substr(state->envp[i],
					7, ft_strlen(state->envp[i]) - 7);
		i++;
	}
	return (1);
}

void	initialization(t_state *state, char **envp)
{
	state->envp = ft_arrdup(envp);
	find_pwd(state);
	implement_tools(state);
}
