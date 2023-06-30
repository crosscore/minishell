/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:12:51 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/26 19:17:58 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path_ret(char *str, t_state *state)
{
	int	i;

	i = 0;
	while (state->envp[i])
	{
		if (!ft_strncmp(state->envp[i], str, ft_strlen(str)))
			return (ft_substr(state->envp[i], ft_strlen(str),
					ft_strlen(state->envp[i]) - ft_strlen(str)));
		i++;
	}
	return (NULL);
}

int	specific_path(t_state *state, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path_ret(str, state);
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, STDERR_FILENO);
		free(str);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

void	add_path_to_env(t_state *state)
{
	int		i;
	char	*tmp;

	i = 0;
	while (state->envp[i])
	{
		if (!ft_strncmp(state->envp[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", state->pwd);
			free(state->envp[i]);
			state->envp[i] = tmp;
		}
		else if (!ft_strncmp(state->envp[i], "OLDPWD=", 7) && state->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", state->old_pwd);
			free(state->envp[i]);
			state->envp[i] = tmp;
		}
		i++;
	}
}

int	cmd_cd(t_state *state, t_cmd *cmd)
{
	int		ret;

	if (!cmd->str[1])
		ret = specific_path(state, "HOME=");
	else if (ft_strncmp(cmd->str[1], "-", 1) == 0)
		ret = specific_path(state, "OLDPWD=");
	else
	{
		ret = chdir(cmd->str[1]);
		if (ret != 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd->str[1], STDERR_FILENO);
			perror(" ");
		}
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	change_path(state);
	add_path_to_env(state);
	return (EXIT_SUCCESS);
}
