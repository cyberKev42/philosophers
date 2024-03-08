/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrauer <kbrauer@student.42vienna.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 17:46:08 by kbrauer           #+#    #+#             */
/*   Updated: 2024/02/23 17:04:03 by kbrauer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_arg(int argc, char **argv)
{
	int	i;
	int	k;

	i = 1;
	k = 0;
	while (i < argc)
	{
		if (check_length(argv[i]) > 10)
			return (-2);
		while ((argv[i][k] >= 9 && argv[i][k] <= 13) || argv[i][k] == 32)
			k++;
		while (argv[i][k] == 43 || argv[i][k] == 45)
			k++;
		while (argv[i][k] >= '0' && argv[i][k] <= '9')
			k++;
		if (argv[i][k] == '\0')
			i++;
		else
			return (-1);
		k = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	data;

	if (argc != 5 && argc != 6)
		return (printf(ERROR_ARG1), 1);
	if (check_arg(argc, argv) == -1)
		return (printf(ERROR_ARG2), 1);
	else if (check_arg(argc, argv) == -2)
		return (printf(ERROR_ARG4), 1);
	if (init_data(&data, argv))
		return (1);
	if (create_table(&data))
		return (1);
	simulation(&data);
	free_all(&data);
	return (0);
}
