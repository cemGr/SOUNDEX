#include "soundex.h"
#include "gmock/gmock.h"

using namespace testing;

class SoundexEncoding : public Test {
public:
	Soundex soundex;
};

TEST_F(SoundexEncoding, RetainsSoloLetterOfOneLetterWord) {
	ASSERT_THAT(soundex.encode("A"), Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits) {
	ASSERT_THAT(soundex.encode("I"), Eq("I000"));
}

TEST_F(SoundexEncoding, ReplaceConsonantsWithAppropriateDigits) {
	ASSERT_THAT(soundex.encode("Ax"), Eq("A200"));
}

TEST_F(SoundexEncoding, IgnoreNonAlpabethLetters) {

	ASSERT_THAT(soundex.encode("A#"), Eq("A00"));
}

TEST_F(SoundexEncoding, ReplaceMultipleConsonantsWithDigits) {

	ASSERT_THAT(soundex.encode("Acdl"), Eq("A234"));
}

TEST_F(SoundexEncoding, LimitLengthToFourCharacters) {

	ASSERT_THAT(soundex.encode("Acdlcd").length(), Eq(4u));
}

//same test as ignoreNonAlphabethLetters
TEST_F(SoundexEncoding, IgnoresVowelsLikeLetters) {

	ASSERT_THAT(soundex.encode("BaEeiIoOuUhHyYcdl"), Eq("B234"));
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings) {

	ASSERT_THAT(soundex.encodedDigit('b'), Eq(soundex.encodedDigit('f')));
	ASSERT_THAT(soundex.encodedDigit('c'), Eq(soundex.encodedDigit('g')));
	ASSERT_THAT(soundex.encodedDigit('d'), Eq(soundex.encodedDigit('t')));

	ASSERT_THAT(soundex.encode("Abfcgdt"), Eq("A123"));
}

TEST_F(SoundexEncoding, UpercaseFirstLatter) {

	ASSERT_THAT(soundex.encode("acdl"), StartsWith("A"));
}

TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants) {

	ASSERT_THAT(soundex.encode("BCDL"), Eq(soundex.encode("Bcdl")));
}

TEST_F(SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st) {

	ASSERT_THAT(soundex.encode("Bbcd"), Eq("B230"));
}

TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingsSeperatedByVowels) {

	ASSERT_THAT(soundex.encode("Jbob"), Eq("J110"));
}