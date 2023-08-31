/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancolmen <ancolmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:58:16 by ancolmen          #+#    #+#             */
/*   Updated: 2023/05/22 16:20:13 by ancolmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_lst
{
	void			*arg;
	char			**cmd_op;
	char			*path;
	struct s_lst	*next;
}		t_lst;

typedef struct s_data
{
	int		pipe[1024][2];
	int		pids[1024];
	int		hd_fd[2];
	int		argc;
	int		n_cmds;
	int		i_fd;
	int		o_fd;
	char	**path;
	t_lst	*cmd;
	t_list	*here;
	char	*key_word;
	int		hd;
	int		child;
	int		wstatus;
}		t_data;

/*CHECK AND STOCK*/
void	stock_path(t_data *ppx, char **envp);
void	stock_cmd(t_data *ppx, char **argv, int argc);
void	add_to_lst(t_data *ppx, char *str);
void	add_to_list_hd(t_data *ppx, char *str);
void	get_exec_path(t_data *ppx);

/*START*/
void	start_pipex(t_data *ppx, char **argv, char **envp);
void	first_process(t_data *ppx, char **argv, t_lst *iter, char **envp);
void	last_process(t_data *ppx, char **argv, t_lst *iter, char **envp);
void	middle_process(t_data *ppx, int i, t_lst *iter, char **envp);
void	here_doc(t_data *ppx);

/*UTILS*/
void	create_pipes(t_data *ppx);
void	close_all_pipes(t_data *ppx);
void	wait_for_all(t_data *ppx);
void	print_hd(t_data *ppx);
void	print_list_hd(t_data *ppx);

/*EXIT*/
void	free_and_exit(t_data *ppx, char *str, int error);
void	free_structure(t_data *ppx);
void	error_handling(t_data *ppx, char *str, int error);
void	ft_lstclear_ppx(t_lst *lst);
void	ft_lstfree(t_list *lst);

#endif
