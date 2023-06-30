/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 12:30:53 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 15:25:23 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*initialize_cmd(t_parser *parser)
{
	char	**str;
	int		i;
	int		arg_size;
	t_lexer	*tmp;

	i = 0;
	rm_redirections(parser);
	arg_size = count_args(parser->lexer);
	str = ft_calloc(arg_size + 1, sizeof(char *));
	if (!str)
		parser_error(1, parser->state, parser->lexer);
	tmp = parser->lexer;
	while (arg_size > 0)
	{
		if (tmp->str)
		{
			str[i++] = ft_strdup(tmp->str);
			ft_lexerdelone(&parser->lexer, tmp->i);
			tmp = parser->lexer;
		}
		arg_size--;
	}
	return (ft_cmd_new(str, parser->num_ops, parser->redirections));
}

int	handle_pipe_errors(t_state *tools, t_ops op)
{
	if (op == PIPELINE)
	{
		parser_double_token_error(tools, tools->lexer,
			tools->lexer->op);
		return (EXIT_FAILURE);
	}
	if (!tools->lexer)
	{
		parser_error(0, tools, tools->lexer);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// Helper Function 1:  Initialization
int	initialize_tools(t_state *tools)
{
	tools->cmd = NULL;
	count_pipes(tools->lexer, tools);
	if (tools->lexer->op == PIPELINE)
		return (parser_double_token_error(tools, tools->lexer,
				tools->lexer->op));
	return (EXIT_SUCCESS);
}

// Helper Function 2: Command Node Generation and Error Handling
int	generate_cmd_nodes_and_handle_errors(t_state *state)
{
	t_cmd			*node;
	t_parser		parser;

	while (state->lexer)
	{
		if (state->lexer && state->lexer->op == PIPELINE)
			ft_lexerdelone(&state->lexer, state->lexer->i);
		if (!state->lexer || \
			handle_pipe_errors(state, state->lexer->op))
		{
			parser_error(0, state, state->lexer);
			return (EXIT_FAILURE);
		}
		parser = init_parser(state->lexer, state);
		node = initialize_cmd(&parser);
		if (!node)
		{
			parser_error(0, state, parser.lexer);
			return (EXIT_FAILURE);
		}
		if (!state->cmd)
			state->cmd = node;
		else
			ft_cmd_add_back(&state->cmd, node);
		state->lexer = parser.lexer;
	}
	return (EXIT_SUCCESS);
}

int	ft_parser(t_state *tools)
{
	if (initialize_tools(tools) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (generate_cmd_nodes_and_handle_errors(tools) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
