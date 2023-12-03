/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   day3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 11:12:54 by ulysse            #+#    #+#             */
/*   Updated: 2023/12/03 21:45:08 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// faire un tableau en 2 dimension

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct s_coor
{
	int x;
	int y;
}	t_coor;

char *gnl(int fd)
{
	char c;
	int i = 0;
	int rd= 0;
	
	if (fd < 0 )
		return(NULL);
	char *buf = malloc(100000);
	while ((rd = read(fd, &c, 1)) > 0)
	{
		if (!rd)
			return (free(buf), NULL);
		buf[i] = c;
		i++;
		if (c == '\n')
			break;
	}
	if (rd == -1 || (!rd && !buf[i - 1]))
		return (free(buf), NULL);
	buf[i] == '\0';
	return (buf);
}



void	find_number(int x, int y, char **tab)
{	
	if (x > 1 || x < 0 || y < 0 || y > 141)
		return;
	if (tab[x][y] != '.')
	{
		write(1, &tab[x][y], 1);
		tab[x][y] = '.';
		find_number(x + 1, y, tab);
		find_number(x + 1, y + 1, tab);
		find_number(x + 1, y - 1, tab);
		find_number(x - 1, y, tab);
		find_number(x - 1, y + 1, tab);
		find_number(x - 1, y - 1, tab);
		find_number(x, y + 1, tab);
		find_number(x, y - 1, tab);
	}
}

void find_sign(char **tab)
{
	int i = 0;
	int j = 0;

	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] != '.' && tab[i][j] != '\n' && (tab[i][j] < '0' || tab[i][j] > '9' ))
			{
				find_number(i, j, tab);
			}
			j++;
		}
		i++;
	}
}
void	create_tab(void)
{
	char 	**tab;
	int fd;
	int i = 0;
	
	fd = open("puzzle", O_RDONLY);
	tab = malloc(sizeof(char * ) * 141);
	while (1)
	{
		tab[i] = gnl(fd);
		if (tab[i] == NULL)
			break;	
		i++;	
	}
	find_sign(tab);
}
int main()
{
	create_tab();
}