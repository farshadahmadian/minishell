/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:18:55 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 09:13:04 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_expansion(t_cmd *cmd, t_data *data)
{
	t_list			*redir;
	t_redir_data	*redir_content;
	char			*tmp;

	redir = (t_list *)cmd->redir;
	redir_content = NULL;
	tmp = NULL;
	while (redir)
	{
		redir_content = (t_redir_data *)redir->content;
		if (redir && redir_content->type != REDIR_HERE_DOC)
		{
			if (ft_strchr(redir_content->f_name, '$'))
			{
				tmp = redir_content->f_name;
				redir_content->f_name = expand(redir_content->f_name, data);
				free(tmp);
				if (!redir_content->f_name)
					return (error(redir_content->f_name, NULL, CE_EXP), 1);
			}
		}
		redir = redir->next;
	}
	return (0);
}

static int	args_expansion(t_cmd *cmd, t_data *data)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			if (ft_strchr(cmd->args[i], '$'))
			{
				tmp = cmd->args[i];
				cmd->args[i] = expand(cmd->args[i], data);
				free(tmp);
				if (cmd->args[i] == NULL)
					return (error(cmd->args[i], NULL, CE_EXP), 1);
			}
			i++;
		}
	}
	return (0);
}

static int	check_expansion(t_cmd *cmd, t_data *data)
{
	if (args_expansion(cmd, data))
		return (1);
	if (redir_expansion(cmd, data))
		return (1);
	return (0);
}

/*
	The expander perform the following operations (IF a syntax tree is built):
		• Expands only args and redir which are not HERE_DOC
		• Removes the $ from the string, like $"..." or $'...'
		• Iterate through the string and counts ALL remaining $
		• Iterate another time and switches the open/close single/double quotes
			so that the expansion is performed or not
		• If the most external quotes are not single, the expansion is done
		• After the expansion, the quote_removal() function is called to
			remove the remaining unuseful quotes
*/
void	expansion(t_data *data)
{
	t_node	*node;
	t_pipe	*pipe;
	t_cmd	*cmd;

	if (!data->tree)
		return ;
	node = data->tree;
	while (node->type == IS_PIPE)
	{
		pipe = (t_pipe *)node->content;
		cmd = (t_cmd *)pipe->left->content;
		if (check_expansion(cmd, data))
		{
			data->e_code = 1;
			return ;
		}
		node = pipe->right;
	}
	cmd = (t_cmd *)node->content;
	if (check_expansion(cmd, data))
	{
		data->e_code = 1;
		return ;
	}
}
