/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree_construction.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 07:25:54 by ncasteln          #+#    #+#             */
/*   Updated: 2023/11/21 10:29:28 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree_construction(char *prev_tkn, char *curr_tkn, char *next_tkn)
{
	if (prev_tkn)
		ft_printf("\x1b[32mprev[%s] <-- ", prev_tkn);
	else
		ft_printf("\x1b[32mprev(null) <-- ");
	ft_printf("curr[%s]", curr_tkn);
	if (next_tkn)
		ft_printf(" --> next[%s]\x1b[0m", next_tkn);
	else
		ft_printf(" --> next(null)\x1b[0m");
	ft_printf("\n\n");
}
