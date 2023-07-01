/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:02:46 by ysakahar          #+#    #+#             */
/*   Updated: 2023/07/01 18:56:23 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_arrdup(char **source_arr)
{
	char	**copied_arr;
	size_t	i;

	i = 0;
	while (source_arr[i] != NULL)
		i++;
	copied_arr = ft_calloc(sizeof(char *), i + 1);
	if (!copied_arr)
		return (NULL);
	i = 0;
	while (source_arr[i] != NULL)
	{
		copied_arr[i] = ft_strdup(source_arr[i]);
		if (copied_arr[i] == NULL)
		{
			free_array(copied_arr);
			return (copied_arr);
		}
		i++;
	}
	return (copied_arr);
}

int	implement_tools(t_state *state)
{
	state->cmd = NULL;
	state->lexer = NULL;
	state->is_reset_completed = false;
	state->pid = NULL;
	state->is_heredoc = false;
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
