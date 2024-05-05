/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote_removal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 08:34:59 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/08 11:23:20 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	args_quote_removal(t_cmd *cmd)
{
	int		i;
	char	*tmp;
	char	*arg;

	arg = NULL;
	tmp = NULL;
	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			arg = cmd->args[i];
			if (ft_strchr(arg, TKN_D_QUOTE) || ft_strchr(arg, TKN_S_QUOTE))
			{
				tmp = cmd->args[i];
				cmd->args[i] = remove_quote_pairs(cmd->args[i]);
				free(tmp);
				if (cmd->args[i] == NULL)
					return (error(cmd->args[i], NULL, CE_EXP), 1);
			}
			i++;
		}
	}
	return (0);
}

static int	redir_quote_removal(t_cmd *cmd)
{
	t_list			*redir;
	t_redir_data	*redir_cont;
	char			*tmp;

	redir = (t_list *)cmd->redir;
	redir_cont = NULL;
	tmp = NULL;
	while (redir)
	{
		redir_cont = (t_redir_data *)redir->content;
		tmp = redir_cont->f_name;
		if (redir_cont->type != REDIR_HERE_DOC)
		{
			if (ft_strchr(tmp, TKN_D_QUOTE) || ft_strchr(tmp, TKN_S_QUOTE))
			{
				redir_cont->f_name = remove_quote_pairs(redir_cont->f_name);
				if (!redir_cont->f_name)
					return (error(tmp, NULL, CE_EXP), free(tmp), 1);
				free(tmp);
			}
		}
		redir = redir->next;
	}
	return (0);
}

static int	check_quote_removal(t_cmd *cmd)
{
	if (args_quote_removal(cmd))
		return (1);
	if (redir_quote_removal(cmd))
		return (1);
	return (0);
}

/*
	If there is a syntax tree and not e_code quote_removal is performed.
	About redirections: here_doc quotes are not removed, because they are
	needed after to understand if expand the heredoc content or nor
	(see get_interactive_input() function).
*/
void	quote_removal(t_data *data)
{
	t_node	*node;
	t_cmd	*cmd;
	t_pipe	*pipe;

	if (!data->tree)
		return ;
	node = data->tree;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		cmd = pipe->left->content;
		if (check_quote_removal(cmd))
		{
			data->e_code = 1;
			return ;
		}
		node = pipe->right;
	}
	cmd = node->content;
	if (check_quote_removal(cmd))
		data->e_code = 1;
}
