#include <stdlib.h>
#include <stdio.h>
#include "include/kernel.h"

int receive_word_num(int *num_word)
{
	int *num_p;
	int i = 0;
	for (num_p = num_word ; *num_p != '\0'; num_p++){
//		printf("runing... num:%d\n",*num_p);
		*num_p = switch_opposite_word_num(num_p);
	}
}

int switch_opposite_word_num(int *num_word)
{
	switch (*num_word) {				/* if you want to add a num_word plase use this style */
		case 1:				/* opposite word "My Name" */
			num_word++;
			if (*num_word == '\0') {	/* For Example: You say : Bob '\0' */
				printf("What?\n");
				return 10;		/* The rebot should say : what? */
				break;
			}
			num_word--;
			printf("Yes,I can\n");
			return 1;	/* should return a action word of number */
			break;
		case 2:
			printf("Sorry I don't know this word\n");
			return 0;	/* opposite word "You" */	
			break;
		case 3:
			printf("Sorry I don't know this word\n");
			return 0;	/* opposite word "he or she" */	
			break;
		case 4:
			printf("Sorry I don't know this word\n");
			return 0;	/* opposite word "" */	
			break;
		default:
			return 0;	/* number 0 means don't know this word */
			printf("Sorry I don't know this number\n");
			break;
	}
}

