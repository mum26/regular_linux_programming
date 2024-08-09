// The origin of "cat" is conCATenate.

#include "regular_linux_programming.h"

static struct option	longopts[] = {
	{"tab", no_argument, NULL, 't'},
	{"end", no_argument, NULL, 'e'},
	{0, 0, 0, 0}
};

static int	eflg, tflg;

static void	die(const char *s)
{
	perror(s);
	exit(1);
}

static void	do_cat(FILE *fp)
{
	int	c;

	if (!fp)
		die("do_cat");
	while ((c = fgetc(fp)) != EOF)
	{
		if (eflg && c == '\n')
			if (putchar('$') < 0)
				exit(1);
		if (tflg && c == '\t')
		{
			if (putchar('\\') < 0 || putchar('t') < 0)
				exit(1);
			continue ;
		}
		if (putchar(c) < 0)
			exit(1);
	}
}

int	main(int argc, char **argv)
{
	int		i;
	int		opt;
	FILE	*fp;

	while ((opt = getopt_long(argc, argv, "et", longopts, NULL)) != -1)
	{
		if (opt == 'e')
			eflg = 1;
		if (opt == 't')
			tflg = 1;
		if (opt == '?')
			return (fprintf(stderr, "Usage %s [-et] [FILE ...]\n", argv[0]), 1);
	}
	if (optind == argc)
		do_cat(stdin);
	else
	{
		i = optind;
		while (i < argc)
		{
			fp = fopen(argv[i], "r");
			if (!fp)
				die(argv[i]);
			do_cat(fp);
			fclose(fp);
			i++;
		}
	}
	return (0);
}

