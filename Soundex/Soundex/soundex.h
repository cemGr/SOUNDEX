#ifndef soundex_h
#define soundex_h
#include <unordered_map>
#include <string>

using namespace std;
static const size_t MaxCodeLength{ 4 };

class Soundex
{

public:
	string encode(const string & word) const {
		
		return zeroPad(upperFront(head(word))+tail(encodingDigits(word)));
	}

	string encodedDigit( char letter) const {
		const unordered_map<char, string>encodings{
			{'b' ,"1"}, {'f',"1"}, {'p',"1"}, {'v',"1"},
			{'c' ,"2"}, {'g' ,"2"}, {'j' ,"2"}, {'k' ,"2"}, {'q' ,"2"},
						{'s' ,"2"}, {'x' ,"2"}, {'z' ,"2"},
			{'d' ,"3"}, {'t' ,"3"},
			{'l' ,"4"},
			{'m' ,"5"}, {'n' ,"5"},
			{'r' ,"6"}
		};

		auto it = encodings.find(lower(letter));
		return it == encodings.end() ? notADigit : it->second;
	}

private:
	const string notADigit{ "*" };

	string zeroPad(const string & word) const {
		auto zerosNeeded = MaxCodeLength-word.length();
		return word + string(zerosNeeded,'0');
	}

	string encodingDigits(const string & word) const {
		string encoding;
		encodedHead(encoding, word);
		encodeTail(word, encoding);
		return encoding;
	}

	void encodedHead(std::string &encoding, const std::string & word) const
	{
		encoding += encodedDigit(word.front());
	}

	void encodeTail(const std::string & word, std::string &encoding) const
	{
		for (auto i = 1u; i < word.length(); i++) {
			if (!isComplete(encoding))
				encodeLetter(word[i], encoding,word[i-1]);
		}
	}

	void encodeLetter(char letter, std::string & encoding, char lastLetter) const
	{
		auto digit = encodedDigit(letter);
		if (digit != notADigit &&
			(!isDuplicateEncoding(letter, encoding) || isVowel(lastLetter)))
			encoding += digit;
	}

	bool isDuplicateEncoding(const char &letter, std::string &encoding) const
	{
		return encodedDigit(letter) == lastDigit(encoding);
	}



	string tail(const string & word) const {
		return word.substr(1);
	}

	string head(const string & word) const {
		return word.substr(0, 1);
	}

	bool isComplete(const string &encoding) const {
		return (encoding.length() == MaxCodeLength );
	}

	string lastDigit(const string & encoding) const {
		if(encoding.empty()) return notADigit;
		return string(1, encoding.back());
	}

	string upperFront(const string &word) const {
		return string(1, toupper(static_cast<unsigned char>(word.front())));
	}

	char lower(char c) const {
		return tolower(static_cast<unsigned char>(c));
	}

	bool isVowel(char letter) const {
		return string("aeiouy").find(lower(letter)) != string::npos;
	}
};





#endif // !soundex_h