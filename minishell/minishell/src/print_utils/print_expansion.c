/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:14:18 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 15:48:06 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_expansion(t_list *var_lst)
{
	t_var	*var;

	while (var_lst)
	{
		if (var_lst->content)
		{
			var = (t_var *)var_lst->content;
			ft_printf("name [%s]", var->name);
			ft_printf("[%d] - ", var->name_len);
			ft_printf("value [%s]", var->value);
			ft_printf("[%d]\n", var->value_len);
		}
		var_lst = var_lst->next;
	}
	ft_printf("________\n\n");
}
