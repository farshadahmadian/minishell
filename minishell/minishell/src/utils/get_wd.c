/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:34:22 by ncasteln          #+#    #+#             */
/*   Updated: 2023/12/09 13:58:40 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_wd(void)
{
	char	*buff;
	size_t	size;

	buff = NULL;
	size = 1;
	buff = getcwd(buff, size);
	while (!buff && errno == ERANGE)
	{
		size += 1;
		buff = getcwd(buff, size);
		if (!buff && errno != ERANGE)
			return (error("pwd", NULL, errno), NULL);
	}
	return (buff);
}
