/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghaciosm <ghaciosm@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:29:36 by ghaciosm          #+#    #+#             */
/*   Updated: 2022/02/20 12:22:01 by ghaciosm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_line.h"

char	*read_line(int fd, char *holder)
{
	char	*buffer;
	int		amount;

	amount = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (nl_checker(holder) && amount)
	{
		amount = read(fd, buffer, BUFFER_SIZE);
		if (amount == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[amount] = '\0';
		holder = ft_strjoin_v2(holder, buffer);
	}
	free (buffer);
	return (holder);
}

char	*get_next_line(int fd)
{
	static char	*holder;
	char		*result;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	holder = read_line(fd, holder);
	if (!holder)
		return (NULL);
	result = till_next_line(holder);
	holder = after_next_line(holder);
	return (result);
}
/*
int main()
{

    int fd = open(FILE_NAME, O_RDONLY);
    char    **str;
    char    *line;
    int 	line_count, i = 0;
    
    line_count = 0;
	line = get_next_line(fd);
    while(line)
    {
		free(line);
        line_count++;
        line = get_next_line(fd);
    }
	close(fd);
    fd = open("src", O_RDONLY);
	str = (char **)malloc(sizeof(char *) * (line_count + 1));
    while(i < line_count)
    {
        str[i] = get_next_line(fd);
		i++;
    }
	str[i] = NULL;
	
}*/
