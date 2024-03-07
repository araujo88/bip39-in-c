all:
	gcc -std=c11 -Wall -Wpedantic -Wextra main.c -o generate_seed -lssl -lcrypto
