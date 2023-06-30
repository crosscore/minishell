/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:10:34 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 22:11:12 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_delimiter(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	skip_delimiter(char *str, int i)
{
	int	j;

	j = 0;
	while (is_delimiter(str[i + j]))
		j++;
	return (j);
}

int	add_node(char *str, t_ops op, t_lexer **lexer)
{
	t_lexer	*node;

	node = ft_lexernew(str, op);
	if (!node)
		return (0);
	ft_lexeradd_back(lexer, node);
	return (1);
}

static int	find_matching_quote(char *str, int i, int *num_del, int del)
{
	int	j;

	j = i + 1;
	*num_del += 1;
	while (str[j] && str[j] != del)
		j++;
	if (str[j] == del)
		*num_del += 1;
	return (j - i);
}

int	count_quotes(char *str)
{
	int	i;
	int	s;
	int	d;

	s = 0;
	d = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"')
			i += find_matching_quote(str, i, &d, '\"');
		if (str[i] == '\'')
			i += find_matching_quote(str, i, &s, '\'');
	}
	if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
		return (0);
	return (1);
}