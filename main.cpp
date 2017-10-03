//============================================================================
// Name        : main.cpp
// Author      : ATPNguyen
// Version     :
// Copyright   : 
// Description : AES Encryption
//============================================================================

#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "AES.h"
using namespace std;

int main(int argc, char* argv[]) {

	// initialisation
	int nKey = 4;
	byte plaintext[16];
	byte key[16];
	byte ciphertext[16];

	AES myAES(128); // set encryption mode to AES-128
	byte key_sched[4*myAES.nBlock*(myAES.nRound+1)];

	// read first 16 bytes which is the master key given
	read(STDIN_FILENO, key, 16);

	// generate round keys
	myAES.KeyExpansion(key, key_sched, nKey);

	// perform encryption for all plaintext blocks
	for(;;){
	    if (read(STDIN_FILENO, plaintext, 16) <= 1)
	    	exit(0); // exit program once all plaintext blocks are encrypted

		// encrypt using AES
		myAES.Cipher(plaintext, ciphertext, key_sched);

		// output resulting ciphertext
		write(STDOUT_FILENO, ciphertext, 16);
	}
}
