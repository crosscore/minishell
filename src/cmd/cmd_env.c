/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:12:39 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/26 19:17:52 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_env(t_state *state, t_cmd *cmd)
{
	int		i;

	(void)cmd;
	i = 0;
	while (state->envp[i])
	{
		ft_putendl_fd(state->envp[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
