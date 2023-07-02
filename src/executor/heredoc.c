/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:11:17 by ysakahar          #+#    #+#             */
/*   Updated: 2023/07/02 14:57:33 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_heredoc(t_lexer *heredoc, bool quotes,
					t_state *state, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline(HEREDOC_MSG);
	while (line && ft_strncmp(heredoc->str, line, ft_strlen(heredoc->str))
		&& g_global.stop_heredoc == 0)
	{
		if (quotes == false)
			line = expander_str(state, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(HEREDOC_MSG);
	}
	free(line);
	if (g_global.stop_heredoc == 1 || line == NULL)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

int	ft_heredoc(t_state *state, t_lexer *heredoc, char *file_name)
{
	bool	quotes;
	int		sl;

	sl = EXIT_SUCCESS;
	if ((heredoc->str[0] == '\"'
			&& heredoc->str[ft_strlen(heredoc->str) - 1] == '\"')
		|| (heredoc->str[0] == '\''
			&& heredoc->str[ft_strlen(heredoc->str) - 1] == '\''))
		quotes = true;
	else
		quotes = false;
	delete_quotes(heredoc->str, '\"');
	delete_quotes(heredoc->str, '\'');
	g_global.stop_heredoc = 0;
	g_global.in_heredoc = 1;
	sl = create_heredoc(heredoc, quotes, state, file_name);
	g_global.in_heredoc = 0;
	state->is_heredoc = true;
	return (sl);
}

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

int	send_heredoc(t_state *state, t_cmd *cmd)
{
	t_lexer	*start;
	int		sl;

	start = cmd->redirections;
	sl = EXIT_SUCCESS;
	while (cmd->redirections)
	{
		if (cmd->redirections->op == HEREDOC)
		{
			if (cmd->hd_file_name)
				free(cmd->hd_file_name);
			cmd->hd_file_name = generate_heredoc_filename();
			sl = ft_heredoc(state, cmd->redirections, cmd->hd_file_name);
			if (sl)
			{
				g_global.error_num = 1;
				return (ft_reset(state));
			}
		}
		cmd->redirections = cmd->redirections->next;
	}
	cmd->redirections = start;
	return (EXIT_SUCCESS);
}
