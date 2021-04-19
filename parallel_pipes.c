#include  "includes/minishell.h"



// возвращает не ноль, если команда последняя и это exit;
// очистка 
// зачем проверка на пустую команду?
// 


void
	pipes(t_list *pipe_lst, t_fdstruct *fds, t_list *envlst)
{
	t_bool	l_cmd;
	t_cmd *cmd;
	init_fd(&fds);

	while (pipe_lst)
	{
		cmd = pipe_lst->content;
		l_cmd = (!pipe_lst) ? TRUE : FALSE;

	}
}
