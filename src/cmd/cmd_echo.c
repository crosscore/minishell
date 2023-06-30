/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:12:45 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/26 19:17:56 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_lines(int i, char **str, int out)
{
	while (str[i])
	{
		ft_putstr_fd(str[i++], out);
		if (str[i])
			ft_putchar_fd(' ', out);
	}
}

int	cmd_echo(t_state *tools, t_simple_cmds *simple_cmd)
{
	int		i;
	int		j;
	bool	n_option;

	i = 1;
	n_option = false;
	(void) tools;
	while (simple_cmd->str[i] && simple_cmd->str[i][0] == '-'
		&& simple_cmd->str[i][1] == 'n')
	{
		j = 1;
		while (simple_cmd->str[i][j] == 'n')
			j++;
		if (simple_cmd->str[i][j] == '\0')
			n_option = true;
		else
			break ;
		i++;
	}
	print_lines(i, simple_cmd->str, STDOUT_FILENO);
	if (n_option == false)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
