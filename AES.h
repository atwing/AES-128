/*
 * AES.h
 *
 *  Created on: 16/04/2017
 *      Author: ATPNguyen
 */

#ifndef AES_H_
#define AES_H_

#include <string.h>
#include <iostream>
using namespace std;

typedef unsigned char byte;

class AES
{
public:
	int nBlock; // size of the plaintext to be ciphered
	int nRound; // number of rounds to be used
	int nKey; // key length

	AES(int keylen);
	~AES();
	void Cipher (byte* in, byte* out, byte* w);
		/*
		 * encrypt using AES
		 *
		 *  in	... input array for current plaintext/message, 128-bit block
		 *  out ... ouput array for current ciphertext, 128-bit block
		 *  w	...	array containing the key schedule
		 */

	void KeyExpansion(byte* key, byte* w, int nKey);
		/*
		 * key	...	array containing cipher key
		 * w	...	array containing the key schedule
		 * nKey ... number of 32-bit words comprising the cipher key; 4, 6 or 8
		 */

private:
	void SubBytes(byte** state);
	/*
	 * state ... 4x4 matrix containing current plaintext block which has 16 bytes
	 * substitute bytes in the matrix state using the AES S-box
	 */
	void ShiftRows(byte** state);
	/*
	 * state ... 4x4 matrix containing current plaintext block which has 16 bytes
	 * shift rows byte-wise based on position in the state matrix
	 * -> left-shift 2nd row once
	 * -> left-shift 3rd row twice
	 * -> left-shift 4th row thrice
	 */
	void MixColumns(byte** state);
	/*
	 * state ... 4x4 matrix containing current plaintext block which has 16 bytes
	 * perform column-wise multiplication with a fixed polynomial in finite field GF(2^8)
	 */
	void AddRoundKey(byte** state, byte* w, int start);
	/*
	 * state ... 4x4 matrix containing current plaintext block which has 16 bytes
	 * w	...	array containing expanded keys
	 * start ... starting position to find current round key in w
	 * XOR state with current round key
	 */

	void SubWord(byte* word);
	/*
	 * word ...	4 byte row for Key Expansion
	 * substitute bytes in a row using the AES S-box
	 */
	void RotWord(byte* word);
	/*
	 * word ...	4 byte row for Key Expansion
	 *	left-shift row byte-wise once
	 */
};

#endif /* AES_H_ */
