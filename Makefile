make:
	@gcc -g -o safe_string.o safe_string.c

test:
	@gcc -g -o test_safe_string.o  test_safe_string.c
	./test_safe_string.o
	@rm test_safe_string.o