
#include <fcntl.h>
#include <termios.h>
#include <stdlib.h> 
//Объявление двух переменных для хранения управляющих структур
int main()
{
	struct termios savetty;
	struct termios tty;
	char c;
//Перевод драйвера клавиатуры в неканонический режим ввода


	tcgetattr (0, &tty);
	savetty = tty; /* Сохранить упр. информацию канонического режима */
	tty.c_lflag &= ~(ICANON|ECHO|ISIG);
	//tty.c_cc[VMIN] = 1;
	tcsetattr (0, TCSAFLUSH, &tty);
	read(0, &c, 1);

	tcsetattr (0, TCSAFLUSH, &savetty);
}