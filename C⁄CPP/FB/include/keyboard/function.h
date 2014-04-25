#ifndef __KB__FUNCTION__H__
#define __KB__FUNCTION__H__ 1

struct termios * termios_init(struct termios *);
struct termios * init_keyboard(struct termios *, struct termios *);
void switch_key(struct termios *);
int kbhit(struct termios *);
int readch();
void get_lrud();
void check_ch(int);
void close_keyboard(struct termios *);


















#endif
