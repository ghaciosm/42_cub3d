/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghaciosm <ghaciosm@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:38:18 by ghaciosm          #+#    #+#             */
/*   Updated: 2022/02/20 13:11:03 by ghaciosm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>
#include "../libft/libft.h"

int	nl_checker(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*till_next_line(char	*holder)
{
	size_t	i;
	char	*result;

	if (*holder == 0)
		return (NULL);
	i = 0;
	while (holder[i] && holder[i] != '\n')
		i++;
	result = malloc(sizeof(char) * i + 2);
	if (!result)
		return (NULL);
	i = 0;
	while (holder[i] && holder[i] != '\n')
	{
		result[i] = holder[i];
		i++;
	}
	if (holder[i] == '\n')
		result[i++] = '\n';
	result[i] = '\0';
	return (result);
}

char	*after_next_line(char *holder)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = 0;
	while (holder[i] && holder[i] != '\n')
		i++;
	if (!holder[i])
	{
		free (holder);
		return (NULL);
	}
	result = malloc(sizeof(char) * (ft_strlen(holder) - i + 1));
	i++;
	if (!result)
		return (NULL);
	j = 0;
	while (holder[i])
		result[j++] = holder[i++];
	free(holder);
	result[j] = '\0';
	return (result);
}

char	*ft_strjoin_v2(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	char		*result;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s2)
		return (0);
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (0);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	free(s1);
	result[i] = '\0';
	return (result);
}
