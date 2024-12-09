main: main.cpp bruteforce_dlp.cpp appl_crypto.hpp
	g++ -pthread -o main main.cpp bruteforce_dlp.cpp elgamal.cpp diffhell_keyexchng.cpp elCurveIES.cpp rsa.cpp -lntl -lgmp
clean:
	rm -rf main