#include <deque>
#include <list>
#include <vector>
#include <string>

#include <unittest++/UnitTest++.h>

#include <string_utils.h>

TEST(CapitalizeString)
{
    CHECK_EQUAL("All lowercase", string_utils::capitalize("all lowercase"));
}

TEST(CapitalizeSingleChar)
{
    CHECK_EQUAL("X", string_utils::capitalize("x"));
}

TEST(CapitalizeEmptyString)
{
    CHECK_EQUAL("", string_utils::capitalize(""));
}

TEST(CapitalizeUpperCaseString)
{
    CHECK_EQUAL("UPPERCASE", string_utils::capitalize("UPPERCASE"));
}

TEST(CapitalizeNumericString)
{
    CHECK_EQUAL("12345678", string_utils::capitalize("12345678"));
}

TEST(CapitalizeAccentedStringNegative)
{
    CHECK_EQUAL("éclair", string_utils::capitalize("éclair"));
}

TEST(CenterString)
{
    CHECK_EQUAL("   cat   ", string_utils::center("cat", 9));
}

TEST(CenterStringWithFiller)
{
    CHECK_EQUAL("wwwdogwww", string_utils::center("dog", 9, 'w'));
}

TEST(CenterStringWithOneLeftOver)
{
    CHECK_EQUAL("mouse ", string_utils::center("mouse", 6));
}

TEST(CenterStringWithTooSmallAWidth)
{
    CHECK_EQUAL("rat", string_utils::center("rat", 2));
}

TEST(CenterStringWithNegativeWidth)
{
    CHECK_EQUAL("tiger", string_utils::center("tiger", -1));
}

TEST(CountCharsInAString)
{
    CHECK_EQUAL(13, string_utils::count("nnnnnnnnnnnnn", "n"));
}

TEST(CountSubstrings)
{
    CHECK_EQUAL(3, string_utils::count("the cat with the hat sat on the mat", "the"));
}

TEST(CountSubstringsStartingMidway)
{
    CHECK_EQUAL(2, string_utils::count("the cat with the hat sat on the mat", "the", 4));
}

TEST(CountSubstringsEndingingMidway)
{
    CHECK_EQUAL(1, string_utils::count("the cat with the hat sat on the mat", "the", 4, 28));
}

TEST(EndsWithPositive)
{
    CHECK_EQUAL(true, string_utils::endswith("contraband", "band"));
}

TEST(EndsWithNegative)
{
    CHECK_EQUAL(false, string_utils::endswith("contraband", "banned"));
}

TEST(EndsWithDealWithExtraLongStrings)
{
    CHECK_EQUAL(false, string_utils::endswith("band", "contraband"));
}

TEST(EndswithStartMidStringPositive)
{
    CHECK_EQUAL(true, string_utils::endswith("abcdef", "def", 3));
}

TEST(EndswithStartMidStringNegative)
{
    CHECK_EQUAL(false, string_utils::endswith("abcdef", "def", 4));
}

TEST(EndswithEndMidStringPositive)
{
    CHECK_EQUAL(true, string_utils::endswith("abcdef", "de", 3, 5));
}

TEST(EndswithEndMidStringNegative)
{
    CHECK_EQUAL(false, string_utils::endswith("abcdef", "de", 4, 5));
}

TEST(ExpandTabs)
{
    CHECK_EQUAL("        ", string_utils::expandtabs("\t"));
}

TEST(ExpandTabsAccountsForChars)
{
    CHECK_EQUAL("xxxxxxx y", string_utils::expandtabs("xxxxxxx\ty"));
}

TEST(ExpandTabsCanRemove)
{
    CHECK_EQUAL("abcxyz", string_utils::expandtabs("a\tb\tc\tx\ty\tz", 0));
}

TEST(ExpandTabsAccountsForNewlines)
{
    const std::string returned = string_utils::expandtabs("xxxxxxx\ty\n"
                                                          "x\t\ty");

    CHECK_EQUAL("xxxxxxx y\n"
                "x               y", returned);
}

TEST(FindSubstringPositive)
{
    CHECK_EQUAL(18, string_utils::find("A haystack with a needle", "needle"));
}

TEST(FindSubstringNegative)
{
    CHECK_EQUAL(-1, string_utils::find("A haystack with a needle", "needles"));
}

TEST(FindSubstringWithStartPosition)
{
    const int index = string_utils::find("A needle can be found in a haystack "
                                         "with a needle", "needle", 5);
    CHECK_EQUAL(43, index);
}

TEST(FindSubstringWithEndPosition)
{
    CHECK_EQUAL(-1, string_utils::find("Needle", "Needle", 0, 4));
}

TEST(GetIndexOfSubstringThrows)
{
    CHECK_THROW(string_utils::index("The Holy Hand Grenade", "Antioch"), string_utils::value_error);
}

TEST(CheckExceptionReasonForIndexFailure)
{
    try
    {
        string_utils::index("The Holy Hand Grenade", "Antioch");
    }
    catch (const string_utils::value_error& e)
    {
        CHECK_EQUAL("substring not found", e.what());
    }
}

TEST(GetIndexOfSubstringPositive)
{
    CHECK_EQUAL(9, string_utils::index("The Holy Hand Grenade", "Hand"));
}

TEST(GetIndexOfSubstringBeforeStartThrows)
{
    CHECK_THROW(string_utils::index("The Holy Hand Grenade", "Holy", 6), string_utils::value_error);
}

TEST(GetIndexOfSubstringAfterEndThrows)
{
    CHECK_THROW(string_utils::index("The Holy Hand Grenade", "Holy", 0, 3), string_utils::value_error);
}

TEST(IdentifyAlphanumericStringsEmpty)
{
    CHECK_EQUAL(false, string_utils::isalnum(""));
}

TEST(IdentifyAlphanumericStringsNegative)
{
    CHECK_EQUAL(false, string_utils::isalnum("The Holy Hand Grenade"));
}

TEST(IdentifyAlphanumericStringsPositive)
{
    CHECK_EQUAL(true, string_utils::isalnum("TheHolyHandGrenade69"));
}

TEST(IdentifyAlphabeticStringsEmpty)
{
    CHECK_EQUAL(false, string_utils::isalpha(""));
}

TEST(IdentifyAlphabeticStringsNegative)
{
    CHECK_EQUAL(false, string_utils::isalpha("We already got one!"));
}

TEST(IdentifyAlphabeticStringsPositive)
{
    CHECK_EQUAL(true, string_utils::isalpha("Grail"));
}

TEST(IdentifyDigitsEmpty)
{
    CHECK_EQUAL(false, string_utils::isdigit(""));
}

TEST(IdentifyDigitsNegative)
{
    CHECK_EQUAL(false, string_utils::isdigit("OneTwoThree"));
}

TEST(IdentifyDigitsPositive)
{
    CHECK_EQUAL(true, string_utils::isdigit("12345678"));
}

TEST(IdentifyLowercaseEmpty)
{
    CHECK_EQUAL(false, string_utils::islower(""));
}

TEST(IdentifyLowercaseNegative)
{
    CHECK_EQUAL(false, string_utils::islower("UPPERCASE"));
}

TEST(IdentifyLowercasePositive)
{
    CHECK_EQUAL(true, string_utils::islower("lowercase"));
}

TEST(IdentifySpaceEmpty)
{
    CHECK_EQUAL(false, string_utils::isspace(""));
}

TEST(IdentifySpaceNegative)
{
    CHECK_EQUAL(false, string_utils::isspace("The final frontier"));
}

TEST(IdentifySpacePositive)
{
    CHECK_EQUAL(true, string_utils::isspace("        "));
}

TEST(IdentifyTabAsSpacePositive)
{
    CHECK_EQUAL(true, string_utils::isspace("\t"));
}

TEST(IdentifyNewlineAsSpacePositive)
{
    CHECK_EQUAL(true, string_utils::isspace("\r\n"));
}

TEST(IdentifyTitlecaseEmpty)
{
    CHECK_EQUAL(false, string_utils::istitle(""));
}

TEST(IdentifyTitlecaseNegative)
{
    CHECK_EQUAL(false, string_utils::istitle("all lowercase"));
}

TEST(IdentifyTitlecasePositive)
{
    CHECK_EQUAL(true, string_utils::istitle("This Is Title Case."));
}

TEST(IdentifyDOubleTItlecaseNegative)
{
    CHECK_EQUAL(false, string_utils::istitle("DOuble TItle"));
}

TEST(IdentifyMixedTitlecaseNegative)
{
    CHECK_EQUAL(false, string_utils::istitle("MiXed CaSe!"));
}

TEST(IdentifyNumericTitlecaseNegative)
{
    CHECK_EQUAL(false, string_utils::istitle("12345"));
}

TEST(IdentifyUppercaseEmpty)
{
    CHECK_EQUAL(false, string_utils::isupper(""));
}

TEST(IdentifyUppercaseNegative)
{
    CHECK_EQUAL(false, string_utils::isupper("lowercase"));
}

TEST(IdentifyUppercasePositive)
{
    CHECK_EQUAL(true, string_utils::isupper("UPPERCASE"));
}

TEST(JoinListOfSingleString)
{
    std::list<std::string> list_of_strings;
    list_of_strings.push_back("Word");

    CHECK_EQUAL("Word", string_utils::join(",", list_of_strings));
}

TEST(JoinListOfStrings)
{
    std::list<std::string> list_of_strings;
    list_of_strings.push_back("Comma");
    list_of_strings.push_back("Separated");
    list_of_strings.push_back("Values");

    CHECK_EQUAL("Comma,Separated,Values", string_utils::join(",", list_of_strings));
}

TEST(JoinVectorOfStrings)
{
    std::vector<std::string> vector_of_strings;
    vector_of_strings.push_back("Tab");
    vector_of_strings.push_back("Separated");
    vector_of_strings.push_back("Values");

    CHECK_EQUAL("Tab\tSeparated\tValues", string_utils::join("\t", vector_of_strings));
}

TEST(JoinDequeOfChars)
{
    std::deque<char> deque_of_chars;
    deque_of_chars.push_back('z');
    deque_of_chars.push_back('y');
    deque_of_chars.push_back('x');

    CHECK_EQUAL("zyx", string_utils::join("", deque_of_chars));
}

TEST(JoinStdString)
{
    CHECK_EQUAL("a b c d e f", string_utils::join(" ", std::string("abcdef")));
}

TEST(JoinArrayOfChar)
{
    CHECK_EQUAL("a b c d e f", string_utils::join(" ", "abcdef"));
}

TEST(LeftJustifyStringShorterThanWidth)
{
    CHECK_EQUAL("a   ", string_utils::ljust("a", 4));
}

TEST(LeftJustifyStringLongerThanWidth)
{
    CHECK_EQUAL("bbbbb", string_utils::ljust("bbbbb", 3));
}

TEST(LeftJustifyStringWithDifferentChar)
{
    CHECK_EQUAL("cxxxx", string_utils::ljust("c", 5, 'x'));
}

TEST(LowercaseString)
{
    CHECK_EQUAL("lowercase", string_utils::lower("LOWERCASE"));
}

TEST(LeftStripString)
{
    CHECK_EQUAL("beard", string_utils::lstrip("    \t\r\nbeard"));
}

TEST(LeftStripStringWithAnyCharacter)
{
    CHECK_EQUAL("bush", string_utils::lstrip("xxxbush", "x"));
}

TEST(LeftStripStringWithAnyCharacters)
{
    CHECK_EQUAL("hedge", string_utils::lstrip("xyxyxyhedge", "xy"));
}

TEST(PartitionStringEmpty)
{
    string_utils::partition_t partition = string_utils::partition("", ",");
    CHECK(partition.head.empty());
    CHECK(partition.sep.empty());
    CHECK(partition.tail.empty());
}

TEST(PartitionStringNegative)
{
    string_utils::partition_t partition = string_utils::partition("The Division Bell", "/");
    CHECK_EQUAL("The Division Bell", partition.head);
    CHECK(partition.sep.empty());
    CHECK(partition.tail.empty());
}

TEST(PartitionStringPositive)
{
    string_utils::partition_t partition = string_utils::partition("Key: Value", ": ");
    CHECK_EQUAL("Key", partition.head);
    CHECK_EQUAL(": ", partition.sep);
    CHECK_EQUAL("Value", partition.tail);
}

TEST(PartitionSecondStringPositive)
{
    string_utils::partition_t partition = string_utils::partition("Key: Value: Second", ": ");
    CHECK_EQUAL("Key", partition.head);
    CHECK_EQUAL(": ", partition.sep);
    CHECK_EQUAL("Value: Second", partition.tail);
}

TEST(ReplaceEmpty)
{
    CHECK_EQUAL("", string_utils::replace("", "Something", "Nothing", 2));
}

TEST(ReplaceNotThere)
{
    CHECK_EQUAL("Anything", string_utils::replace("Anything", "Something", "Nothing", 2));
}

TEST(ReplaceSingleChar)
{
    CHECK_EQUAL("snooze", string_utils::replace("sneeze", "e", "o", 2));
}

TEST(ReplaceStrings)
{
    CHECK_EQUAL("another cat sat on another mat",
                string_utils::replace("the cat sat on the mat", "the", "another"));
}

TEST(ReverseFindEmpty)
{
    CHECK_EQUAL(9, string_utils::rfind("something", ""));
}

TEST(ReverseFindNegative)
{
    CHECK_EQUAL(-1, string_utils::rfind("", "something"));
}

TEST(ReverseFindWholeString)
{
    CHECK_EQUAL(0, string_utils::rfind("something", "something"));
}

TEST(ReverseFindLastString)
{
    CHECK_EQUAL(4, string_utils::rfind("baa baa black sheep", "baa"));
}

TEST(ReverseFindWithStartNegative)
{
    CHECK_EQUAL(-1, string_utils::rfind("baa baa black sheep", "baa", 5));
}

TEST(ReverseFindWithStartPositive)
{
    CHECK_EQUAL(4, string_utils::rfind("baa baa black sheep", "baa", 3));
}

TEST(ReverseFindWithEndNegative)
{
    CHECK_EQUAL(-1, string_utils::rfind("baa baa black sheep", "sheep", 0, 10));
}

TEST(ReverseFindWithEndNegativeBorderline)
{
    CHECK_EQUAL(-1, string_utils::rfind("baa baa black sheep", "baa", 0, 5));
}

TEST(ReverseFindWithEndPositive)
{
    CHECK_EQUAL(0, string_utils::rfind("baa baa black sheep", "baa", 0, 3));
}

TEST(ReverseIndexThrows)
{
    CHECK_THROW(string_utils::rindex("The C++03 Standard", "std::wobbly"), string_utils::value_error);
}

TEST(RightJustifyStringShorterThanWidth)
{
    CHECK_EQUAL("   a", string_utils::rjust("a", 4));
}

TEST(RightJustifyStringLongerThanWidth)
{
    CHECK_EQUAL("bbbbb", string_utils::rjust("bbbbb", 3));
}

TEST(RightJustifyStringWithDifferentChar)
{
    CHECK_EQUAL("xxxxc", string_utils::rjust("c", 5, 'x'));
}

TEST(ReversePartitionStringEmpty)
{
    string_utils::partition_t partition = string_utils::rpartition("", ",");
    CHECK(partition.head.empty());
    CHECK(partition.sep.empty());
    CHECK(partition.tail.empty());
}

TEST(ReversePartitionStringNegative)
{
    string_utils::partition_t partition = string_utils::rpartition("Dark Side", "/");
    CHECK_EQUAL("Dark Side", partition.head);
    CHECK(partition.sep.empty());
    CHECK(partition.tail.empty());
}

TEST(ReversePartitionSecondStringPositive)
{
    string_utils::partition_t partition = string_utils::rpartition("Key: Value: Second", ": ");
    CHECK_EQUAL("Key: Value", partition.head);
    CHECK_EQUAL(": ", partition.sep);
    CHECK_EQUAL("Second", partition.tail);
}

TEST(ReverseSplitEmptySeperatorThrows)
{
    CHECK_THROW(string_utils::rsplit("", ""), string_utils::value_error);
}

TEST(CheckExceptionReasonForSplitFailure)
{
    try
    {
        string_utils::rsplit("", "");
    }
    catch (const string_utils::value_error& e)
    {
        CHECK_EQUAL("empty separator", e.what());
    }
}

TEST(ReverseSplitEmptyString)
{
    string_utils::string_list returned = string_utils::rsplit("", ",");
    CHECK_EQUAL(1U, returned.size());
    CHECK_EQUAL("", returned.back());
}

TEST(ReverseSplitOneWordDefault)
{
    string_utils::string_list returned = string_utils::rsplit("Badger");
    CHECK_EQUAL(1U, returned.size());
    CHECK_EQUAL("Badger", returned.front());
}

TEST(ReverseSplitOneWordDefaultWithAddedNewlines)
{
    string_utils::string_list returned = string_utils::rsplit("Badger\r\n");
    CHECK_EQUAL(1U, returned.size());
    CHECK_EQUAL("Badger", returned.front());
}

TEST(ReverseSplitThreeWordsDefault)
{
    string_utils::string_list returned = string_utils::rsplit("Famous Last Words");
    CHECK_EQUAL(3U, returned.size());
    CHECK_EQUAL("Famous", returned.front()); returned.pop_front();
    CHECK_EQUAL("Last", returned.front()); returned.pop_front();
    CHECK_EQUAL("Words", returned.front()); returned.pop_front();
}

TEST(ReverseSplitThreeWordsDefaultWithTabs)
{
    string_utils::string_list returned = string_utils::rsplit("Blah\tBlah\tBlah");
    CHECK_EQUAL(3U, returned.size());
    for (int count = 3; count > 0; --count)
    {
        CHECK_EQUAL("Blah", returned.front());
        returned.pop_front();
    }
}

TEST(ReverseSplitThreeWordsDefaultWithMultipleTabs)
{
    string_utils::string_list returned = string_utils::rsplit("Blah\t\t\tBlah\t\tBlah");
    CHECK_EQUAL(3U, returned.size());
    for (int count = 3; count > 0; --count)
    {
        CHECK_EQUAL("Blah", returned.front());
        returned.pop_front();
    }
}

TEST(ReverseSplitThreeWordsCommaSpace)
{
    string_utils::string_list returned = string_utils::rsplit("Three, Dog, Night", ", ");
    CHECK_EQUAL(3U, returned.size());
    CHECK_EQUAL("Three", returned.front()); returned.pop_front();
    CHECK_EQUAL("Dog", returned.front()); returned.pop_front();
    CHECK_EQUAL("Night", returned.front()); returned.pop_front();
}

TEST(ReverseSplitThreeWordsOnceOnly)
{
    string_utils::string_list returned = string_utils::rsplit("Three, Dog, Night", ", ", 1);
    CHECK_EQUAL(2U, returned.size());
    CHECK_EQUAL("Three, Dog", returned.front()); returned.pop_front();
    CHECK_EQUAL("Night", returned.front()); returned.pop_front();
}

TEST(RightStripString)
{
    CHECK_EQUAL("tease", string_utils::rstrip("tease \t\r\n"));
}

TEST(RightStripStringWithNothingToDo)
{
    CHECK_EQUAL("tease", string_utils::rstrip("tease"));
}

TEST(SplitEmptyString)
{
    string_utils::string_list returned = string_utils::split("", ",");
    CHECK_EQUAL(1U, returned.size());
    CHECK_EQUAL("", returned.back());
}

TEST(SplitThreeWordsDefault)
{
    string_utils::string_list returned = string_utils::split("Famous Last Words");
    CHECK_EQUAL(3U, returned.size());
    CHECK_EQUAL("Famous", returned.front()); returned.pop_front();
    CHECK_EQUAL("Last", returned.front()); returned.pop_front();
    CHECK_EQUAL("Words", returned.front()); returned.pop_front();
}

TEST(SplitThreeWordsDefaultWithNewlines)
{
    string_utils::string_list returned = string_utils::split("Rapid\r\nEar\r\nMovement");
    CHECK_EQUAL(3U, returned.size());
    CHECK_EQUAL("Rapid", returned.front()); returned.pop_front();
    CHECK_EQUAL("Ear", returned.front()); returned.pop_front();
    CHECK_EQUAL("Movement", returned.front()); returned.pop_front();
}

TEST(SplitThreeWordsCommaSpace)
{
    string_utils::string_list returned = string_utils::split("Three, Dog, Night", ", ");
    CHECK_EQUAL(3U, returned.size());
    CHECK_EQUAL("Three", returned.front()); returned.pop_front();
    CHECK_EQUAL("Dog", returned.front()); returned.pop_front();
    CHECK_EQUAL("Night", returned.front()); returned.pop_front();
}

TEST(SplitThreeWordsOnceOnly)
{
    string_utils::string_list returned = string_utils::split("Three, Dog, Night", ", ", 1);
    CHECK_EQUAL(2U, returned.size());
    CHECK_EQUAL("Three", returned.front()); returned.pop_front();
    CHECK_EQUAL("Dog, Night", returned.front()); returned.pop_front();
}

TEST(SplitSeparatorAtStart)
{
    string_utils::string_list returned = string_utils::split("|pipe", "|");
    CHECK_EQUAL(2U, returned.size());
    CHECK_EQUAL("", returned.front()); returned.pop_front();
    CHECK_EQUAL("pipe", returned.front()); returned.pop_front();
}

TEST(SplitSeparatorAtEnd)
{
    string_utils::string_list returned = string_utils::split("bang!", "!");
    CHECK_EQUAL(2U, returned.size());
    CHECK_EQUAL("bang", returned.front()); returned.pop_front();
    CHECK_EQUAL("", returned.front()); returned.pop_front();
}

TEST(SplitOnlyASeparator)
{
    string_utils::string_list returned = string_utils::split("*", "*");
    CHECK_EQUAL(2U, returned.size());
    CHECK_EQUAL("", returned.front()); returned.pop_front();
    CHECK_EQUAL("", returned.front()); returned.pop_front();
}

TEST(SplitNothingBetweenSeparators)
{
    string_utils::string_list returned = string_utils::split("four::dots", ":");
    CHECK_EQUAL(3U, returned.size());
    CHECK_EQUAL("four", returned.front()); returned.pop_front();
    CHECK_EQUAL("", returned.front()); returned.pop_front();
    CHECK_EQUAL("dots", returned.front()); returned.pop_front();
}

TEST(SplitLines)
{
    string_utils::string_list returned = string_utils::splitlines("1. One\n2. Two\n3. Three\n");
    CHECK_EQUAL(3U, returned.size());
    CHECK_EQUAL("1. One", returned.front()); returned.pop_front();
    CHECK_EQUAL("2. Two", returned.front()); returned.pop_front();
    CHECK_EQUAL("3. Three", returned.front()); returned.pop_front();
}

TEST(SplitLinesWithBlankLines)
{
    string_utils::string_list returned = string_utils::splitlines("1. One\n\n2. Two\n\n3. Three\n\n");
    CHECK_EQUAL(6U, returned.size());
    CHECK_EQUAL("1. One", returned.front()); returned.pop_front();
    CHECK_EQUAL("", returned.front()); returned.pop_front();
    CHECK_EQUAL("2. Two", returned.front()); returned.pop_front();
    CHECK_EQUAL("", returned.front()); returned.pop_front();
    CHECK_EQUAL("3. Three", returned.front()); returned.pop_front();
    CHECK_EQUAL("", returned.front()); returned.pop_front();
}

TEST(SplitLinesWithBlankLinesAndCarriageReturns)
{
    string_utils::string_list returned = string_utils::splitlines("1. One\r\n\r\n2. Two\r\n\r\n3. Three\r\n\r\n");
    CHECK_EQUAL(6U, returned.size());
    CHECK_EQUAL("1. One", returned.front()); returned.pop_front();
    CHECK_EQUAL("", returned.front()); returned.pop_front();
    CHECK_EQUAL("2. Two", returned.front()); returned.pop_front();
    CHECK_EQUAL("", returned.front()); returned.pop_front();
    CHECK_EQUAL("3. Three", returned.front()); returned.pop_front();
    CHECK_EQUAL("", returned.front()); returned.pop_front();
}

TEST(SplitLinesWithBlankLinesAndCarriageReturnsWithKeepEnds)
{
    string_utils::string_list returned = string_utils::splitlines("1. One\r\n\r\n2. Two\r\n\r\n3. Three\r\n\r\n", true);
    CHECK_EQUAL(6U, returned.size());
    CHECK_EQUAL("1. One\r\n", returned.front()); returned.pop_front();
    CHECK_EQUAL("\r\n", returned.front()); returned.pop_front();
    CHECK_EQUAL("2. Two\r\n", returned.front()); returned.pop_front();
    CHECK_EQUAL("\r\n", returned.front()); returned.pop_front();
    CHECK_EQUAL("3. Three\r\n", returned.front()); returned.pop_front();
    CHECK_EQUAL("\r\n", returned.front()); returned.pop_front();
}

TEST(StartsWithPositive)
{
    CHECK_EQUAL(true, string_utils::startswith("contraband", "contra"));
}

TEST(StartsWithNegative)
{
    CHECK_EQUAL(false, string_utils::startswith("contraband", "contour"));
}

TEST(StartsWithDealWithExtraLongStrings)
{
    CHECK_EQUAL(false, string_utils::startswith("band", "bandit"));
}

TEST(StartswithStartMidStringPositive)
{
    CHECK_EQUAL(true, string_utils::startswith("abcdef", "def", 3));
}

TEST(StartswithStartMidStringNegative)
{
    CHECK_EQUAL(false, string_utils::startswith("abcdef", "def", 4));
}

TEST(StartswithEndMidStringPositive)
{
    CHECK_EQUAL(true, string_utils::startswith("abcdef", "de", 3, 5));
}

TEST(StartswithEndMidStringNegative)
{
    CHECK_EQUAL(false, string_utils::startswith("abcdef", "def", 3, 4));
}

TEST(StripBothEnds)
{
    CHECK_EQUAL("trimmed", string_utils::strip("    trimmed    "));
}

TEST(SwapCase)
{
    CHECK_EQUAL("s.SWAPCASE() -> STRING", string_utils::swapcase("S.swapcase() -> string"));
}

TEST(TitleCase)
{
    CHECK_EQUAL("Wall Street", string_utils::title("WALL street"));
}

TEST(Translate)
{
    const char* const translation_table =
        "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"
        "DDDDDDDDDD"
        "OOOOOOO"
        "VCCCVCCCVCCCCCVCCCCCVCCCCC"
        "OOOOOO"
        "VCCCVCCCVCCCCCVCCCCCVCCCCC"
        "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO"
        "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO";
    CHECK_EQUAL("VCVCCCVCCODDDD", string_utils::translate("APassword!6969", translation_table));
}

TEST(TranslateAndDeleteChars)
{
    std::string translation_table(256, '_');
    std::string delete_chars("?!");
    CHECK_EQUAL("______", string_utils::translate("xxx!?xxx", translation_table, delete_chars));
}

TEST(TranslateThrowsWhenTableIsWrongSize)
{
    CHECK_THROW(string_utils::translate("Some String", "Small Table"), string_utils::value_error);
}

TEST(TranslateThrowsMessageWhenTableIsWrongSize)
{
    try
    {
        string_utils::translate("Some String", "Small Table");
    }
    catch (const string_utils::value_error& e)
    {
        CHECK_EQUAL("translation table must be 256 characters long", e.what());
    }
}

TEST(Upper)
{
    CHECK_EQUAL("UPPERCASE", string_utils::upper("uppercase"));
}

TEST(ZeroFill)
{
    CHECK_EQUAL("00001", string_utils::zfill("1", 5));
}

TEST(ZeroFillDoesNotTruncate)
{
    CHECK_EQUAL("123456", string_utils::zfill("123456", 5));
}

int main()
{
    return UnitTest::RunAllTests();
}
