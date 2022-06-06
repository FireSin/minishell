/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:07:20 by bclarind          #+#    #+#             */
/*   Updated: 2022/06/06 20:27:41 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/stat.h>

# include "color.h"
# include "../libft/includes/libft.h"

typedef struct s_envr
{
	char			*key;
	char			*val;
	struct s_envr	*next;
}	t_envr;

typedef struct s_comm
{
	int				fd[2];
	int				i;
	pid_t			pid;
	pid_t			prnt;
	char			*comm;
	char			**args;
	char			*oper;
	struct s_data	*data;
	struct s_comm	*next;
	struct s_comm	*prev;
	int				status;
}	t_comm;

typedef struct s_data
{
	struct s_comm	*comm;
	struct s_envr	*env;
	struct s_envr	*vars;
	char			*instr;
}	t_data;

typedef struct s_finfo
{
	char	*start;
	char	*finish;
	char	**between;
}	t_finfo;

typedef struct s_box
{
	t_comm			*dt_comm;
	char			*oper;
	struct s_box	*next;
}	t_box;

/*!!!!DELETE!!!!!*/
void	tmp_print_env(t_envr *env);
void	tmp_print_arg_after_parser(t_comm *data);
void	print_containers(t_box *box);

/* general */
int		is_same_lines(char *f_str, char *s_str);
void	freedata(t_data *data);
void	free_arrs(char **arr);
int		ft_perror(t_comm *dt);
int		continue_with_print(char *err_str);
void	ft_fprintf(char *command, char *str);
int		print_error_and_errno(char *str, int error, int ret);
void	pars_and_launch(t_data *data, int i);

/* parser */
int		check_for_move_arg(t_box **box);
int		check_argv(int argc, char **argv, char **env, t_data *data);
char	*delete_hashtag(char *str);
void	error_mes_with_exit(char *err_mes, t_data *data);
void	take_start_env(t_data *data, char **envar);
void	write_start_env(char *envar, t_envr **temp);
int		ft_create_var(t_data *data, char *var);
int		parser(t_data *data, int i);
t_comm	*addelem(t_data *data, int i);
void	delcommand(t_comm **comm);
int		check_quote(char **s, char **str, char quote, t_comm *data);
int		write_arg(char **arg, char **s, int i);
int		take_arg_mass(char ***args, int a);
int		check_second_qoute(char *s, int i, char quote);
int		takevar(char **s, char **str, t_comm *data, int i);
int		operand(t_comm	*data, char **s, int *i, char **arg);
void	delenv(t_envr **env);
int		command_in_bin(char *command);
void	exit_from_minishell(void);
t_envr	*take_path_env(t_envr **env, char *s);
int		check_wildcard(t_comm *tmp);
int		write_pos_wild(int **pos, int i, int a);
int		varisdigit(char **s);
int		writevar(char **str, t_envr p);
int		last_error(char **s, char **str);
int		vars_quote_check(char **str, char **s, int i, t_comm *data);
int		checkallcommands(t_comm **p);
int		add_list_env(t_envr **env, char *arg);
int		check_for_local_vars(char **str, t_data *data);
int		check_right_var(char *arg);
int		check_prnts(char **str, char **s, int *i, t_comm *data);
void	init_index(t_comm *dt);
void	increment_shlvl(t_data *data);

/* launcher */
int		launcher(t_data *data);
int		init_var(t_comm **tmp_dt, t_data *dt, int *wait_c, int *count_comm);
int		get_count_comm(t_comm *data);
void	add_ptr_prev_to_data(t_comm *data);
int		close_fd(t_comm *data);
int		check_redirect(t_data *data);
int		is_correct_comm(char *comm);
int		handle_error_executor(int error);
int		create_pipe(t_comm *data);
void	set_next_ptr_data_and_free_path(t_data *data);
int		handle_oper(t_data *data, int count_comm);
int		heredoc(t_comm *data);
int		init_result(char **free_ptr, char **nl, char **line, char **res);
int		is_redirect(char *op);
int		duplicate_fd_for_heredoc(t_comm *data);
int		set_next_dt(t_data *data);
int		del_file_doc(t_comm *data);
int		duplicate_fd(t_comm *data, int idx, int count_comm);
int		redirect_out(t_comm *data);
int		redirect_in(t_comm *data);
int		initialize_dirs(char ***dirs, t_data *data, int *i);
int		check_oper(t_data *data);
int		check_tilda(t_comm **comm);
char	**get_env(t_envr *dt_env);
int		set_env(t_comm *data, t_data *dt);

/* builtins */
int		ft_export(t_data *data);
void	ft_unset(t_data *data);
int		ft_echo(t_comm com);
int		ft_pwd(void);
int		ft_env(t_envr *env);
int		ft_exit(t_data *data);
int		ft_cd(t_data *data);
int		ft_space(char str);
int		launch_builtins(t_data *data);
int		check_right_var(char *arg);
int		is_builtins(char *comm, t_data *dt);
int		is_builtins_in_main_proc(char *comm, t_data *dt);
int		check_builtins(t_data *data, char **path);

/* executor */
int		executor(t_data *data, char *path, int count_comm);
int		kill_childs(t_comm *data);
void	print_last_exit(void);
t_envr	*search_var(char *tmp, t_envr *p, t_envr *vars);
char	**get_env(t_envr *dt_env);
int		check_operator(t_comm *dt);
int		exec_heredoc(t_comm **data);
int		next_oper(char *oper);
int		curr_oper(char *oper);

/* wildcard */
char	**wildcard(char *template, int *arr);
int		check_start(t_finfo *dt, char *filename);
int		check_finish(t_finfo *dt, char *filename);
int		check_between(t_finfo *dt, char *filename);
int		free_dt(t_finfo *dt);
int		len(char **template);
int		initial_var(char ***split_template, \
		t_finfo *dt, char *template, int *arr_int);
int		init_dt_start(t_finfo *dt, char *str, char ***split_template);
int		init_dt_finish(t_finfo *dt, char *str, char ***temp, int last_idx_str);
int		init_dt_between(t_finfo *dt, char ***split_template, int *i);
int		check_parts(t_finfo *dt, char *filename);
int		in_arr(int *arr, int i);
int		wild_add_elem(char ***arr, char *file, int i);
char	**split_wild(char *str, int *arr);
void	fill_zero(int *arr, int k, int *j, char **res);
int		take_pos_for_wild(char **str, int **pos);
int		write_arg_wild(char ***args, char **wild, int a);

/* bonus func */
int		is_logic_oper(char *str);
int		init_containers(t_comm *data, t_box	**box);
void	set_next_box(t_box **box);
int		freebox(t_box **box);
int		check_parenthesis(int c, t_data *data, t_comm *tmp_dt);

#endif
