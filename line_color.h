#include <iostream>


void Color_Change(int a){
	switch(a){
		case 1 :
			printf("%c[%d;%d;%dm",27,0,37,44);
			break;

		case 2 :
			printf("%c[%d;%d;%dm",27,0,97,42);
			break;

		case 5 :
			printf("%c[%d;%d;%dm",27,0,37,45);
			break;

		case 7 :
			printf("%c[%d;%d;%dm",27,0,97,43);
			break;

		case 8 :
			printf("%c[%d;%d;%dm",27,0,97,105);
			break;
			
		case 10 :
			printf("%c[%d;%d;%dm",27,0,90,103);
			break;

	}
}


