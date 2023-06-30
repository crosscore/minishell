/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:10:28 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 13:43:18 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_heredoc(char *str1, char *str2)
{
	char	*ret;
	char	*tmp;

	if (!str2)
		return (ft_strdup(str1));
	tmp = ft_strjoin(str1, " ");
	ret = ft_strjoin(tmp, str2);
	free(tmp);
	free(str2);
	return (ret);
}

int	add_new_redirection(t_lexer *tmp, t_parser *parser)
{
	t_lexer	*node;
	int		index_1;
	int		index_2;

	node = ft_lexernew(ft_strdup(tmp->next->str), tmp->op);
	if (!node)
		parser_error(1, parser->state, parser->lexer);
	ft_lexeradd_back(&parser->redirections, node);
	index_1 = tmp->i;
	index_2 = tmp->next->i;
	ft_lexerdelone(&parser->lexer, index_1);
	ft_lexerdelone(&parser->lexer, index_2);
	parser->num_redirections++;
	return (0);
}

void	rm_redirections(t_parser *parser)
{
	t_lexer	*tmp;

	tmp = parser->lexer;
	while (tmp && tmp->op == 0)
		tmp = tmp->next;
	if (!tmp || tmp->op == PIPELINE)
		return ;
	if (!tmp->next)
		parser_error(0, parser->state, parser->lexer);
	if (tmp->next->op)
		parser_double_token_error(parser->state, \
			parser->lexer, tmp->next->op);
	if ((tmp->op >= REDIRECT_OUTPUT && tmp->op <= HEREDOC))
		add_new_redirection(tmp, parser);
	rm_redirections(parser);
}
