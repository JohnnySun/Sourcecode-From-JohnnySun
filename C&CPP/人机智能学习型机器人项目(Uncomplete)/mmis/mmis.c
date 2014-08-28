#include <stdio.h>
#include <stdlib.h>

#include "include/kernel.h"
#include "include/mmis.h"

int get_sentence()
{
//	char sentence[1000];
//	scanf("%s",&sentence);
	int sentence[10] = {0}, i , num;
	for (i = 0 ; i<9 ; i++) {
	scanf("%d",&num);
	sentence[i] = num;
	}
	sentence_buffer(sentence);
	return 0;
}

int sentence_buffer(int buf1[])
{
	int *send;
	send = buf1;
	receive_word_num(send);
	return 0;
}


