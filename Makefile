main: main.cpp crypt_classes.cpp appl_crypto.hpp	
	g++ -O2 -std=c++11 -pthread -march=native -o main main.cpp crypt_classes.cpp -lntl -lgmp
clean:
	rm -rf main
