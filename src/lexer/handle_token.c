/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:10:39 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 18:23:34 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ops	check_op(int c)
{
	static int	op_arr[3][2] = {
	{'|', PIPELINE},
	{'>', REDIRECT_OUTPUT},
	{'<', REDIRECT_INPUT},
	};
	int			i;

	i = 0;
	while (i < 3)
	{
		if (op_arr[i][0] == c)
			return (op_arr[i][1]);
		i++;
	}
	return (0);
}

int	handle_op(char *str, int i, t_lexer **lexer)
{
	t_ops	op;

	op = check_op(str[i]);
	if (op == REDIRECT_OUTPUT && check_op(str[i + 1]) == REDIRECT_OUTPUT)
	{
		if (!add_node(NULL, APPEND_OUTPUT, lexer))
			return (-1);
		return (2);
	}
	else if (op == REDIRECT_INPUT && check_op(str[i + 1]) == REDIRECT_INPUT)
	{
		if (!add_node(NULL, HEREDOC, lexer))
			return (-1);
		return (2);
	}
	else if (op)
	{
		if (!add_node(NULL, op, lexer))
			return (-1);
		return (1);
	}
	return (0);
}
