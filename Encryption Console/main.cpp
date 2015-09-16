#include <string>
#include <iostream>

using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyz0123456789.,?!- ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string removeDupLetters(string keyword){
	
	string tempText;

	for (unsigned int i = 0; i < keyword.length(); i++){

		if (tempText.find(keyword[i]) == string::npos && alphabet.find(keyword[i]) != string::npos){
			tempText += keyword[i];
		}
	}

	return tempText;
}

string removeInvalidLetters(string keyword){
	
	string tempText;

	for (unsigned int i = 0; i < keyword.length(); i++){

		if (alphabet.find(keyword[i]) != string::npos){
			tempText += keyword[i];
		}
	}

	return tempText;
}

string keywordCryptobet(string keyword, string keyletter){

	string reducedAlphabet = alphabet;

	for (unsigned int i1 = 0; i1 < keyword.length(); i1++){

		for (unsigned int i2 = 0; i2 < reducedAlphabet.length(); i2++){

			if (reducedAlphabet[i2] == keyword[i1]){
				reducedAlphabet.erase(reducedAlphabet.begin() + i2);
				i2--;
			}
		}
	}

	unsigned int keyletterPos = alphabet.find(keyletter);
	unsigned int alphabetPos = keyletterPos;

	string tempText = alphabet;

	while (alphabetPos < keyword.length() + keyletterPos){
		tempText[alphabetPos % alphabet.length()] = keyword[alphabetPos - keyletterPos];
		alphabetPos++;
	}

	while (alphabetPos < alphabet.length() + keyletterPos){
		tempText[alphabetPos % alphabet.length()] = reducedAlphabet[alphabetPos - keyletterPos - keyword.length()];
		alphabetPos++;
	}

	return tempText;
}

string jellyshiftCryptobet(string keyword){

	int midPos = alphabet.length() / 2;

	string firstHalf = alphabet.substr(0, midPos);
	string secondHalf = alphabet.substr(midPos);
	string tempText;

	for (unsigned int i = 0; i < firstHalf.length(); i++){
		int shiftAmount = alphabet.find(keyword[i % keyword.length()]);

		swap(firstHalf[i], secondHalf[(i + shiftAmount) % secondHalf.length()]);
	}

	for (unsigned int i = 0; i < secondHalf.length(); i++){
		
		if (i < firstHalf.length()){
			tempText += firstHalf[i];
		}

		tempText += secondHalf[i];
	}

	return tempText;
}

string encryptMessage(string message, string cryptobet){
	
	string tempText;

	for (unsigned int i = 0; i < message.length(); i++){

		int cryptobetPos = alphabet.find(message[i]);

		if (cryptobetPos != string::npos){
			tempText += cryptobet[cryptobetPos];
		}
		else{
			tempText += message[i];
		}
	}

	return tempText;
}

string decryptMessage(string message, string cryptobet){
	
	string tempText;

	for (unsigned int i = 0; i < message.length(); i++){
		int alphabetPos = cryptobet.find(message[i]);

		if (alphabetPos != string::npos){
			tempText += alphabet[alphabetPos];
		}
		else{
			tempText += message[i];
		}
	}

	return tempText;
}

int main(int argc, char** argv){

	string option = "3";

	while (option == "3"){

		cout << "Which algorithm would you like to use" << endl << "[1] Keyword Cipher" << endl << "[2] Jellyshift Cipher" << endl;

		string algorithm;
		getline(cin, algorithm);

		while (algorithm != "1" && algorithm != "2"){
			cout << endl << "That is not a valid option. Please try again:" << endl;
			getline(cin, algorithm);
		}

		cout << endl << "What is your keyphrase?" << endl;

		string keyword;
		getline(cin, keyword);

		string cryptobet;

		if (algorithm == "1"){

			cout << endl << "What is your keyletter?" << endl;

			string keyletter;
			getline(cin, keyletter);

			while (alphabet.find(keyletter) == string::npos || keyletter.length() > 1){
				cout << endl << "That is not a valid keyletter. Please try again:" << endl;
				getline(cin, keyletter);
			}

			keyword = removeDupLetters(keyword);
			cryptobet = keywordCryptobet(keyword, keyletter);
		}
		else{
			keyword = removeInvalidLetters(keyword);
			cryptobet = jellyshiftCryptobet(keyword);
		}

		cout << endl << "Would you like to:" << endl << "[1] Encrypt" << endl << "[2] Decrypt" << endl;
		getline(cin, option);

		while (option != "1" && option != "2"){
			cout << endl << "That is not a valid option. Please try again:" << endl;
			getline(cin, option);
		}

		while (option == "1" || option == "2"){
			cout << endl << "Input your message below:" << endl;

			string message;
			getline(cin, message);

			if (option == "1"){
				cout << endl << "Your encrypted message is:" << endl << encryptMessage(message, cryptobet) << endl;
			}
			else {
				cout << endl << "Your decrypted message is:" << endl << decryptMessage(message, cryptobet) << endl;
			}

			cout << endl << "What next?" << endl << "[1] Encrypt" << endl << "[2] Decrypt" << endl << "[3] New encryption parameters" << endl << "[Q] Quit" << endl;

			getline(cin, option);
			cout << endl;
		}

	}

	return 0;
}

