/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:04:07 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/12 09:06:53 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Given the token list, the parser check first for syntax errors. In case of
	syntax error data->e_code is set to 2. The syntax tree is built only if
	there is no syntax error.
*/
void	parser(t_data *data)
{
	if (!data->tokens)
		return ;
	if (check_for_syntax_err(data->tokens, 0))
	{
		data->e_code = 258;
		return ;
	}
	data->tree = build_syntax_tree(data->tokens, 0);
	if (!data->tree)
	{
		data->e_code = 1;
		error("parser", NULL, CE_SYNTAX_TREE);
	}
}
