NAME = get_line.a

all: $(NAME)

$(NAME): get_line.c get_line_utils.c
	gcc -c get_line.c -o a.o
	gcc -c get_line_utils.c -o b.o
	ar rcs $(NAME) *.o

clean:
	rm -rf *.o

fclean: clean
	rm -rf *.a

re: fclean all