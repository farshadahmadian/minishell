/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_dollar_char_with_next_token.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 10:52:43 by fahmadia          #+#    #+#             */
/*   Updated: 2023/12/10 18:12:16 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_needed_to_merge(char first_char)
{
	bool	is_alpha;
	bool	is_digit;
	bool	is_under_score;

	is_alpha = ft_isalpha(first_char);
	is_digit = ft_isdigit(first_char);
	is_under_score = first_char == '_';
	if (!(is_alpha || is_digit || is_under_score || first_char == '$'
			|| first_char == '?' || first_char == '\"'
			|| first_char == '\'' ))
		return (false);
	else
		return (true);
}

void	merge_dollar_char_with_next_token(t_list *tkns_head)
{
	t_list		*cur_node;
	t_tkn_data	*cur_tkn_d;
	t_tkn_data	*next_tkn_d;

	cur_node = tkns_head;
	while (cur_node && cur_node->next)
	{
		cur_tkn_d = (t_tkn_data *)(cur_node->content);
		next_tkn_d = (t_tkn_data *)(cur_node->next->content);
		if ((cur_tkn_d->str)[0] == TKN_DOLLAR_CHAR)
		{
			if (!is_needed_to_merge(*(next_tkn_d->str)))
			{
				cur_node = cur_node->next;
				continue ;
			}
			cur_tkn_d->str = join_two_strs(&(cur_tkn_d->str), next_tkn_d->str);
			remove_next_node(cur_node);
			cur_tkn_d->type = TKN_ENV_VAR;
			cur_tkn_d->str_len = ft_strlen(cur_tkn_d->str);
			((t_tkn_data *)(tkns_head->content))->list_size--;
			continue ;
		}
		cur_node = cur_node->next;
	}
}
