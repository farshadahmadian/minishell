/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:31:07 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 14:36:25 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*
	SYNTAX TREE
	The tree is composed by t_node items. Each t_node can be either of type
	IS_PIPE or IS_CMD, and consequently its content is either t_pipe or t_cmd.
*/
enum e_node
{
	IS_PIPE,
	IS_CMD
};

typedef struct s_node
{
	int			n;
	enum e_node	type;
	void		*content;
}	t_node;

/*
	t_pipe is the content type of t_node, when its type is IS_PIPE.
	It holds just two address to 2 different t_node.
*/
typedef struct s_pipe
{
	struct s_node	*left;
	struct s_node	*right;
}	t_pipe;

/*
	t_cmd is the content of t_node in case its type is IS_CMD.
	It holds information about the tokens in a block delimited by start/end of
	the input, and by pipes.
*/
typedef struct s_cmd
{
	char		**args;
	t_list		*redir;
}	t_cmd;

typedef enum e_redir_type
{
	REDIR_IN = '<',
	REDIR_OUT = '>',
	REDIR_HERE_DOC = 8,
	REDIR_APPEND = 7
}	t_redir_type;

typedef struct s_redir_data
{
	char			*f_name;
	t_redir_type	type;
}	t_redir_data;

// ---------------------------------------------------------------- SYNTAX TREE
t_node	*build_syntax_tree(t_list *token, int n);
void	free_tree(t_node *tree);
void	free_cmd_node(t_node *node_c);
void	free_pipe_node(t_node *node_p);
void	free_dptr(char **p);

// -------------------------------------------------------------- SYNTAX ERRORS
int		check_for_syntax_err(t_list *tkn, int i);
int		is_redir(t_tkn_type tkn_type);

// ----------------------------------------------------------- UPDATE CMD TABLE
int		update_cmd_node(t_list *curr_tkn, t_list *prev_tkn, t_node *node);
int		update_cmd_redir(t_list *curr_tkn, t_cmd *cmd);
int		update_cmd_args(char *arg, t_cmd *cmd);

// ---------------------------------------------------------------- PRINT UTILS
void	print_syntax_tree(t_node *root);
void	print_redir_list(t_list *redir);
void	print_cmd_args(char **args);
void	print_tree_construction(char *prev_tkn, char *curr_tkn, char *next);

#endif
