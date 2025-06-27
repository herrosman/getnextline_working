#include "get_next_line.h"

int main()
{
	FILE *f = fopen("sample.txt", "r");

	char *line;
	while ((line = get_next_line(fileno(f))))
	{
		printf("Line: %s", line);  // or use printf("Line: %s\n", line) carefully
		free(line);                // ✅ prevent leak
	}

}
