/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_quoted_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:03:49 by fahmadia          #+#    #+#             */
/*   Updated: 2023/12/10 18:12:46 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_close_pair(t_list *cur_node, t_list *cur_quoted_node, char tkn_type)
{
	t_tkn_data	*cur_quoted_tkn_data;
	t_tkn_data	*cur_tkn_data;

	if (!cur_quoted_node)
		return (false);
	cur_quoted_tkn_data = (t_tkn_data *)(cur_quoted_node->content);
	cur_tkn_data = (t_tkn_data *)(cur_node->content);
	if (((cur_quoted_tkn_data->str)[0] == tkn_type
		&& (cur_quoted_tkn_data)->quote_status == CLOSED_QUOTE))
	{
		(cur_tkn_data)->quote_status = OPEN_AND_CLOSED_PAIRS;
		if (tkn_type == TKN_S_QUOTE)
		{
			(cur_tkn_data)->type = TKN_S_QUOTED_STR;
			(cur_tkn_data)->quote = IN_S_QUOTE;
		}
		else if (tkn_type == TKN_D_QUOTE)
		{
			(cur_tkn_data)->type = TKN_D_QUOTED_STR;
			(cur_tkn_data)->quote = IN_D_QUOTE;
		}
		return (true);
	}
	return (false);
}

void	merge(t_list *cur_node, t_list *cur_quoted_node, char tkn_type)
{
	t_tkn_data	*cur_quoted_tkn_data;
	t_tkn_data	*cur_tkn_data;

	cur_tkn_data = (t_tkn_data *)(cur_node->content);
	cur_quoted_tkn_data = (t_tkn_data *)(cur_quoted_node->content);
	if (tkn_type == TKN_S_QUOTE
		&& cur_quoted_tkn_data->quote_status != CLOSED_QUOTE)
	{
		(cur_tkn_data)->type = TKN_NOT_CLOSED_S_QUOTE_STR;
		(cur_tkn_data)->quote = IN_S_QUOTE;
	}
	else if (tkn_type == TKN_D_QUOTE
		&& cur_quoted_tkn_data->quote_status != CLOSED_QUOTE)
	{
		(cur_tkn_data)->type = TKN_NOT_CLOSED_D_QUOTE_STR;
		(cur_tkn_data)->quote = IN_D_QUOTE;
	}
}

bool	is_opening_quote(t_tkn_data *cur_tkn_data)
{
	if ((*(cur_tkn_data->str) == TKN_S_QUOTE
			|| (cur_tkn_data->str)[0] == TKN_D_QUOTE)
		&& cur_tkn_data->quote_status == OPEN_QUOTE)
		return (true);
	else
		return (false);
}

void	merge_tokens(t_list *tkns_head, t_list *cur_node, t_list *cur_q_node)
{
	t_tkn_data	*cur_tkn_data;
	t_tkn_data	*cur_quoted_tkn_data;
	char		tkn_type;
	t_list		*temp;

	cur_tkn_data = (t_tkn_data *)(cur_node->content);
	cur_q_node = cur_node->next;
	tkn_type = *(cur_tkn_data->str);
	while (cur_q_node)
	{
		temp = cur_q_node->next;
		merge(cur_node, cur_q_node, tkn_type);
		cur_quoted_tkn_data = (t_tkn_data *)(cur_q_node->content);
		join_two_strs(&cur_tkn_data->str, cur_quoted_tkn_data->str);
		((t_tkn_data *)(tkns_head->content))->list_size--;
		(cur_tkn_data)->str_len = ft_strlen((cur_tkn_data)->str);
		cur_tkn_data->white_space = cur_quoted_tkn_data->white_space;
		if (is_close_pair(cur_node, cur_q_node, tkn_type))
		{
			remove_next_node(cur_node);
			return ;
		}
		remove_next_node(cur_node);
		cur_q_node = temp;
	}
}

void	merge_quoted_tokens(t_list *tkns_head)
{
	t_list		*cur_node;
	t_list		*cur_quoted_node;
	t_tkn_data	*cur_tkn_data;

	cur_node = tkns_head;
	cur_quoted_node = tkns_head;
	while (cur_node)
	{
		cur_tkn_data = (t_tkn_data *)(cur_node->content);
		if (is_opening_quote(cur_tkn_data))
			merge_tokens(tkns_head, cur_node, cur_quoted_node);
		cur_node = cur_node->next;
	}
}
