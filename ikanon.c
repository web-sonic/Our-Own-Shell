/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ikanon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:13:55 by sgath             #+#    #+#             */
/*   Updated: 2021/03/16 16:19:49 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <signal.h>
#include <string.h>
/* переменная для сохранения исходных атрибутов терминала */
struct termios saved_attributes;
void reset_input_mode(void)
{
	tcsetattr(0, TCSANOW, &saved_attributes);
}
	
void sighnd(int signo)
{
	exit(0);
}
	
void set_input_mode(void)
{
	struct termios tattr;
	/* проверяем, что вводим с терминала */
	if (!isatty(0)) {
		fprintf(stderr, "Not a terminal.\n");
		exit(1);
	}
	/* считываем текущий режим работы терминала */
	tcgetattr(0, &saved_attributes);
	memcpy(&tattr, &saved_attributes, sizeof(tattr));
	/* включаем неканонический режим без эха */
	tattr.c_lflag &= ~(ICANON|ECHO);
	/* считываем минимум по одному символу */
	tattr.c_cc[VMIN] = 1;
	/* без ограничения времени ожидания */
	tattr.c_cc[VTIME] = 0;
	/* устанавливаем новый режим работы терминала */
	tcsetattr(0, TCSAFLUSH, &tattr);
}

int main(void)
{
	char c;
	set_input_mode();
	atexit(reset_input_mode);
	/* устанавливаем обработку сигналов завершения */
	signal(SIGINT, sighnd);
	signal(SIGTERM, sighnd);
	while (1) {
		read(0, &c, 1);
		if (c == 4) break;
			write(1, &c, 1);
	}
	return 0;
}