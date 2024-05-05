/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_quote_status_to_tokens.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:12:23 by fahmadia          #+#    #+#             */
/*   Updated: 2023/12/12 14:22:01 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_quote_status_to_tkn(t_list *tkns_head)
{
	t_list			*current_node;
	char			tkn_first_char;
	t_quote			position;
	t_tkn_data		*tkn_data;
	t_quote_open	*quote_open;

	position = NOT_QUOTED;
	current_node = tkns_head;
	while (current_node)
	{
		tkn_data = ((t_tkn_data *)(current_node->content));
		tkn_first_char = *(tkn_data->str);
		quote_open = detect_quote(tkn_data, tkn_first_char, &position);
		tkn_data->quote = position;
		if (tkn_data->quote == IN_S_QUOTE && tkn_first_char == TKN_S_QUOTE)
			tkn_data->quote = NOT_QUOTED;
		if (tkn_data->quote == IN_D_QUOTE && tkn_first_char == TKN_D_QUOTE)
			tkn_data->quote = NOT_QUOTED;
		current_node = current_node->next;
	}
	quote_open->is_d_quote_open = false;
	quote_open->is_s_quote_open = false;
}
