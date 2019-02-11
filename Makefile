nm:
	@echo "making nm"
	@make re -C nm/
	@make clean -C nm/
	@mv nm/my_nm .

objdump:
	make re -C objdump/
	make clean -C objdump/
	mb objdump/my_objdump .

all: nm objdump

.PHONY: all nm objdump