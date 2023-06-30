/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_simple_cmds_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:09:34 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 15:27:32 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ft_cmd_new(char **str, int num_ops, t_lexer *redirections)
{
	t_cmd	*new_element;

	new_element = malloc(sizeof(t_cmd));
	if (!new_element)
		return (0);
	new_element->str = str;
	new_element->builtin = cmd_arr(str[0]);
	new_element->hd_file_name = NULL;
	new_element->num_ops = num_ops;
	new_element->redirections = redirections;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	ft_cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	ft_cmd_rm_first(t_cmd **lst)
{
	t_cmd	*tmp;

	if (!*lst)
		return ;
	tmp = (*lst)->next;
	ft_lexerclear(&(*lst)->redirections);
	free(*lst);
	*lst = tmp;
}

void	ft_cmd_clear(t_cmd **lst)
{
	t_cmd	*tmp;
	t_lexer			*redirections_tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redirections_tmp = (*lst)->redirections;
		ft_lexerclear(&redirections_tmp);
		if ((*lst)->str)
			free_array((*lst)->str);
		if ((*lst)->hd_file_name)
			free((*lst)->hd_file_name);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

t_cmd	*ft_cmd_first(t_cmd *map)
{
	if (!map)
		return (NULL);
	while (map->prev != NULL)
	{
		map = map->prev;
	}
	return (map);
}
