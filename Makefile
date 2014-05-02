################################################################################
# Makefile
# History:
#        2014/05/03 Dennis Create
################################################################################

subdirs := $(sort $(subst /,,$(dir $(wildcard */*))))

all:
	$(foreach N,$(subdirs),make -C $(N);)

.PHONY: clean
clean:
	$(foreach N,$(subdirs),make -C $(N) clean;)
