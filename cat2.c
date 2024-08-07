// The origin of "cat" is conCATenate.

#include "regular_linux_programming.h"

int	main(int argc, char **argv)
{
	FILE	*fp;
	int		c;
	int		i;

	i = 1;
	while (i < argc)
	{
		fp = fopen(argv[i], "r");
		if (!fp)
		{
			perror(argv[i]);
			exit(1);
		}
		while((c = fgetc(fp)) != EOF)
			if (putchar(c) < 0)
				exit(1);
		fclose(fp);
		i++;
	}
	return (0);
}
