PROGS = cat cat2
CFLAGS = -Wall -Wextra -Werror -g

.PHONY: all
all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean-%
clean-%:
	rm -f $@

.PHONY: fclean-%
fclean-%:
	rm -rf $@ $@.o $@.dSYM

.PHONY: re-%
re-%: fclean-% %
	
.PHONY: clean
clean:
	rm -f $(PROGS)

.PHONY: fclean
fclean:
	rm -rf $(PROGS) *.o *.dSYM

.PHONY: re
re: fclean all

