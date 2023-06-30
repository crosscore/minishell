/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:10:34 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 13:43:18 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || (c > 8 && c < 14));
}

int	skip_spaces(char *str, int i)
{
	int	j;

	j = 0;
	while (is_whitespace(str[i + j]))
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

int	read_words(int i, char *str, t_lexer **lexer)
{
	int	j;

	j = 0;
	while (str[i + j] && !(check_token(str[i + j])))
	{
		j += handle_quotes(i + j, str, 34);
		j += handle_quotes(i + j, str, 39);
		if (is_whitespace(str[i + j]))
			break ;
		else
			j++;
	}
	if (!add_node(ft_substr(str, i, j), 0, lexer))
		return (-1);
	return (j);
}

int	token_reader(t_state *state)
{
	int		i;
	int		j;

	i = 0;
	while (state->args[i])
	{
		j = 0;
		i += skip_spaces(state->args, i);
		if (check_token(state->args[i]))
			j = handle_token(state->args, i, &state->lexer);
		else
			j = read_words(i, state->args, &state->lexer);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
