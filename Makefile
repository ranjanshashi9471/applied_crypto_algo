main: main.cpp bruteforce_dlp.cpp appl_crypto.hpp
	g++ -O2 -std=c++11 -pthread -march=native -o main main.cpp bruteforce_dlp.cpp elgamal.cpp diffhell_keyexchng.cpp -lntl -lgmp
clean:
	rm -rf main
