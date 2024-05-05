/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:46:56 by fahmadia          #+#    #+#             */
/*   Updated: 2023/12/13 11:31:28 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "stdbool.h"
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>	// used for dirctory checking
# include <limits.h>
# include <termios.h>

# include "libft.h"
# include "ft_printf.h"
# include "lexer.h"
# include "env.h"
# include "parser.h"

/*
	@param n_ps: number of the process that has to be forked from parent ps
*/
typedef struct s_data
{
	const char	*prompt;
	t_list		*env;
	char		*input;
	t_list		*tokens;
	t_node		*tree;
	int			n_ps;
	int			*pid;
	int			e_code;
}	t_data;

/*
	Custom error values are in the range between 107 (106 is the max errno
	value) and 127.
*/
enum e_custom_errors
{
	CE_INVARG = 107,
	CE_INVALIDIDENTIFIER = 108,
	CE_TOOMANYARGS = 109,
	CE_SYNTAX_ERROR = 110,
	CE_SYNTAX_TREE = 111,
	CE_EXP = 112,
	CE_HERE_DOC = 113,
	CE_OVERFLOW = 114,
	CE_NUM_REQUIRED = 115,
	CE_INITENV = 116,
	CE_ISADIRECTORY = 126,
	CE_CMDNOTFOUND = 127
};

// --------------------------------------------------------------------- PARSER
void	parser(t_data *data);

// -------------------------------------------------------------------- SIGNALS
void	set_sig_action(int is_before_rl);
void	switch_g_var(t_data *data);

// ------------------------------------------------------------------ EXPANSION
void	expansion(t_data *data);
char	*expand(char *old_str, t_data *data);
int		get_n_dollars(char *s);
int		get_var_name_len(char *s);
char	*expand(char *s, t_data *data);
char	*remove_translation_operator(char *old_str);
char	*build_str(char *old_str, t_list *var_lst);
void	print_expansion(t_list *var_lst);

// -------------------------------------------------------------- QUOTE REMOVAL
void	quote_removal(t_data *data);
char	*remove_quote_pairs(char *s);
void	change_is_open_quote(char curr_quote, char *is_open);

// ------------------------------------------------------------------- HERE_DOC
int		here_doc(t_node *tree, t_data *data);
char	**collect_eofs(t_node *tree, t_data *data);
int		get_tmp_name(t_redir_data *redir_cont, int fd_tmp, int n);
int		get_interactive_input(int fd_tmp, char **eof, t_data *data);

// ------------------------------------------------------------------- EXECUTOR
void	executor(t_data *data);
int		execute_single_cmd(t_data *data);
int		execute_pipechain(t_data *data);

void	child_single_cmd(t_data *data);
void	child_pipechain(t_data *data, t_node *node, int *pipe, int *prev_pipe);
int		parent(t_data *data);

int		resolve_cmd_path(char **cmd_name, char **env);
char	*get_path_var(char **env);
int		file_and_exec_ok(char *cmd_name, char **abs_path, char	*path);
int		is_a_directory(char *cmd_name);
int		contains_a_path(char *cmd_name);

int		redirect_to_explicit(t_node *node);
int		redirect_to_pipes(int *pipe, int *prev_pipe);

int		is_builtin(t_cmd *cmd);
int		call_builtin_function(t_cmd *cmd, t_data *data);
int		run_builtin_same_ps(t_data *data);

void	free_child_and_exit(t_data *data, char **env, int e_code);
void	unlink_here_doc(t_node *tree);

// ------------------------------------------------------------------- BUILTINS
int		print_env(t_list *env);
int		cd(t_cmd *cmd, t_data *data);
char	*get_wd(void);
int		pwd(void);
int		exit_custom(t_cmd *cmd, t_data *data);
int		echo(t_data *data, t_cmd *cmd);
int		unset(t_cmd *cmd, t_data *data);
int		export(t_cmd *cmd, t_data *data);
int		print_exported(t_list *env);
int		check_export(char *arg, t_list **env);
char	**check_next_chars(char **sorted_env);
char	**sort_export(t_list *env);
void	print_each_line(int *i, bool *is_equal, char **sorted_env);
size_t	find_min_len(char *str1, char *str2);
void	swap(char **str1, char **str2);

// ---------------------------------------------------------------------- UTILS
void	terminal_config(void);
char	*get_wd(void);
void	error(char *s1, char *s2, int err_id);
int		ft_strcmp(const char *s1, const char *s2);
void	free_data(t_data *data);
int		get_substr_len(char *s, char c);
void	del_redir_content(void *content);

extern int	g_ctrl_c_pressed;

#endif
