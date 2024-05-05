/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:54:11 by fahmadia          #+#    #+#             */
/*   Updated: 2023/10/30 09:58:14 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_input(char *input, t_list **tkn_head)
{
	int		input_counter;
	int		tkn_counter;
	char	*ref;

	ref = input;
	input_counter = 0;
	tkn_counter = 1;
	while (input[input_counter])
	{
		read_char(input[input_counter], &ref, &tkn_counter, tkn_head);
		input_counter++;
		tkn_counter++;
	}
	store_prev_chars_as_tkn(ref, tkn_counter, tkn_head);
	if (*ref != '\0')
		ref += tkn_counter;
	tkn_counter = 0;
}
