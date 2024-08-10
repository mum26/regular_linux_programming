#include "regular_linux_programming.h"

static void	do_grep(regex_t *pat, FILE *src)
{
	char	buf[BUFFER_SIZE];

	while (fgets(buf, sizeof(buf), src))
	{
		if (regexec(pat, buf, 0, NULL, 0) == 0)
			fputs(buf, stdout);
	}
	return ;
}

int	main(int argc, char **argv)
{
	regex_t	pat;
	int		err;
	int		i;
	char	buf[BUFFER_SIZE];
	FILE	*fp;

	if (argc < 2)
		return (fputs("no pattern\n", stderr), 1);
	err = regcomp(&pat, argv[1], REG_EXTENDED | REG_NOSUB | REG_NEWLINE);
	if (err != 0)
	{
		regerror(err, &pat, buf, sizeof(buf));
		puts(buf);
		exit(1);
	}
	if (argc == 2)
		do_grep(&pat, stdin);
	else
	{
		i = 2;
		while(i < argc)
		{
			fp = fopen(argv[i], "r");
			if (!fp)
				return (perror(argv[i]), 1);
		}
		do_grep(&pat, fp);
		fclose(fp);
	}
	regfree(&pat);
	return (0);
}
