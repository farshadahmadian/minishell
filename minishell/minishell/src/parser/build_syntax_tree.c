/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_syntax_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:32:21 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 10:50:42 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Iterates the token t_list and updates the cmd table. When a pipe or the end
	of the line is found, it returns it. Block is something between the start
	of the line and a pipe, between 2 pipe, or between a pipe and end of line.
	Example. [block1] | [block2] | [block3]
*/
static t_list	*parse_tkn_block(t_list *curr_tkn, t_node *node_c)
{
	t_list		*prev_tkn;

	prev_tkn = NULL;
	while (curr_tkn)
	{
		if (((t_tkn_data *)curr_tkn->content)->type == TKN_PIPE)
			return (curr_tkn);
		if (update_cmd_node(curr_tkn, prev_tkn, node_c))
			return (NULL);
		prev_tkn = curr_tkn;
		if (curr_tkn->next)
			curr_tkn = curr_tkn->next;
		else
			break ;
	}
	return (curr_tkn);
}

static t_node	*init_pipe_node(int n)
{
	t_node	*node_p;

	node_p = ft_calloc(1, sizeof(t_node));
	if (!node_p)
		return (NULL);
	node_p->type = IS_PIPE;
	node_p->n = n + 1;
	node_p->content = ft_calloc(1, sizeof(t_pipe));
	if (!node_p->content)
		return (free(node_p), NULL);
	((t_pipe *)node_p->content)->left = NULL;
	((t_pipe *)node_p->content)->right = NULL;
	return (node_p);
}

static t_node	*init_cmd_node(int n)
{
	t_node	*node_c;
	t_cmd	*cmd;

	node_c = ft_calloc (1, sizeof(t_node));
	if (!node_c)
		return (NULL);
	node_c->type = IS_CMD;
	node_c->n = n;
	node_c->content = ft_calloc(1, sizeof(t_cmd));
	if (!node_c->content)
		return (free(node_c), NULL);
	cmd = (t_cmd *)node_c->content;
	cmd->args = NULL;
	cmd->redir = NULL;
	return (node_c);
}

static void	free_cmd_and_pipe_node(t_node *node_c, t_node *node_p)
{
	free_cmd_node(node_c);
	free_pipe_node(node_p);
}

/*
	The function build the syntax tree recursively. The operations:
		1)	Init a new cmd node.
		2)	Copy the next tkn block (block means until the pipe sign)
			populating the cmd table with arguments and redirections.
		3)	After it, it checks if parse_tkn_block() function exited because
			of a pipe or end of the line. If it was a pipe sign, a t_pipe node
			is created. The cmd node created is assgined to pipe->left,
			while the right one is assigned to the result of the function
			which calls itself.
		4)	The function always returns a pipe node, until it reaches the end
			of the line; in that last case, a cmd node is returned.
		5)	The last returned value is the first pipe node created, which
			is the top of the tree.
	@param n - is just a number to identify which node of the tree it is and
	visualize it when printed.
*/
t_node	*build_syntax_tree(t_list *tkn, int n)
{
	t_node	*node_c;
	t_node	*node_p;

	node_c = init_cmd_node(n);
	if (!node_c)
		return (NULL);
	tkn = parse_tkn_block(tkn, node_c);
	if (!tkn)
		return (NULL);
	node_p = NULL;
	if (ft_strcmp(((t_tkn_data *)tkn->content)->str, "|") == 0)
	{
		tkn = tkn->next;
		node_p = init_pipe_node(n);
		if (!node_p)
			return (free_cmd_and_pipe_node(node_c, node_p), NULL);
		((t_pipe *)node_p->content)->left = node_c;
		((t_pipe *)node_p->content)->right = build_syntax_tree(tkn, n + 2);
		if (!((t_pipe *)node_p->content)->right)
			return (free_cmd_and_pipe_node(node_c, node_p), NULL);
		return (node_p);
	}
	return (node_c);
}
