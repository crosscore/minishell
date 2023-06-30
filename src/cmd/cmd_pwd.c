/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:12:14 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/26 19:16:38 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_pwd(t_state *state, t_cmd *cmd)
{
	(void)cmd;
	ft_putendl_fd(state->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
