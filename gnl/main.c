/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadawson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:43:03 by jadawson          #+#    #+#             */
/*   Updated: 2018/04/20 21:50:17 by jadawson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	char	*str;
	int		fd;
	int		result;

	if ((fd = open("one.txt", O_RDONLY)) < 0)
		return (0);
	while ((result = get_next_line(fd, &str)) != 0) //checking for each line.
	{
		printf("%s\n[endofline]\n", str);
		//free(str);
	}
	close(fd);
	return (0);
}
