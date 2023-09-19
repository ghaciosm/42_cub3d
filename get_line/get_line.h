/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghaciosm <ghaciosm@student.42kocaeli.com.  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:08:20 by ghaciosm          #+#    #+#             */
/*   Updated: 2022/02/20 12:23:59 by ghaciosm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_H
# define GET_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

char	*get_next_line(int fd);
int		nl_checker(char *str);
char	*ft_strjoin_v2(char *s1, char *s2);
char	*till_next_line(char	*holder);
char	*after_next_line(char *holder);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
#endif
