make:
	@gcc -g -o safe_string.exe safe_string.c

test:
	@gcc -g -o test_safe_string.exe  test_safe_string.c
	./test_safe_string.exe
	@rm test_safe_string.exe