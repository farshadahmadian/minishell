/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:30:52 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/13 11:31:04 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	find_min_len(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 < len2)
		return (len1);
	else
		return (len2);
}

void	swap(char **str1, char **str2)
{
	char		*temp;

	temp = *str2;
	*str2 = *str1;
	*str1 = temp;
}
