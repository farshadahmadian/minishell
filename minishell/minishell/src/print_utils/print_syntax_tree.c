/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 08:30:02 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 15:49:58 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_args(char **args)
{
	int	i;

	if (!args)
	{
		ft_printf("No arguments\n");
		return ;
	}
	i = 0;
	ft_printf("{");
	while (args[i])
	{
		ft_printf(" %s ", args[i]);
		i++;
	}
	ft_printf("}\n");
}

void	print_redir_list(t_list *redir)
{
	t_redir_data	*content;
	char			*type;

	if (!redir)
	{
		ft_printf("	No redirections!\n");
		return ;
	}
	while (redir)
	{
		content = (t_redir_data *)redir->content;
		ft_printf("	File name: [ %s ]", content->f_name);
		if (content->type == REDIR_IN)
			type = "<";
		else if (content->type == REDIR_OUT)
			type = ">";
		else if (content->type == REDIR_APPEND)
			type = ">>";
		else if (content->type == REDIR_HERE_DOC)
			type = "<<";
		ft_printf("	type [ %s ]\n", type);
		redir = redir->next;
	}
}

static void	print_cmd_node(t_cmd *cmd, int n)
{
	ft_printf("CMD	[%d]\n", n);
	ft_printf("args	");
	print_cmd_args(cmd->args);
	ft_printf("redir");
	print_redir_list(cmd->redir);
	ft_printf("- - - - - - - - - - - - - - - - - - - - - - - -\n");
}

void	print_syntax_tree(t_node *tree)
{
	t_pipe	*pipe;

	ft_printf("\n____SYNTAX TREE____");
	if (!tree)
		return ;
	if (tree->type == IS_CMD)
	{
		ft_printf("___First node is CMD___\n\n");
		print_cmd_node(tree->content, tree->n);
		ft_printf("\n");
		return ;
	}
	ft_printf("___First node is PIPE___\n\n");
	while (tree->type == IS_PIPE)
	{
		pipe = (t_pipe *)tree->content;
		print_cmd_node(pipe->left->content, pipe->left->n);
		tree = pipe->right;
	}
	print_cmd_node(pipe->right->content, pipe->right->n);
	ft_printf("\n");
}
