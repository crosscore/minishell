/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:10:39 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/26 20:15:48 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ops	check_token(int c)
{
	static int	token_arr[3][2] = {
	{'|', PIPELINE},
	{'>', REDIRECT_OUTPUT},
	{'<', REDIRECT_INPUT},
	};
	int			i;

	i = 0;
	while (i < 3)
	{
		if (token_arr[i][0] == c)
			return (token_arr[i][1]);
		i++;
	}
	return (0);
}

int	handle_token(char *str, int i, t_lexer **lexer_list)
{
	t_ops	op;

	op = check_token(str[i]);
	if (op == REDIRECT_OUTPUT && check_token(str[i + 1]) == REDIRECT_OUTPUT)
	{
		if (!add_node(NULL, APPEND_OUTPUT, lexer_list))
			return (-1);
		return (2);
	}
	else if (op == REDIRECT_INPUT && check_token(str[i + 1]) == REDIRECT_INPUT)
	{
		if (!add_node(NULL, HEREDOC, lexer_list))
			return (-1);
		return (2);
	}
	else if (op)
	{
		if (!add_node(NULL, op, lexer_list))
			return (-1);
		return (1);
	}
	return (0);
}
