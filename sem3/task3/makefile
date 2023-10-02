ASM=nasm
FLAGS=-f elf64
LD=ld

%.o: %.asm
	$(ASM) $(FLAGS) -o $@ $<

program: main.o lib.o
	$(LD) -o $@ $^

.PHONY: clean
clean:
	rm *.o
