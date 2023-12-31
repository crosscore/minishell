/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:09:58 by ysakahar          #+#    #+#             */
/*   Updated: 2023/07/01 19:37:52 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}

int	parse_envp(t_state *state)
{
	char	*path_from_envp;
	int		i;
	char	*tmp;

	path_from_envp = find_path(state->envp);
	state->paths = ft_split(path_from_envp, ':');
	free(path_from_envp);
	i = 0;
	while (state->paths[i])
	{
		if (ft_strncmp(&state->paths[i][ft_strlen(state->paths[i]) - 1],
			"/", 1) != 0)
		{
			tmp = ft_strjoin(state->paths[i], "/");
			free(state->paths[i]);
			state->paths[i] = tmp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
