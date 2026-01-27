mexec: mexec.o info.o
	gcc -g -std=gnu11 -Werror -Wall -Wextra -Wpedantic -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition -o mexec mexec.o info.o

mexec.o: mexec.c info.h
	gcc -g -std=gnu11 -Werror -Wall -Wextra -Wpedantic -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition -c mexec.c

info.o: info.c info.h
	gcc -g -std=gnu11 -Werror -Wall -Wextra -Wpedantic -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition -c info.c

clean:
	rm -f *.o mexec