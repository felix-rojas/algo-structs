g++ main.cpp -g -o a && valgrind --leak-check=full ./a &> memcheck_out.txt