#include "regular_linux_programming.h"

static struct option	longopts[] = {
	{"lines", required_argument, NULL, 'n'},
	{"help", no_argument, NULL, 'h'},
	{0, 0, 0, 0}
};

static void	do_head(FILE *fp, long nlines)
{
	int	c;

	if (nlines <= 0)
		return ;
	while ((c = getc(fp)) != EOF)
	{
		if (putchar(c) < 0)
			exit(1);
		if (c == '\n')
		{
			nlines--;
			if (nlines == 0)
				return ;
		}
	}
	return ;
}

int	main(int argc, char **argv)
{
	int		opt;
	long	nlines;
	int		i;
	FILE	*fp;

	nlines = DEFAULT_N_LINES;
	while ((opt = getopt_long(argc, argv, "n:", longopts, NULL)) != -1)
	{
		if (opt == 'n')
			nlines = atoi(optarg);
		if (opt == 'h')
			return (fprintf(stdout, "Usage %s [-n LINES] [FILE ...]\n", argv[0]), 0);
		if (opt == '?')
			return (fprintf(stderr, "Usage %s [-n LINES] [FILE ...]\n", argv[0]), 1);
	}
	if (optind == argc)
		do_head(stdin, nlines);
	else
	{
		i = optind;
		while (i < argc)
		{
			fp = fopen(argv[i], "r");
			if (!fp)
			{
				perror(argv[i]);
				exit(1);
			}
			do_head(fp, nlines);
			fclose(fp);
			i++;
		}
	}
	return (0);
}

