/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:09:32 by fahmadia          #+#    #+#             */
/*   Updated: 2023/12/10 18:04:35 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_d_quote(t_tkn_data *tkn_data, bool *is_d_q_open, t_quote *quote)
{
	*is_d_q_open = true;
	*quote = IN_D_QUOTE;
	tkn_data->quote_status = OPEN_QUOTE;
}

void	close_d_quote(t_tkn_data *tkn_data, bool *is_d_q_open, t_quote *quote)
{
	*is_d_q_open = false;
	*quote = NOT_QUOTED;
	tkn_data->quote_status = CLOSED_QUOTE;
}

void	open_s_quote(t_tkn_data *tkn_data, bool *is_s_q_open, t_quote *quote)
{
	*is_s_q_open = true;
	*quote = IN_S_QUOTE;
	tkn_data->quote_status = OPEN_QUOTE;
}

void	close_s_quote(t_tkn_data *tkn_data, bool *is_s_q_open, t_quote *quote)
{
	*is_s_q_open = false;
	*quote = NOT_QUOTED;
	tkn_data->quote_status = CLOSED_QUOTE;
}

t_quote_open	*detect_quote(t_tkn_data *tkn_data, char tkn_first_char,
	t_quote *quote)
{
	static t_quote_open	quote_open;

	if (tkn_first_char == TKN_D_QUOTE && !quote_open.is_d_quote_open
		&& !quote_open.is_s_quote_open)
		open_d_quote(tkn_data, &quote_open.is_d_quote_open, quote);
	else if (tkn_first_char == TKN_D_QUOTE && quote_open.is_d_quote_open
		&& *quote == IN_D_QUOTE)
		close_d_quote(tkn_data, &quote_open.is_d_quote_open, quote);
	else if (tkn_first_char == TKN_S_QUOTE && !quote_open.is_s_quote_open
		&& !quote_open.is_d_quote_open)
		open_s_quote(tkn_data, &quote_open.is_s_quote_open, quote);
	else if (tkn_first_char == TKN_S_QUOTE && quote_open.is_s_quote_open
		&& *quote == IN_S_QUOTE)
		close_s_quote(tkn_data, &quote_open.is_s_quote_open, quote);
	return (&quote_open);
}
