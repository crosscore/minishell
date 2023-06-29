/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 23:02:46 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 00:08:09 by ysakahar         ###   ########.fr       */
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

int	implement_tools(t_tools *tools)
{
	tools->simple_cmds = NULL;
	tools->lexer_list = NULL;
	tools->reset = false;
	tools->pid = NULL;
	tools->heredoc = false;
	g_global.stop_heredoc = 0;
	g_global.in_cmd = 0;
	g_global.in_heredoc = 0;
	parse_envp(tools);
	init_signals();
	return (1);
}

static int	find_pwd(t_tools *tools)
{
	int	i;

	i = 0;
	while (tools->envp[i])
	{
		if (!ft_strncmp(tools->envp[i], "PWD=", 4))
			tools->pwd = ft_substr(tools->envp[i],
					4, ft_strlen(tools->envp[i]) - 4);
		if (!ft_strncmp(tools->envp[i], "OLDPWD=", 7))
			tools->old_pwd = ft_substr(tools->envp[i],
					7, ft_strlen(tools->envp[i]) - 7);
		i++;
	}
	return (1);
}

void	initialization(t_tools *tools, char **envp)
{
	tools->envp = ft_arrdup(envp);
	find_pwd(tools);
	implement_tools(tools);
}
