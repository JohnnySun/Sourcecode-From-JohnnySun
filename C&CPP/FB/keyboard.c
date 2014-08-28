#include "include/keyboard/variable.h"
#include "include/keyboard/function.h"
#include "include/keyboard/keyboard.h"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

struct termios * termios_init(struct termios * init_term)
{
	struct termios * term = init_term;
	term->c_lflag &= ~ICANON;
	term->c_lflag &= ~ECHO;
	term->c_lflag &= ~ISIG;
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	
	return term;
}

struct termios * init_keyboard(struct termios * init_term, struct termios * new_term)
{
	struct termios * iterm = init_term;
	struct termios * nterm = new_term;
	tcgetattr(STDIN_FILENO, iterm);
	nterm = termios_init(iterm);
	tcsetattr(STDIN_FILENO, TCSANOW, nterm);

	return nterm;
}

int kbhit(struct termios * new_term)
{
	char ch;
	int nread;
	struct termios * nterm = new_term;
	if (peek_ch != -1)
		return 1;
	nterm->c_cc[VMIN] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, nterm);
	nread = read(STDIN_FILENO, &ch, 1);
	nterm->c_cc[VMIN] = 1;
	tcsetattr(STDIN_FILENO, TCSANOW, nterm);
	if (nread == 1){
		peek_ch = (int)ch;
		return 1;
	} 
	return 0;
}

int readch()
{
	char ch;
	if(peek_ch != -1){
		ch = peek_ch;
		peek_ch = -1;
		return (int)ch;
	}
	read(STDIN_FILENO, &ch, 1);
	return (int)ch;
}

void get_way()
{
	int ch;
	ch = readch();
	ch = readch();
	switch(ch)
	{
		case 65:
			printf("UP\n");
			break;
		case 66:
			printf("DOWN\n");
			break;
		case 67:
			printf("RIGHT\n");
			break;
		case 68:
			printf("LEFT\n");
			break;
		default:
			printf("Unknow\n");
	}
}

void check_ch(int ch)
{
	printf("you hit %c %d\n", (char)ch, ch);
}

void switch_key(struct termios * new_term)
{
	int ch = 0;
	struct termios * nterm = new_term;
	while(1)
	{
		if(kbhit(nterm))
		{
			ch = readch();
			switch(ch)
			{
				case 27:
					get_way();
					break;
				case 10:
					printf("enter the menu\n");
					break;
				default:
					check_ch(ch);
				break;
			}
		}
	}
}

void close_keyboard(struct termios * init_term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, init_term);
}






