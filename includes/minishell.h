/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:27:37 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 13:43:18 by ysakahar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include "libft.h"

# define RESET_COLOR	"\033[0m"
# define BLACK   		"\033[30m"
# define RED     		"\033[31m"
# define GREEN   		"\033[32m"
# define YELLOW  		"\033[33m"
# define BLUE    		"\033[34m"
# define MAGENTA 		"\033[35m"
# define CYAN    		"\033[36m"
# define WHITE   		"\033[37m"
# define GREY    		"\033[90m"
# define HEREDOC_MSG	"\033[1;34mheredoc> \033[0m"
# define READLINE_MSG	"\033[1;36mminishell\033[34m$ \033[0m"

typedef struct s_global
{
	int	error_num;
	int	stop_heredoc;
	int	in_cmd;
	int	in_heredoc;
}	t_global;

t_global	g_global;

/*  PIPELINE: |  */
/*  REDIRECT_OUTPUT: >  */
/*  APPEND_OUTPUT: >>  */
/*  REDIRECT_INPUT: <  */
/*  HEREDOC: <<  */
typedef enum s_ops
{
	PIPELINE = 1,
	REDIRECT_OUTPUT,
	APPEND_OUTPUT,
	REDIRECT_INPUT,
	HEREDOC,
}	t_ops;

typedef struct s_lexer
{
	char			*str;
	t_ops			op;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_parser
{
	t_lexer			*lexer;
	t_lexer			*redirections;
	int				num_redirections;
	struct s_state	*state;
}	t_parser;

typedef struct s_state
{
	char					*args;
	char					**paths;
	char					**envp;
	struct s_simple_cmds	*simple_cmds;
	t_lexer					*lexer;
	char					*pwd;
	char					*old_pwd;
	int						pipes;
	int						*pid;
	bool					heredoc;
	bool					reset;
}	t_state;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_state *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

int				parse_envp(t_state *tools);
int				ft_parser(t_state *tools);

//parser_utils
t_parser		init_parser(t_lexer *lexer, t_state *tools);
void			count_pipes(t_lexer *lexer, t_state *tools);
int				count_args(t_lexer *lexer);
t_lexer			*find_next_cmd(t_lexer *lexer_lst);

//handle_redirections
int				add_new_redirection(t_lexer *tmp, t_parser *parser_tools);
int				handle_heredoc(t_parser *parser_tools, t_lexer *tmp);
void			rm_redirections(t_parser *parser_tools);
int				reset_tools(t_state *tools);
void			init_stri(int i, int j, t_state *tools);
char			**expander(t_state *tools, char **str);
char			*expander_str(t_state *tools, char *str);
size_t			dollar_sign(char *str);
char			*char_to_str(char c);
int				after_dol_lenght(char *str, int j);
void			free_things(char *tmp2, t_state *tools, int i);
void			print_parser(t_simple_cmds simple_cmds);
char			*delete_quotes_value(char *str);
void			sigint_handler(int sig);
void			sigquit_handler(int sig);
void			init_signals(void);
char			*delete_quotes(char *str, char c);
char			*delete_quotes_export(char *str, char c);
int				question_mark(char **tmp);

//builtins
int		(*cmd_arr(char *str))(t_state *tools, t_simple_cmds *simple_cmd);

// utils
int				count_quotes(char *line);
int				implement_tools(t_state *tools);
char			**ft_arrdup(char **arr);
int				minishell_loop(t_state *tools);

//t_simple_cmds_utils
t_simple_cmds	*ft_simple_cmdsnew(char **str,
					int num_redirections, t_lexer *redirections);
void			ft_simple_cmdsadd_back(t_simple_cmds **lst, t_simple_cmds *new);
void			ft_simple_cmds_rm_first(t_simple_cmds **lst);
void			ft_simple_cmdsclear(t_simple_cmds **lst);
t_simple_cmds	*ft_simple_cmdsfirst(t_simple_cmds *map);

//t_lexer_utils
t_lexer			*ft_lexernew(char *str, int op);
void			ft_lexeradd_back(t_lexer **lst, t_lexer *new);
void			ft_lexerdelone(t_lexer **lst, int i);
void			ft_lexerclear(t_lexer **lst);
int				token_reader(t_state *tools);
int				add_node(char *str, t_ops op, t_lexer **lexer);
t_ops			check_token(int c);
int				handle_token(char *str, int i, t_lexer **lexer);

/* lexer */
int				handle_quotes(int i, char *str, char del);

/* executor */
int				check_redirections(t_simple_cmds *cmd);
int				executor(t_state *tools);
t_simple_cmds	*call_expander(t_state *tools, t_simple_cmds *cmd);
int				pipe_wait(int *pid, int amount);

// handle_cmd
int				find_cmd(t_simple_cmds *cmd, t_state *tools);
void			handle_cmd(t_simple_cmds *cmd, t_state *tools);
void			dup_cmd(t_simple_cmds *cmd, t_state *tools,
					int end[2], int fd_in);
void			single_cmd(t_simple_cmds *cmd, t_state *tools);

// heredoc
int				send_heredoc(t_state *tools, t_simple_cmds *cmd);

/* initialization */
int				parse_envp(t_state *tools);
void			initialize_signals(void);
int				implement_tools(t_state *tools);
char			**ft_arrdup(char **arr);
void			initialization(t_state *tools, char **envp);

/* error */
void			parser_error(int error, t_state *tools, t_lexer *lexer);
int				parser_double_token_error(t_state *tools, t_lexer *lexer,
					t_ops op);
void			lexer_error(int error, t_state *tools);
int				cmd_not_found(char *str);
int				export_error(char *c);
int				ft_error(int error, t_state *tools);

//cmd
void			change_path(t_state *tools);
int				cmd_echo(t_state *tools, t_simple_cmds *simple_cmd);
int				cmd_cd(t_state *tools, t_simple_cmds *simple_cmd);
int				cmd_pwd(t_state *tools, t_simple_cmds *simple_cmd);
int				cmd_export(t_state *tools, t_simple_cmds *simple_cmd);
int				cmd_unset(t_state *tools, t_simple_cmds *simple_cmd);
int				cmd_env(t_state *tools, t_simple_cmds *simple_cmd);
int				cmd_exit(t_state *tools, t_simple_cmds *simple_cmd);
int				cmd_continue(t_state *tools, t_simple_cmds *simple_cmd);
size_t			equal_sign(char *str);
int				check_valid_identifier(char c);

/* main */

#endif