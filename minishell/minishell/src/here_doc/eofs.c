/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eofs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:13:39 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 11:02:55 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	store_eofs_single_block(t_list *redir, char **eofs, int *i)
{
	t_list			*head;
	t_redir_data	*redir_cont;

	head = redir;
	while (head)
	{
		redir_cont = head->content;
		if (redir_cont->type == REDIR_HERE_DOC)
		{
			eofs[*i] = ft_strdup(redir_cont->f_name);
			if (!eofs[*i])
				return (free_dptr(eofs), error("eofs", NULL, errno), 1);
			if (get_tmp_name(redir_cont, -1, *i) == -1)
				return (free_dptr(eofs), 1);
			(*i)++;
		}
		head = head->next;
	}
	return (0);
}

static char	**store_eofs(t_node *tree, int n)
{
	t_pipe	*pipe;
	t_cmd	*cmd;
	char	**eofs;
	int		i;

	eofs = ft_calloc(n + 1, sizeof(char *));
	if (!eofs)
		return (error("eofs", NULL, errno), NULL);
	eofs[n] = NULL;
	i = 0;
	while (tree->type == IS_PIPE)
	{
		pipe = tree->content;
		cmd = (t_cmd *)pipe->left->content;
		if (store_eofs_single_block(cmd->redir, eofs, &i))
			return (NULL);
		tree = pipe->right;
	}
	cmd = (t_cmd *)tree->content;
	if (store_eofs_single_block(cmd->redir, eofs, &i))
		return (NULL);
	return (eofs);
}

static int	count_all_here_doc(t_list *redir)
{
	t_redir_data	*redir_cont;
	int				n;

	n = 0;
	if (!redir)
		return (0);
	while (redir)
	{
		redir_cont = redir->content;
		if (redir_cont->type == REDIR_HERE_DOC)
			n++;
		redir = redir->next;
	}
	return (n);
}

static int	get_n_eofs(t_node *tree)
{
	t_pipe	*pipe;
	t_cmd	*cmd;
	int		n;

	n = 0;
	while (tree->type == IS_PIPE)
	{
		pipe = tree->content;
		cmd = (t_cmd *)pipe->left->content;
		n += count_all_here_doc(cmd->redir);
		tree = pipe->right;
	}
	cmd = (t_cmd *)tree->content;
	n += count_all_here_doc(cmd->redir);
	return (n);
}

char	**collect_eofs(t_node *tree, t_data *data)
{
	int		n;
	char	**eofs;

	n = 0;
	n = get_n_eofs(tree);
	if (n == 0)
		return (NULL);
	eofs = store_eofs(tree, n);
	if (!eofs)
		data->e_code = 1;
	return (eofs);
}
