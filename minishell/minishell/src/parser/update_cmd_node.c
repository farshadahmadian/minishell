/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:53:33 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/08 12:09:08 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Take the current token assuming that syntax error are already catched in
	previous steps. @line - if (!prev_tkn) - verifies if the curr_tkn is
	the first of the token list.
*/
int	update_cmd_node(t_list *tkn, t_list *prev_tkn, t_node *node)
{
	t_tkn_data	*curr_cont;
	t_tkn_data	*prev_cont;

	curr_cont = NULL;
	prev_cont = NULL;
	if (tkn)
		curr_cont = (t_tkn_data *)tkn->content;
	if (!prev_tkn)
	{
		if (is_redir(curr_cont->type))
			return (update_cmd_redir(tkn, node->content));
		else
			return (update_cmd_args(curr_cont->str, node->content));
	}
	else
	{
		prev_cont = (t_tkn_data *)prev_tkn->content;
		if (!is_redir(curr_cont->type) && !is_redir(prev_cont->type))
			return (update_cmd_args(curr_cont->str, node->content));
		else if (!is_redir(curr_cont->type) && is_redir(curr_cont->type))
			return (update_cmd_redir(tkn, node->content));
		else
			return (update_cmd_redir(tkn, node->content));
	}
	return (0);
}
