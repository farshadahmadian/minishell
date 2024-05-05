/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_var_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:30:03 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/07 13:50:47 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var_content(void *content)
{
	t_var	*var;

	var = (t_var *)content;
	if (var)
	{
		if (var->name)
		{
			free(var->name);
			var->name = NULL;
		}
		if (var->value)
		{
			free(var->value);
			var->value = NULL;
		}
		var->name_len = -1;
		var->value_len = -1;
		free(var);
		var = NULL;
	}
}
