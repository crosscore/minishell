/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:10:15 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/29 17:23:22 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_simple_cmds	*initialize_cmd(t_parser_tools *parser_tools)
{
	char	**str;
	int		i;
	int		arg_size;
	t_lexer	*tmp;

	i = 0;
	rm_redirections(parser_tools);
	arg_size = count_args(parser_tools->lexer_list);
	str = ft_calloc(arg_size + 1, sizeof(char *));
	if (!str)
		parser_error(1, parser_tools->tools, parser_tools->lexer_list);
	tmp = parser_tools->lexer_list;
	while (arg_size > 0)
	{
		if (tmp->str)
		{
			str[i++] = ft_strdup(tmp->str);
			ft_lexerdelone(&parser_tools->lexer_list, tmp->i);
			tmp = parser_tools->lexer_list;
		}
		arg_size--;
	}
	return (ft_simple_cmdsnew(str,
			parser_tools->num_redirections, parser_tools->redirections));
}

int	handle_pipe_errors(t_tools *tools, t_ops op)
{
	if (op == PIPELINE)
	{
		parser_double_token_error(tools, tools->lexer_list,
			tools->lexer_list->op);
		return (EXIT_FAILURE);
	}
	if (!tools->lexer_list)
	{
		parser_error(0, tools, tools->lexer_list);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// Helper Function 1:  Initialization
int	initialize_tools(t_tools *tools)
{
	tools->simple_cmds = NULL;
	count_pipes(tools->lexer_list, tools);
	if (tools->lexer_list->op == PIPELINE)
		return (parser_double_token_error(tools, tools->lexer_list,
				tools->lexer_list->op));
	return (EXIT_SUCCESS);
}

// Helper Function 2: Command Node Generation and Error Handling
int	generate_cmd_nodes_and_handle_errors(t_tools *tools)
{
	t_simple_cmds	*node;
	t_parser_tools	parser_tools;

	while (tools->lexer_list)
	{
		if (tools->lexer_list && tools->lexer_list->op == PIPELINE)
			ft_lexerdelone(&tools->lexer_list, tools->lexer_list->i);
		if (!tools->lexer_list || \
			handle_pipe_errors(tools, tools->lexer_list->op))
		{
			parser_error(0, tools, tools->lexer_list);
			return (EXIT_FAILURE);
		}
		parser_tools = init_parser_tools(tools->lexer_list, tools);
		node = initialize_cmd(&parser_tools);
		if (!node)
		{
			parser_error(0, tools, parser_tools.lexer_list);
			return (EXIT_FAILURE);
		}
		if (!tools->simple_cmds)
			tools->simple_cmds = node;
		else
			ft_simple_cmdsadd_back(&tools->simple_cmds, node);
		tools->lexer_list = parser_tools.lexer_list;
	}
	return (EXIT_SUCCESS);
}

// The original function would look like this:
int	parser(t_tools *tools)
{
	if (initialize_tools(tools) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (generate_cmd_nodes_and_handle_errors(tools) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
