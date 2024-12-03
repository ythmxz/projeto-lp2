#include <stdio.h>
#include <time.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#define DELAY(x) Sleep(x)
#else
#define DELAY(x) usleep(x * 1000)
#endif

int main() {

	int i = 0;
	int cor = 31;

	while ( i == 0 ) {

		printf("\033[%dm", cor);
		printf("TEXTO COLORIDO!\r");

		if ( cor > 37 )
			cor = 31;

		cor++;

		DELAY(1000);

	}

	return 0;

}
