/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:15:53 by fahmadia          #+#    #+#             */
/*   Updated: 2023/12/12 14:30:36 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_empty_input(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (ft_strlen(s) == i)
		return (1);
	return (0);
}

void	lexer(char *input, t_list **tkns_head)
{
	if (is_empty_input(input))
		return ;
	tokenize_input(input, tkns_head);
	assign_type_to_tkn(*tkns_head);
	assign_quote_status_to_tkn(*tkns_head);
	merge_consecutive_less_or_greater_than(*tkns_head);
	merge_quoted_tokens(*tkns_head);
	merge_dollar_char_with_next_token(*tkns_head);
	assign_following_space_status(*tkns_head);
	delete_not_quoted_spaces(tkns_head);
	merge_strings(*tkns_head);
}
