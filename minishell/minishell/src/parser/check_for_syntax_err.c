/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_syntax_err.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:06:20 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 15:58:20 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_tkn_type tkn_type)
{
	if (tkn_type == TKN_REDIR_APPEND
		|| tkn_type == TKN_HERE_DOC
		|| tkn_type == TKN_REDIR_IN
		|| tkn_type == TKN_REDIR_OUT)
		return (tkn_type);
	return (0);
}

static int	is_redir_syntax_err(t_tkn_data *next_tkn)
{
	if (is_redir(next_tkn->type))
		return (1);
	if (next_tkn->type == TKN_NEW_LINE
		|| next_tkn->type == TKN_TAB_CHAR
		|| next_tkn->type == TKN_PIPE)
		return (1);
	return (0);
}

static int	is_pipe_syntax_err(t_tkn_data *next_tkn)
{
	if (!next_tkn)
		return (1);
	if (next_tkn->type == TKN_PIPE)
		return (1);
	return (0);
}

static int	check_curr_next(t_tkn_data *curr_tkn, t_tkn_data *next_tkn)
{
	if (is_redir(curr_tkn->type) && is_redir_syntax_err(next_tkn))
		return (error(next_tkn->str, NULL, CE_SYNTAX_ERROR), 1);
	if (curr_tkn->type == TKN_PIPE && is_pipe_syntax_err(next_tkn))
		return (error(next_tkn->str, NULL, CE_SYNTAX_ERROR), 1);
	return (0);
}

int	check_for_syntax_err(t_list *tkn, int i)
{
	t_tkn_data	*curr_tkn;

	curr_tkn = NULL;
	while (tkn)
	{
		curr_tkn = (t_tkn_data *)tkn->content;
		if (curr_tkn->type == TKN_PIPE && i == 0)
			return (error(curr_tkn->str, NULL, CE_SYNTAX_ERROR), 1);
		if (curr_tkn->quote_status == OPEN_QUOTE)
			return (error("quotes", NULL, CE_SYNTAX_ERROR), 1);
		if (tkn->next)
		{
			if (check_curr_next(curr_tkn, tkn->next->content))
				return (1);
		}
		else
		{
			if (is_redir(curr_tkn->type) || curr_tkn->type == TKN_PIPE)
				return (error("newline", NULL, CE_SYNTAX_ERROR), 1);
		}
		i++;
		tkn = tkn->next;
	}
	return (0);
}
