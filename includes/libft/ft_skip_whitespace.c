/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_whitespaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:00:39 by marvin            #+#    #+#             */
/*   Updated: 2024/05/22 12:00:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_skip_whitespace(char **line)
{
	if (**line == '\0')
		return ;
	while (ft_strchr(WHITESPACE, **line))
		(*line)++;
}
