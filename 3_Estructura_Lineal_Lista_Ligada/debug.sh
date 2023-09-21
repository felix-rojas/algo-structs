<<<<<<< HEAD
g++ main.cpp -g -o a && valgrind --leak-check=full ./a &> tee memcheck_out.txt
=======
g++ main.cpp -g -o a && valgrind --leak-check=full ./a &> memcheck_out.txt
>>>>>>> a92b162 (silent output for mem check)
