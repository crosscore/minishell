/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:10:21 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 13:43:18 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parser	init_parser(t_lexer *lexer, t_state *state)
{
	t_parser	parser;

	parser.lexer = lexer;
	parser.redirections = NULL;
	parser.num_redirections = 0;
	parser.state = state;
	return (parser);
}

void	count_pipes(t_lexer *lexer, t_state *state)
{
	t_lexer	*tmp;

	tmp = lexer;
	state->pipes = 0;
	while (tmp)
	{
		if (tmp->op == PIPELINE)
			state->pipes++;
		tmp = tmp->next;
	}
}

int	count_args(t_lexer *lexer)
{
	t_lexer	*tmp;
	int		i;

	i = 0;
	tmp = lexer;
	while (tmp && tmp->op != PIPELINE)
	{
		if (tmp->i >= 0)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

t_lexer	*find_next_cmd(t_lexer *lexer_lst)
{
	while (lexer_lst && lexer_lst->op != PIPELINE)
		lexer_lst = lexer_lst->next;
	return (lexer_lst);
}
