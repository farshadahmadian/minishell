/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_each_token_string.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:07:54 by fahmadia          #+#    #+#             */
/*   Updated: 2023/11/06 09:28:12 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_each_tkn_str(t_tkn_data *tkn_data)
{
	char	tkn_first_char;

	tkn_first_char = *(tkn_data->str);
	if (tkn_first_char == TKN_REDIR_IN)
		tkn_data->type = TKN_REDIR_IN;
	else if (tkn_first_char == TKN_REDIR_OUT)
		tkn_data->type = TKN_REDIR_OUT;
	else if (tkn_first_char == TKN_SPACE_CAHR)
		tkn_data->type = TKN_SPACE_CAHR;
	else if (tkn_first_char == TKN_TAB_CHAR)
		tkn_data->type = TKN_TAB_CHAR;
	else if (tkn_first_char == TKN_NEW_LINE)
		tkn_data->type = TKN_NEW_LINE;
	else if (tkn_first_char == TKN_S_QUOTE)
		tkn_data->type = TKN_S_QUOTE;
	else if (tkn_first_char == TKN_D_QUOTE)
		tkn_data->type = TKN_D_QUOTE;
	else if (tkn_first_char == TKN_ESCAPE_CHAR)
		tkn_data->type = TKN_ESCAPE_CHAR;
	else if (tkn_first_char == TKN_PIPE)
		tkn_data->type = TKN_PIPE;
	else if (tkn_first_char == TKN_DOLLAR_CHAR)
		tkn_data->type = TKN_DOLLAR_CHAR;
	else
		tkn_data->type = TKN_WORD;
}
