/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysakahar <ysakahar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:27:37 by ysakahar          #+#    #+#             */
/*   Updated: 2023/06/30 22:01:26 by ysakahar         ###   ########.fr       */
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
	int				num_ops;
	struct s_state	*state;
}	t_parser;

typedef struct s_state
{
	char			*args;
	char			**paths;
	char			**envp;
	struct s_cmd	*cmd;
	t_lexer			*lexer;
	char			*pwd;
	char			*old_pwd;
	int				pipes;
	int				*pid;
	bool			heredoc;
	bool			reset;
}	t_state;

typedef struct s_cmd
{
	char			**str;
	int				(*builtin)(t_state *, struct s_cmd *);
	int				num_ops;
	char			*hd_file_name;
	t_lexer			*redirections;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

int				parse_envp(t_state *state);
int				ft_parser(t_state *state);

//parser_utils
t_parser		init_parser(t_lexer *lexer, t_state *state);
void			count_pipes(t_lexer *lexer, t_state *state);
int				count_args(t_lexer *lexer);
t_lexer			*find_next_cmd(t_lexer *lexer_lst);

//handle_redirections
int				add_new_redirection(t_lexer *tmp, t_parser *parser);
int				handle_heredoc(t_parser *parser, t_lexer *tmp);
void			rm_redirections(t_parser *parser);
int				reset_tools(t_state *state);
void			init_stri(int i, int j, t_state *state);
char			**expander(t_state *state, char **str);
char			*expander_str(t_state *state, char *str);
size_t			dollar_sign(char *str);
char			*char_to_str(char c);
int				after_dol_lenght(char *str, int j);
void			free_things(char *tmp2, t_state *state, int i);
void			print_parser(t_cmd cmd);
char			*delete_quotes_value(char *str);
void			sigint_handler(int sig);
void			sigquit_handler(int sig);
void			init_signals(void);
char			*delete_quotes(char *str, char c);
char			*delete_quotes_export(char *str, char c);
int				question_mark(char **tmp);

//builtins
int				(*cmd_arr(char *str))(t_state *state, t_cmd *cmd);

// utils
int				implement_tools(t_state *state);
char			**ft_arrdup(char **arr);

//t_simple_cmds_utils
t_cmd			*ft_cmd_new(char **str, int num_ops, t_lexer *redirections);
void			ft_cmd_add_back(t_cmd **lst, t_cmd *new);
void			ft_cmd_rm_first(t_cmd **lst);
void			ft_cmd_clear(t_cmd **lst);
t_cmd			*ft_cmd_first(t_cmd *map);

//t_lexer_utils
t_lexer			*ft_lexernew(char *str, int op);
void			ft_lexeradd_back(t_lexer **lst, t_lexer *new);
void			ft_lexerdelone(t_lexer **lst, int i);
void			ft_lexerclear(t_lexer **lst);
int				add_node(char *str, t_ops op, t_lexer **lexer);
t_ops			check_op(int c);
int				handle_op(char *str, int i, t_lexer **lexer);

/* lexer */
int				ft_lexer(t_state *state);
int				is_delimiter(char c);
int				skip_delimiter(char *str, int i);
int				count_quotes(char *str);
int				handle_quotes(int i, char *str, char del);

/* executor */
int				check_redirections(t_cmd *cmd);
int				executor(t_state *state);
t_cmd			*call_expander(t_state *state, t_cmd *cmd);
int				pipe_wait(int *pid, int amount);

// handle_cmd
int				find_cmd(t_cmd *cmd, t_state *state);
void			handle_cmd(t_cmd *cmd, t_state *state);
void			dup_cmd(t_cmd *cmd, t_state *state, int end[2], int fd_in);
void			single_cmd(t_cmd *cmd, t_state *state);

// heredoc
int				send_heredoc(t_state *state, t_cmd *cmd);

/* initialization */
int				parse_envp(t_state *state);
void			initialize_signals(void);
int				implement_tools(t_state *state);
char			**ft_arrdup(char **arr);
void			initialization(t_state *state, char **envp);

/* error */
void			parser_error(int error, t_state *state, t_lexer *lexer);
int				parser_double_token_error(t_state *state, t_lexer *lexer,
					t_ops op);
void			lexer_error(int error, t_state *state);
int				cmd_not_found(char *str);
int				export_error(char *c);
int				ft_error(int error, t_state *state);

//cmd
void			change_path(t_state *state);
int				cmd_echo(t_state *state, t_cmd *cmd);
int				cmd_cd(t_state *state, t_cmd *cmd);
int				cmd_pwd(t_state *state, t_cmd *cmd);
int				cmd_export(t_state *state, t_cmd *cmd);
int				cmd_unset(t_state *state, t_cmd *cmd);
int				cmd_env(t_state *state, t_cmd *cmd);
int				cmd_exit(t_state *state, t_cmd *cmd);
int				cmd_continue(t_state *state, t_cmd *cmd);
size_t			equal_sign(char *str);
int				check_valid_identifier(char c);

/* main */

#endif