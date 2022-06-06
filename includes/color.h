/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclarind <bclarind@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 16:07:12 by bclarind          #+#    #+#             */
/*   Updated: 2022/05/31 16:07:13 by bclarind         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# define TERM_BLACK			"\033[1;90m"
# define TERM_RED			"\033[1;91m"
# define TERM_GREEN			"\033[1;92m"
# define TERM_YELLOW		"\033[1;93m"
# define TERM_BLUE			"\033[1;94m"
# define TERM_PURPLE		"\033[1;95m"
# define TERM_CYAN			"\033[1;96m"
# define TERM_WHITE			"\033[1;97m"
# define TERM_RESET			"\033[0m"

# define READLINE_BLACK		"\001\033[1;90m\002"
# define READLINE_RED		"\001\033[1;91m\002"
# define READLINE_GREEN		"\001\033[1;92m\002"
# define READLINE_YELLOW	"\001\033[1;93m\002"
# define READLINE_BLUE		"\001\033[1;94m\002"
# define READLINE_PURPLE	"\001\033[1;95m\002"
# define READLINE_CYAN		"\001\033[1;96m\002"
# define READLINE_WHITE		"\001\033[1;97m\002"
# define READLINE_RESET		"\001\033[0m\002"

# define OK					TERM_GREEN
# define WARNING			TERM_YELLOW
# define ERROR				TERM_RED
# define RESET				TERM_RESET

# define PIPE_ERR			-1
# define FORK_ERR			-2
# define DUP_ERR			-3
# define CLOSE_ERR			-4
# define EXEC_ERR			-5
# define MALLOC_ERR			-6
# define OPEN_ERR			-7
# define KILL_ERR			-8

# define BUILTIN_ECHO		1
# define BUILTIN_CD 		2
# define BUILTIN_PWD		3
# define BUILTIN_EXPORT		4
# define BUILTIN_UNSET		5
# define BUILTIN_ENV		6
# define BUILTIN_EXIT		7

#endif