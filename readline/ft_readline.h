/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:55:33 by yabakhar          #+#    #+#             */
/*   Updated: 2020/01/24 17:18:34 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H

# define FT_READLINE_H
# include <term.h>
# include <termios.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include <sys/ioctl.h>

# define BUTTON_ESC 27
# define BUTTON_SELECT 40899
# define BUTTON_COPY 42947
# define BUTTON_CUT 8948194
# define BUTTON_PAST 10127586
# define BUTTON_PUP 2117425947
# define BUTTON_PDOWN 2117491483
# define BUTTON_UP 4283163
# define BUTTON_DOWN 4348699
# define BUTTON_RIGHT 4414235
# define BUTTON_ALT_RIGHT 26139
# define BUTTON_LEFT 4479771
# define BUTTON_ALT_LEFT 25115
# define BUTTON_SPACE 32
# define BUTTON_ENTER 10
# define BUTTON_DEL 127
# define BUTTON_DEL2 2117294875
# define BUTTON_END 4610843
# define BUTTON_HOME 4741915
# define BUTTON_R 114
# define BUTTON_CTL_D 4
# define BUTTON_CTL_L 12

typedef struct	s_point
{
	int x;
	int y;
}				t_point;

typedef struct	s_cmd_history
{
	char					*tmp_line;
	char					*line;
	struct s_cmd_history	*next;
	struct s_cmd_history	*prev;
	int						len;
	int						tmp_len;
}				t_cmd_history;

typedef struct	s_line
{
	int			*details;
	int			index;
	int			linecount;
}				t_line;

typedef struct	s_readline
{
	const char		*g_prompt;
	char			*to_past;
	t_cmd_history	*cmd;
	struct termios	config;
	t_line			line_props;
	t_point			o_cursor;
	t_point			ov_cursor;
	int				cursor;
	int				line_index;
	int				col;
	int				row;
	void			(*c_handler)(int);
}				t_readline;

/*
**	Cursor Events & Operations
*/
void			cur_up(t_readline *readline);
void			cur_down(t_readline *readline);
void			cur_right(t_readline *readline);
void			cur_left(t_readline *readline);
void			cur_move_by_word(t_readline *readline, int button);
void			to_start_or_end(t_readline *readline, int button);

/*
**	Cursor Helper Functions
*/
void			set_virtual_origin(t_readline *readline);
void			get_cursor_position(t_readline *readline);
void			set_cursor_from_index(t_readline *readline);
void			set_idnex_from_cursor(t_readline *readline);
void			cur_goto(t_readline *readline, int cursor);
int				get_virtua_line_count(t_readline *readline);
void			update_o_cursor(t_readline *readline);

/*
**	Events
*/
void			history_previous(t_readline *readline);
void			history_next(t_readline *readline);

/*
**	Helpers
*/
int				manage_ctlr_d(t_readline *readline);
char			*manage_ctlr_c(t_readline *readline);
void			clear_buffer(t_readline *readline);
void			configure_terminal(t_readline *readline);
void			unconfigure_terminal(t_readline *readline);
char			*remove_unprintable_chars(char *str);
int				output(int str);

/*
**	Line Operations
*/
void			insert_in_line(t_readline *readline, char *str);
void			remove_from_line(t_readline *readline, int start, int end);
void			rewrite_line(t_readline *readline);
int				*get_line_details(t_readline *readline);

/*
**	CMD History
*/
void			clean_hsitory(void);
void			add_to_history(const char *str, int len);
void			free_history(void);
void			set_cur_history(t_readline *readline, t_cmd_history *cur);
t_cmd_history	*get_cmd_history_head(void);

void			set_signal(void);
void			signal_c(int sig);
void			signal_resize(int sig);
void			sig_dispatch(int a);
void			selection(t_readline *readline);
char			*ft_readline(const char *g_prompt);
char			*end_readline(t_readline *readline, char *ret);

int				g_read_interrput;
t_readline		*g_readline;

#endif
