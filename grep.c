#include "regular_linux_programming.h"

static struct option	longopts[] = {
	{"file", required_argument, NULL, 'f'},
	{"invert-match", no_argument, NULL, 'v'},
	{"help", no_argument, NULL, 'h'},
	{0, 0, 0, 0}
};

static int	fflg, vflg;

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
	int		opt;
	regex_t	pat;
	int		err;
	int		i;
	char	buf[BUFFER_SIZE];
	FILE	*fp;

	if (argc < 2)
		return (fprintf(stderr, "Usage %s [-vh] [-f FILE] [FILE ...]\n", argv[0]), 1);

	while ((opt = getopt_long(argc, argv, "f:hv", longopts, NULL)) != -1)
	{
		if (opt == 'f')
			fflg = 1;
		if (opt == 'h')
			return (fprintf(stdout, "Usage %s [-vh] [-f FILE] [FILE ...]\n", argv[0]), 0);
		if (opt == 'v')
			vflg = 1;
		if (opt == '?')
			return (fprintf(stderr, "Usage %s [-vh] [-f FILE] [FILE ...]\n", argv[0]), 1);
	}

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
			i++;
		}
		do_grep(&pat, fp);
		fclose(fp);
	}
	regfree(&pat);
	return (0);
}
