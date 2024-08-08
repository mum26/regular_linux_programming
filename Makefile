PROGS = cat cat2
CFLAGS = -Wall -Wextra -Werror -g

.PHONY: all
all: $(PROGS)

.PHONY: %
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean-%
clean-%:
	$(RM) $*

.PHONY: fclean-%
fclean-%:
	$(RM) -r $* $*.o $*.dSYM

.PHONY: re-%
re-%: fclean-%
	make $*

.PHONY: clean
clean:
	rm -f $(PROGS)

.PHONY: fclean
fclean:
	rm -rf $(PROGS) *.o *.dSYM

.PHONY: re
re: fclean all

