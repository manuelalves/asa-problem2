asa_problem2: 	main.cpp
		$(RM) main
		g++ -O3 -ansi -Wall -o main main.cpp -lm

clean:
		$(RM) main
