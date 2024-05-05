/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:00:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/08 12:18:02 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_type	get_redir_type(t_tkn_type curr_tkn_type)
{
	if (curr_tkn_type == TKN_REDIR_IN)
		return (REDIR_IN);
	if (curr_tkn_type == TKN_REDIR_OUT)
		return (REDIR_OUT);
	if (curr_tkn_type == TKN_REDIR_APPEND)
		return (REDIR_APPEND);
	if (curr_tkn_type == TKN_HERE_DOC)
		return (REDIR_HERE_DOC);
	return (-1);
}

static t_list	*create_redir_content(t_tkn_data *tkn_content)
{
	t_redir_data	*new_cont;
	t_list			*new_node;

	new_cont = ft_calloc(1, sizeof(t_redir_data));
	if (!new_cont)
		return (NULL);
	new_cont->type = get_redir_type(tkn_content->type);
	new_cont->f_name = NULL;
	new_node = ft_lstnew(new_cont);
	if (!new_node)
		return (del_redir_content(new_cont), NULL);
	return (new_node);
}

/*
	Updates the t_list *redir inside t_cmd. Can accept a token which is either
	a redirection (< << >> >) or a string, which is automatically set as a
	file name of the last node of the list.
*/
int	update_cmd_redir(t_list *curr_tkn, t_cmd *cmd)
{
	t_tkn_data		*tkn_content;
	t_list			*new_node;
	t_list			*last;

	last = NULL;
	tkn_content = (t_tkn_data *)curr_tkn->content;
	if (is_redir(tkn_content->type))
	{
		new_node = create_redir_content(tkn_content);
		if (!new_node)
			return (1);
		ft_lstadd_back(&cmd->redir, new_node);
	}
	else
	{
		last = ft_lstlast(cmd->redir);
		((t_redir_data *)last->content)->f_name = ft_strdup(tkn_content->str);
		if (!((t_redir_data *)last->content)->f_name)
			return (1);
	}
	return (0);
}
