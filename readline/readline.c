/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 00:57:15 by aait-ihi          #+#    #+#             */
/*   Updated: 2020/01/24 17:18:34 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include <readline/readline.h>

static int		key_handel(t_readline *env, int b, int r)
{
	if (b == BUTTON_UP && !(r = 0))
		set_cur_history(env, env->cmd->next);
	else if (b == BUTTON_DOWN && !(r = 0))
		set_cur_history(env, env->cmd->prev);
	else if (b == BUTTON_RIGHT && !(r = 0))
		cur_right(env);
	else if (b == BUTTON_LEFT && !(r = 0))
		cur_left(env);
	else if (b == BUTTON_PUP && !(r = 0))
		cur_up(env);
	else if (b == BUTTON_PDOWN && !(r = 0))
		cur_down(env);
	else if ((b == BUTTON_HOME || b == BUTTON_END) && !(r = 0))
		to_start_or_end(env, b);
	else if ((b == BUTTON_ALT_RIGHT || b == BUTTON_ALT_LEFT) && !(r = 0))
		cur_move_by_word(env, b);
	else if ((b == BUTTON_DEL || b == BUTTON_DEL2) && !(r = 0))
		remove_from_line(env, env->line_index - 1, env->line_index - 1);
	else if (b == BUTTON_ENTER && !(r = 0))
		ft_memdel((void **)&env->line_props.details);
	else if (b == BUTTON_SELECT && !(r = 0))
		selection(env);
	else if (b == BUTTON_PAST && !(r = 0))
		insert_in_line(env, remove_unprintable_chars(env->to_past));
	return (r);
}

static void		readline_init(t_readline *readline, const char *g_prompt)
{
	g_readline = readline;
	ft_bzero(readline, sizeof(t_readline));
	readline->g_prompt = g_prompt;
	configure_terminal(readline);
	signal_resize(0);
	signal(SIGWINCH, signal_resize);
	readline->c_handler = signal(SIGINT, signal_c);
	get_cursor_position(readline);
	add_to_history("", 0);
	readline->cmd = get_cmd_history_head();
	readline->line_props.linecount = 1;
	readline->line_props.details = ft_memalloc(sizeof(int));
}

char			*end_readline(t_readline *readline, char *ret)
{
	const t_point	cursor = readline->o_cursor;

	tputs(tgoto(tgetstr("cm", 0), cursor.x, cursor.y), 0, output);
	if (readline->cmd && readline->cmd->tmp_line)
	{
		ft_putendl(readline->cmd->tmp_line);
		if (ret == NULL)
		{
			ret = readline->cmd->tmp_line;
			readline->cmd->tmp_line = NULL;
		}
		else
			ft_memdel((void **)&readline->cmd->tmp_line);
	}
	free(readline->line_props.details);
	clean_hsitory();
	unconfigure_terminal(readline);
	signal(SIGINT, readline->c_handler);
	return (ret);
}

static int		everything_is_ok(t_readline *readline)
{
	int				ret;
	const t_line	line_props = readline->line_props;

	ret = 1;
	ret &= (readline->cmd && readline->cmd->tmp_line);
	ret &= (readline->line_props.details != NULL);
	if (ret)
	{
		if (!between(readline->line_index, 0, readline->cmd->tmp_len))
			readline->line_index = 0;
		if (!between(line_props.index, 0, line_props.linecount))
			readline->line_props.index = 0;
		if (!between(readline->cursor, 0, line_props.details[line_props.index]))
			readline->cursor = 0;
	}
	return (ret);
}

char			*ft_readline(const char *g_prompt)
{
	t_readline	readline;
	char		buff[2049];
	int			button;

	g_prompt = g_prompt ? g_prompt : "";
	ft_putstr(g_prompt);
	readline_init(&readline, g_prompt);
	while (everything_is_ok(&readline) && ft_memset(buff, 0, 2049))
		if (read(0, buff, 2048) > 0)
		{
			button = *((int *)buff);
			if (key_handel(&readline, button, 1))
			{
				if (button == BUTTON_CTL_L)
					clear_buffer(&readline);
				else if (button == BUTTON_CTL_D && manage_ctlr_d(&readline))
					return (ft_strdup("\4"));
				else
					insert_in_line(&readline, remove_unprintable_chars(buff));
			}
		}
		else
			return (manage_ctlr_c(&readline));
	return (end_readline(&readline, NULL));
}
