/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:58:36 by ancolmen          #+#    #+#             */
/*   Updated: 2023/05/19 16:19:41 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	ppx;

	ft_bzero(&ppx, sizeof(t_data));
	if (argc >= 5)
	{
		ppx.n_cmds = argc - 3;
		ppx.argc = argc - 1;
		if (!ft_strcmp(argv[1], "here_doc"))
		{	
			ppx.n_cmds = argc - 4;
			ppx.hd = 1;
			ppx.key_word = argv[2];
		}
		if (ppx.n_cmds <= 1)
			free_and_exit(&ppx, NULL, 22);
		stock_path(&ppx, envp);
		stock_cmd(&ppx, argv, argc);
		create_pipes(&ppx);
		start_pipex(&ppx, argv, envp);
	}
	else
		free_and_exit(&ppx, NULL, 22);
	free_structure(&ppx);
	return (EXIT_SUCCESS);
}
