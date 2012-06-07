// BasicCryptoPPWrap.h
// By: Michael R. Rich, 2009
// This code is placed into the public domain by its author
// No warranty or guarantee of applicability or function is granted.

// This is a wrapper designed to allow rapid use of the Crypto++ cryptographic library in a multitude of applications.
// It permits a developer with a nominal understanding of C++ to rapidly field apps that use cryptography to provide basic confidentiality.
// I wrote it so that a developer need not use any other variable types than string to encrypt and decrypt at will.
// Encrypting a string is as simple as:
//        string plainText = "I don't want anyone seeing this without my permission!"
//        string key = BasicCryptoPPWrap::BitGen(256);        // Better not lose this key!!
//        bool err;
//		  string errMsg;
//        string cipherText = BasicCryptoPPWrap::MREncryptStringAES(plainText, key, &err, &errMsg);
// The returned string is not directly viewable.  In this case the string class is used as a handy data buffer for the crypto work.  If you want to see the
// string, simply do this:
//        cout << BasicCryptoPPWrap::HexEncode(cipherText) << "\n";
// To see the text again:
//        string recoveredText = BasicCryptoPPWrap::MRDecryptStringAES(cipherText, key, &err, &errMsg);
//        cout << recoveredText << "\n";
// A more comprehensive example can be seen in the sample code provided with this header

// To use the wrapper, you first need to successfully build and test the Crypto++ library.
// Visit the Crypto++ hompage (www.cryptopp.com) for the latest code, build, and test instructions.
// Then, add the Crypto++ directory to your include directories, link to the cryptopp library and include this header in your code.

// The Crypto++ library is a very powerful set of cryptographic tools, but I found the learning curve to get my first apps running with
// it to be very high.  I examined all the sample code I could find, worked through the API documentation, and examined the
// validation and test code before I finally started catching on.  Then I had to "grep" my way through the files to identify which headers I
// needed to include for a given function.  All of this brainache is undoubtedly due to my own lack of skill and formal training.

// Nonetheless, once I got the pattern figured out, I didn't want to repeat it all over the place in my code, so I wrote this wrapper.
// I don't want you to go through the same thing, so I'm offering this wrapper to those who can use it.

// This simplification comes at a cost of flexibility and performance.  I hope you outgrow this wrapper.  But, until you do, use it well!

// WARNINGS!!
// Data encrypted with methods starting with "MREncrypt" implement a custom initialization vector protocol.  Essentially the iv is either prepended to
// the string or the file you are using.  The "MRDecrypt" methods should be used to decrypt them.  Methods without the "MR" prefix are
// designed to work with a separately supplied iv.
//
// The binary "strings" returned by this wrapper do not play well with the formatted input and output functions and operators (i.e. <<, >>, getLine, etc..)
// You should use binary, unformatted functions to move them around.  See the MREncryptFileAES and MRDecryptFileAES methods for examples.
//
// This wrapper currently only uses one mode of AES encryption.  See flexibility and performance warning above!
//
// I am not a Crypto anything.  The word novice hardly even applies to me.  I am using the Crypto++ library in it's most basic form.
// As a result, I wouldn't use this wrapper in anything serious like financial or medical records, or access to critical infrastructure control
// routines.  I'm just saying.

// If you get a weird link error like "variable not in vtable" or "virtual thunk", add -DCRYPTOPP_DISABLE_ASM to the build options.
// This apparently happens on Mac OS X from time to time (it happened to me)


#ifndef __MRCRYPTOWRAP_H
#define __MRCRYPTOWRAP_H

#include <iostream>
#include <string>
#include <cstdio>
#include "config.h"
#include "hex.h"
#include "files.h"
#include "cryptlib.h"
#include "modes.h"
#include "osrng.h"
#include "filters.h"
#include "aes.h"

using namespace std;
using namespace CryptoPP;

class BasicCryptoPPWrap {
public:

	static bool isHex(string checkForHex) {
		size_t found;
		found = checkForHex.find_first_not_of("0123456789ABCDEF");
		if (found!=string::npos) {
			// This string has non-hex characters in it
			return false;
		} else {
			// only hex characters
			return true;
		}
	}

	static string HexEncode(string binaryString) {

		if (isHex(binaryString)) {
			// This string is already hex, don't convert it!
			return binaryString;
		} else {
			string hexString;
			StringSource(binaryString, true, new HexEncoder(new StringSink(hexString)));
			return hexString;
		}
	}

	static string HexDecode(string hexString) {
		if (isHex(hexString)) {
			string binaryString;
			StringSource(hexString, true, new HexDecoder(new StringSink(binaryString)));
			return binaryString;
		} else {
			// it's already binary!
			return hexString;
		}
	}

	static string MREncryptStringAES(string plainText, string key, bool &err, string &errMsg) {
		// returns an encypted string in binary
		// This version will generate a random 16 byte initialization vector (iv) and prepend it to the actual encrypted text
		// Use MRDecryptStringAES to decrypt this string
		// use EncryptStringAES(plainText, key, iv, err) if you have already have an iv you want to use.
		// key can be sent as a true binary "string" or a hex encoded string
		try {
			// get a random iv
			string iv = ByteGen(AES::BLOCKSIZE);	// BLOCKSIZE is in bytes

			// convert the key if it is sent in hex
			key = HexDecode(key);


			string cipherText = EncryptStringAES(plainText, key, iv, err, errMsg);
			if (err) return "ERROR";

			return iv+cipherText;

		} catch (Exception& e) {
			string errText = "Bad encrypt";
			errMsg = e.GetWhat();
			err = true;
			return errText;
		}
	}

	static string EncryptStringAES(string plainText, string key, string iv, bool &err, string &errMsg) {
		// returns an encypted string in binary
		// This version uses the given iv and returns only the cipherText with no prepend
		// use EncryptStringAES(plainText, key, err) if you want a random iv
		// key and iv can be sent as a true binary "string" or a hex encoded string
		try {
			// convert the iv if it is sent in hex
			iv = HexDecode(iv);

			// convert the key if it is sent in hex
			key = HexDecode(key);

			// setup the encyptor
			CBC_Mode< Rijndael >::Encryption e1( (byte *)key.c_str(), key.length(), (byte *)iv.c_str() );
			// Encryption
			string cipherText;
			StringSource( plainText, true,
						 new StreamTransformationFilter( e1, new CryptoPP::StringSink( cipherText )));

			// return the concatated iv and cipherText
			err = false;
			return cipherText;
		} catch (Exception& e) {
			string errText = "Bad encrypt";
			errMsg = e.GetWhat();
			err = true;
			return errText;
		}

	}

	static string MRDecryptStringAES(string ivAndCipherText, string key, bool &err, string &errMsg){
		// returns the decrypted string
		// This version expects a 16-byte initialization vector prepended to the cipherText
		// This is the output generated by MREncryptStringAES
		// ivAndCipherText & key can be given as hex or binary
		try {
			// convert ivAndCipherText as neccessary
			ivAndCipherText = HexDecode(ivAndCipherText);

			// convert key if necessary
			key = HexDecode(key);

			// recover the bits of the message
			string iv;
			iv.assign(ivAndCipherText, 0, 16);
			string cipherText;
			cipherText.assign(ivAndCipherText, 16, string::npos);

			string plainText = DecryptStringAES(cipherText, key, iv, err, errMsg);
			if (err) return "ERROR";

			err = false;
			return plainText;
		} catch (Exception& e) {
			string errText = "Bad decrypt";
			errMsg = e.GetWhat();
			err = true;
			return errText;
		}
	}

	static string DecryptStringAES(string cipherText, string key, string iv, bool &err, string &errMsg){
		// returns the decrypted string
		// This version uses the given iv
		// use DecryptStringAES(cipherText, key, err) if the iv is prepended to the cipherText
		// cipherText, key, and iv can be given as hex or binary
		try {
			// convert ivAndCipherText as neccessary
			cipherText = HexDecode(cipherText);

			// convert key if necessary
			key = HexDecode(key);

			// convert iv if necessary
			if (isHex(iv)) {
				iv = HexDecode(iv);
			}

			// set up decrypter
			CBC_Mode< Rijndael >::Decryption d((byte *)key.c_str(), key.length(), (byte *)iv.c_str());
			// decrypt
			string plainText;
			StringSource( cipherText, true, new StreamTransformationFilter( d, new StringSink( plainText)));
			err = false;
			return plainText;
		} catch (Exception& e) {
			string errText = "Bad decrypt";
			errMsg = e.GetWhat();
			err = true;
			return errText;
		}
	}

	static void EncryptFileAES(istream& inFile, ostream& outFile, string key, string iv, bool &err, string &errMsg) {
		// will encrypt the file at filenameIn to filenameOut using AES
		// WARNING: The iv must be known and retained for decryption!!
		// key and iv can be hex or binary


		// convert the key and iv
		key = HexDecode(key);
		iv = HexDecode(iv);
		try {
			// Set up the encrypter
			CBC_Mode< Rijndael >::Encryption e1( (byte *)key.c_str(), key.length(), (byte *)iv.c_str() );
			// encrypt
			//if (filenameOut == "cout")
			//	FileSource( filenameIn.c_str(), true, new StreamTransformationFilter( e1, new FileSink(cout)));
			//else
				FileSource( inFile, true, new StreamTransformationFilter( e1, new FileSink(outFile)));
			err= false;
			return;
		} catch (Exception& e) {
			errMsg = e.GetWhat();
			err = true;
			return;
		}
	}


	static void MREncryptFileAES(istream& inFile, ostream& outFile, string key, bool &err, string &errMsg) {
		// will encrypt the file at inFile to outFile using AES
		// but, adds a random iv to the beginning of the newly encrypted file which is recovered and used to decrypt it later.
		// Use MRDecryptFileAES to decrypt this file
		// key can be hex or binary
		// programmers job to open and close the istream and ostream correctly!

		string iv = ByteGen(AES::BLOCKSIZE);

		// encrypt the file to temp
		// generate a random file name that is unlikely to conflict with any existing names.
		string tempName = HexEncode(ByteGen(8));
		ofstream tempFile(tempName.c_str(), ios::binary);
		EncryptFileAES(inFile, tempFile, key, iv, err, errMsg);
		if (err) return;
		tempFile.close();

		try {
			// Now open a new file and put the iv in it

			if (!outFile.good()) {
				err = true;
				errMsg = "Couldn't open desired output file";
				return;
			}

			//write the iv to it
			outFile.write(iv.c_str(), iv.length());

			// open the temp file and load into memory..
			ifstream::pos_type size;
			char * memblock;

			ifstream file(tempName.c_str(), ios::binary | ios::ate);
			if (file.is_open()) {
				size = file.tellg();
				memblock = new char [size];
				file.seekg (0, ios::beg);
				file.read (memblock, size);
				file.close();
			} else {
				err = true;
				errMsg = "Couldn't open encrypted temp file";
				return;
			}

			// write the data to the finished file
			outFile.write(memblock, size);

			delete[] memblock;

			// delete the temp file
			remove(tempName.c_str());
			err = false;
			return;

		} catch (std::exception &e) {
			errMsg = e.what();
			err = true;
			return;
		}
	}


	static void DecryptFileAES(istream& inFile, ostream& outFile, string key, string iv, bool &err, string &errMsg) {
		// will encrypt the file at filenameIn to filenameOut using AES
		// WARNING: The correct iv MUST be provided
		// key and iv can be hex or binary

		// convert the key and iv
		key = HexDecode(key);
		iv = HexDecode(iv);

		try {
			// Set up the encrypter
			CBC_Mode< Rijndael >::Decryption d ( (byte *)key.c_str(), key.length(), (byte *)iv.c_str() );
			// encrypt
			//if (filenameOut == "cout")
			//	FileSource( filenameIn.c_str(), true, new StreamTransformationFilter( d, new FileSink(cout)));
			//else
				FileSource( inFile, true, new StreamTransformationFilter( d, new FileSink(outFile)));
			err= false;
			return;
		} catch (Exception& e) {
			errMsg = e.GetWhat();
			err = true;
			return;
		}
	}

	static void MRDecryptFileAES(istream& inFile, ostream& outFile, string key, bool &err, string &errMsg) {
		// Decrypts a file with a iv stored as the initial 16 bytes;
		// This type of file is generated by MREncryptFileAES

		// first, open the file and load into memory..
		ifstream::pos_type size;
		int datasize;
		char * ivblock;
		char * datablock;

		if (inFile.good()) {
			inFile.seekg(0, ios::end);
			size = inFile.tellg();
			inFile.seekg(0, ios::beg);
			datasize = (int)size-16;
			ivblock = new char[16];
			datablock = new char[datasize];
			inFile.read (ivblock, 16);
			inFile.read(datablock, datasize);

		} else {
			err = true;
			errMsg = "Couldn't open encrypted input file";
			return;
		}

		// Make the iv
		string iv;
		iv.assign(ivblock, 16);
		delete[] ivblock;

		//save the rest of the data as a temp file
		// generate a random file name that is unlikely to conflict with any existing names.
		string tempFile = HexEncode(ByteGen(8));
		ofstream tempOut(tempFile.c_str(), ios::binary);
		if (tempOut.is_open()) {
			// save the data here.
			tempOut.write(datablock, (datasize));
			tempOut.close();
			delete[] datablock;
		} else {
			err = true;
			errMsg = "Couldn't create encrypted temporary file";
			delete[] datablock;
			return;
		}

		ifstream tempIn(tempFile.c_str(), ios::binary);
		// Now decrypt the temp file
		DecryptFileAES(tempIn, outFile, key, iv, err, errMsg);

		tempIn.close();
		remove(tempFile.c_str());
		if (err) return;

		err = false;
		return;
	}

	static string BitGen(int howManyBits) {
		// returns a new random key in binary of the given bit length
		int byteLength = howManyBits/8; // bitLengths always better be div 8!!
		return ByteGen(byteLength);
	}

	static string ByteGen(int howManyBytes) {
		// returns a new random key of the given byte length
		AutoSeededRandomPool rnd;
		byte block[howManyBytes];
		rnd.GenerateBlock(block, howManyBytes);
		string blockString;
		blockString.assign((char *)block, sizeof(block));
		return blockString;
	}


	static string hashSHA256(string inputString) {
		// returns a SHA-256 encoded hash of the inputString in binary
		// always returns 256 bits
		SHA256 hash;
		byte digest [ SHA256::DIGESTSIZE ];

		hash.CalculateDigest( digest, (byte *)inputString.c_str(), inputString.length() );
		string hashString;
		hashString.assign((char *)digest, sizeof(digest));

		return hashString;
	}
	static string hashSHA512(string inputString) {
		// returns a SHA-256 encoded hash of the inputString in binary
		// always returns 256 bits
		SHA512 hash;
		byte digest [ SHA512::DIGESTSIZE ];

		hash.CalculateDigest( digest, (byte *)inputString.c_str(), inputString.length() );
		string hashString;
		hashString.assign((char *)digest, sizeof(digest));

		return hashString;
	}

};

#endif



