/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpastukh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 16:11:10 by kpastukh          #+#    #+#             */
/*   Updated: 2019/07/31 20:27:38 by kpastukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bsq.h"

int		g_strt;
int		g_rows;
char	g_spce;
char	g_obst;
char	g_sqre;
int		g_size;
int		g_posn;

void	get_config(char *input)
{
	int i;
	int j;
	char *rows;

	i = 0;
	j = 0;
	while (input[i] != '\n')
		i++;
	g_strt = i + 1;
	g_sqre = input[i - 1];
	g_obst = input[i - 2];
	g_spce = input[i - 3];
	i = i - 4;	
	rows = malloc(i + 1);
	while (j <= i)
	{
		rows[j] = input[j];
		j++;
	}
	rows[j] = '\0';
	g_rows = ft_atoi(rows);
	free(rows);
}

int		main(int argc, char **argv)
{
	char *test_str = ft_read_file(argv[1]);
	get_config(test_str);
	int test[ft_strlen(test_str) - g_strt - g_rows];

	printf("strlen: %d\n", ft_strlen(test_str));
	printf("strlen - config: %d\n", ft_strlen(test_str) - g_strt);
	printf("map_start: %d | space: %c | obstacle: %c | square: %c\n", g_strt, g_spce, g_obst, g_sqre);
	int i = 0;
	int j = 0;
	int k = 0;
	int start = g_strt;
	int rows = g_rows;
	int	cols = (ft_strlen(test_str) - g_strt - g_rows) / rows;
	printf("rows: %d | cols: %d\n", rows, cols);
	int diag;
	int abov;
	int left;
	g_size = 0;
	g_posn = 0;
	int col_counter;
	int row_counter;

	ft_putstr(test_str, 1);
	write(1, "\n", 1);

	i = 0;
	j = 0;
	start = g_strt;
	while (test_str[start])
	{
		ft_zero_vars3(&abov, &diag, &left);
		/* diag = 0; */
		/* abov = 0; */
		/* left = 0; */
		if (test_str[start] == '\n')
			start++;
		if (j != 0)
			abov = test[i - cols];
		if (!((i / (j + 1) % cols) == 0))
			left = test[i - 1];
		if (!((i / (j + 1) % cols) == 0) && j != 0)
			diag = test[i - cols - 1];
		if (test_str[start] == 'o')
			test[i] = 0;
		else
		{
			test[i] = MIN3(left, abov, diag) + 1;
			/* printf("test[i]: %d\n", test[i]); */
			if (test[i] > g_size)
			{
				g_size = test[i];
				g_posn = start;
			}
		}
		if ((i / (j + 1) % cols) == 0 && i != 0)
			j++;
		i++;
		start++;
		/* printf("g_size: %d | g_posn: %d\n", g_size, g_posn); */
	}

	/* i = 0; */
	/* j = 0; */
	/* k = 0; */
	/* while (i < rows) */
	/* { */
	/* 	j = 0; */
	/* 	while (j < cols) */
	/* 	{ */
	/* 		printf("%d", test[k++]); */
	/* 		j++; */
	/* 	} */
	/* 	printf("\n"); */
	/* 	i++; */
	/* } */

	col_counter = g_size;
	row_counter = g_size;
	printf("g_posn: %d, g_size: %d\n", g_posn, g_size);
	ft_fill_spaces(test_str, g_size, g_size, cols);
	ft_putstr(test_str, 1);
	write(1, "\n", 1);
	return (0);
}


void	ft_fill_spaces(char *str, int col_counter, int row_counter, int cols)
{
	while (row_counter > 0)
	{
		while (col_counter > 0)
		{
			str[g_posn] = 'x';
			g_posn--;
			col_counter--;
		}
		col_counter = g_size;
		row_counter--;
		g_posn = (g_posn + g_size - 1) - cols;
	}
}


