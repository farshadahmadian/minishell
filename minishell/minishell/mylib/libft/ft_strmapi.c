/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 18:02:27 by fahmadia          #+#    #+#             */
/*   Updated: 2023/12/10 18:34:11 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_length;
	size_t	i;
	char	*p;

	s_length = ft_strlen(s);
	i = 0;
	p = (char *)malloc((s_length + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (i < s_length)
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
