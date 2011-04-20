#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <cctype>
#include <exception>
#include <limits>

namespace string_utils {

class value_error: public std::exception
{
public:
    value_error(const std::string& reason)
        :reason_(reason)
    {
    }

    virtual ~value_error() throw()
    {
    }

    virtual const char* what() const throw()
    {
        return reason_.c_str();
    }

private:
    const std::string reason_;
};

typedef std::list<std::string> string_list;

const int max_pos = std::numeric_limits<int>::max();
const int max_count = max_pos;

std::string capitalize(std::string copy)
{
    copy[0] = ::toupper(copy[0]);
    return copy;
}

std::string center(const std::string& s, int width, char fill = ' ')
{
    const int padding = width - s.length();
    if (padding > 0)
    {
        const int before = padding / 2;
        const int after = padding - before;
        return std::string(before, fill) + s + std::string(after, fill);
    }
    return s;
}

int count(const std::string& s, const std::string& substring, int start = 0, int end = max_pos)
{
    int count = 0;
    for (int pos = s.find(substring, start);
         start <= pos && pos < end;
         pos = s.find(substring, pos + substring.size()))
    {
        ++count;
    }
    return count;
}

bool endswith(const std::string& s, const std::string& suffix, int start = 0, int end = max_pos)
{
    if (end == max_pos)
    {
        end = s.size();
    }
    const int chars_from_end = s.size() - end;
    return (end - start >= static_cast<int>(suffix.length()))
        && std::equal(suffix.rbegin(), suffix.rend(), s.rbegin() + chars_from_end);
}

std::string expandtabs(const std::string& s, int tabsize = 8)
{
    std::string copy = "";
    int pos_in_line = 0;

    for (std::string::const_iterator current = s.begin(), end = s.end(); current != end; ++current)
    {
        switch (*current)
        {
            case '\n':
            case '\r':
                copy.push_back(*current);
                pos_in_line = 0;
                break;
            case '\t':
                if (tabsize > 0)
                {
                    int fillsize = tabsize - (pos_in_line % tabsize);
                    copy.append(std::string(fillsize, ' '));
                    pos_in_line += fillsize;
                }
                break;
            default:
                copy.push_back(*current);
                ++pos_in_line;
        }
    }
    return copy;
}

int find(const std::string& s, const std::string& substring, int start = 0, int end = max_pos)
{
    int index = s.find(substring, start);
    if (end < index + static_cast<int>(substring.size()))
    {
        index = -1;
    }
    return index;
}

int index(const std::string& s, const std::string& substring, int start = 0, int end = max_pos)
{
    int index = find(s, substring, start, end);
    if (index < 0)
    {
        throw value_error("substring not found");
    }
    return index;
}

bool isalnum(const std::string& s)
{
    return !s.empty()
        && std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun(::isalnum))) == s.end();
}

bool isalpha(const std::string& s)
{
    return !s.empty()
        && std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun(::isalpha))) == s.end();
}

bool isdigit(const std::string& s)
{
    return !s.empty()
        && std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun(::isdigit))) == s.end();
}

bool islower(const std::string& s)
{
    return !s.empty()
        && std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun(::islower))) == s.end();
}

bool isspace(const std::string& s)
{
    return !s.empty()
        && std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun(::isspace))) == s.end();
}

bool istitle(const std::string& s)
{
    bool follows_cased = false;
    bool has_uppercase = false;
    bool istitle = true;

    for (std::string::const_iterator current = s.begin(), end = s.end(); istitle && current != end; ++current)
    {
        if (::islower(*current))
        {
            if (!follows_cased)
            {
                istitle = false;
            }
            follows_cased = true;
        }
        else if (::isupper(*current))
        {
            if (follows_cased)
            {
                istitle = false;
            }
            follows_cased = true;
            has_uppercase = true;
        }
        else
        {
            follows_cased = false;
        }
    }
    return istitle && has_uppercase;
}

bool isupper(const std::string& s)
{
    return !s.empty()
        && std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun(::isupper))) == s.end();
}

template<typename C>
std::string join(const std::string& s, C container)
{
    std::ostringstream joined;
    typename C::const_iterator current = container.begin(), end = container.end();
    joined << *current;
    for (++current; current != end; ++current)
    {
        joined << s;
        joined << *current;
    }

    return joined.str();
}

template<>
std::string join(const std::string& s, const char* buffer)
{
    return join(s, std::string(buffer));
}

std::string ljust(std::string copy, int width, char fillchar = ' ')
{
    int fillsize = width - copy.length();
    if (fillsize > 0)
    {
        copy.append(std::string(fillsize, fillchar));
    }
    return copy;
}

std::string lower(const std::string& s)
{
    std::string lowercased;
    std::transform(s.begin(), s.end(), back_inserter(lowercased), ::tolower);
    return lowercased;
}

std::string lstrip(const std::string& s, const char* chars = " \t\r\n")
{
    std::string::size_type begin = s.find_first_not_of(chars);
    if (begin == std::string::npos)
    {
        return "";
    }
    return std::string(s, begin);
}

std::string rstrip(const std::string& s, const char* chars = " \t\r\n")
{
    std::string::size_type end = s.find_last_not_of(chars);
    return std::string(s, 0, end + 1);
}

std::string strip(const std::string& s)
{
    return lstrip(rstrip(s));
}

struct partition_t
{
    std::string head, sep, tail;
};

partition_t partition_helper(const std::string& s, const std::string& sep, const int pos)
{
    if (pos < 0)
    {
        partition_t partitioned = { s, "", "" };
        return partitioned;
    }

    partition_t partitioned = {
        std::string(s, 0, pos),
        sep,
        std::string(s, pos + sep.length())
    };
    return partitioned;
}

partition_t partition(const std::string& s, const std::string& sep)
{
    return partition_helper(s, sep, s.find(sep));
}

std::string replace(std::string copy, const std::string& old, const std::string& with, int count = max_count)
{
    const int old_length = old.length(), with_length = with.length();
    for (int pos = copy.find(old);
         pos >= 0 && count > 0;
         pos = copy.find(old, pos + with_length))
    {
        copy.replace(pos, old_length, with);
        --count;
    }
    return copy;
}

int rfind(const std::string& s, const std::string& substring, int start = 0, int end = max_pos)
{
    int pos = s.rfind(substring, end);
    if (start > pos
        || pos > end - static_cast<int>(substring.length()))
    {
        pos = -1;
    }
    return pos;
}

int rindex(const std::string& s, const std::string& substring, int start = 0, int end = max_pos)
{
    int index = rfind(s, substring, start, end);
    if (index < 0)
    {
        throw value_error("substring not found");
    }
    return index;
}

std::string rjust(const std::string& s, int width, char fillchar = ' ')
{
    std::string out;
    int fillsize = width - s.length();
    if (fillsize > 0)
    {
        out = std::string(fillsize, fillchar);
    }
    return out + s;;
}

partition_t rpartition(const std::string& s, const std::string& sep)
{
    return partition_helper(s, sep, s.rfind(sep));
}

string_list split_helper(const std::string& s)
{
    string_list split;
    const std::string stripped = strip(s);
    std::string::const_iterator end_of_space = stripped.begin();
    std::string::const_iterator end_of_string = stripped.end();
    std::string::const_iterator next_space = std::find_if(stripped.begin(), end_of_string, std::ptr_fun(::isspace));
    for (;
         next_space != end_of_string;
         next_space = std::find_if(end_of_space, end_of_string, std::ptr_fun(::isspace)))
    {
        split.push_back(std::string(end_of_space, next_space));
        end_of_space = std::find_if(next_space, end_of_string, std::not1(std::ptr_fun(::isspace)));
    }
    if (end_of_space != next_space)
    {
        split.push_back(std::string(end_of_space, next_space));
    }
    return split;
}

string_list rsplit(const std::string& s)
{
    return split_helper(s);
}

string_list rsplit(const std::string& s, const std::string& sep, int max_split = max_count)
{
    if (sep.empty())
    {
        throw value_error("empty separator");
    }

    string_list split;
    const int sep_length = sep.length();
    int last_pos = s.length();
    int pos = s.rfind(sep);
    for (;
         pos > 0 && max_split > 0;
         pos = s.rfind(sep, last_pos - 1))
    {
        split.push_front(std::string(s, pos + sep_length, last_pos - pos - sep_length));
        last_pos = pos;
        --max_split;
    }

    if (0 == pos)
    {
        split.push_front(std::string(s, sep_length, last_pos));
        split.push_front("");
    }
    else
    {
        split.push_front(std::string(s, 0, last_pos));
    }
    return split;
}

string_list split(const std::string& s)
{
    return split_helper(s);
}

string_list split(const std::string& s, const std::string& sep, int max_split = max_count)
{
    if (sep.empty())
    {
        throw value_error("empty separator");
    }

    string_list split;
    const int sep_length = sep.length();
    int last_pos = 0;
    for (int pos = s.find(sep);
         pos >= 0 && max_split > 0;
         pos = s.find(sep, last_pos))
    {
        split.push_back(std::string(s, last_pos, pos - last_pos));
        last_pos = pos + sep_length;
        --max_split;
    }
    if (0 == last_pos)
    {
        split.push_back("");
    }
    else
    {
        split.push_back(std::string(s, last_pos));
    }
    return split;
}

bool isnewline(char ch)
{
    return '\r' == ch || '\n' == ch;
}

string_list splitlines(const std::string& s, bool keepends = false)
{
    string_list split;
    std::string::const_iterator start_of_line = s.begin();
    std::string::const_iterator end_of_line = s.end();
    std::string::const_iterator new_line = std::find_if(s.begin(), end_of_line, std::ptr_fun(isnewline));
    for (;
         new_line != end_of_line;
         new_line = std::find_if(start_of_line, end_of_line, std::ptr_fun(isnewline)))
    {
        int newline_size = 1;
        if ('\r' == *new_line && '\n' == *(new_line + 1))
        {
            newline_size = 2;
        }
        split.push_back(std::string(start_of_line, new_line + (keepends ? newline_size : 0)));
        start_of_line = new_line + newline_size;
    }
    return split;
}

bool startswith(const std::string& s, const std::string& prefix, int start = 0, int end = max_pos)
{
    return (end - start >= static_cast<int>(prefix.length()))
        && std::equal(prefix.begin(), prefix.end(), s.begin() + start);
}

char swapcase_helper(char ch)
{
    if (::islower(ch))
    {
        ch = ::toupper(ch);
    }
    else if (::isupper(ch))
    {
        ch = ::tolower(ch);
    }
    return ch;
}

std::string swapcase(const std::string& s)
{
    std::string swapcased;
    std::transform(s.begin(), s.end(), back_inserter(swapcased), swapcase_helper);
    return swapcased;
}

struct titlecase_helper
{
    titlecase_helper()
        :uppercase_next_(true)
    {
    }

    char operator()(const char& ch)
    {
        char out = ch;
        if (::isalpha(ch))
        {
            if (uppercase_next_)
            {
                out = ::toupper(ch);
                uppercase_next_ = false;
            }
            else
            {
                out = ::tolower(ch);
            }
        }
        else
        {
            uppercase_next_ = true;
        }
        return out;
    }

    bool uppercase_next_;
};

std::string title(const std::string& s)
{
    std::string titlecased;
    std::transform(s.begin(), s.end(), back_inserter(titlecased), titlecase_helper());
    return titlecased;
}

std::string translate(const std::string& s, const std::string& translation_table, const std::string& delete_chars = "")
{
    if (translation_table.length() != 256)
    {
        throw value_error("translation table must be 256 characters long");
    }

    std::string out;
    for (std::string::const_iterator current = s.begin(), end = s.end(); current != end; ++current)
    {
        if (std::find(delete_chars.begin(), delete_chars.end(), *current) == delete_chars.end())
        {
            out.push_back(translation_table[*current]);
        }
    }
    return out;
}

std::string upper(const std::string& s)
{
    std::string uppercased;
    std::transform(s.begin(), s.end(), back_inserter(uppercased), ::toupper);
    return uppercased;
}

std::string zfill(const std::string& s, int width)
{
    return rjust(s, width, '0');
}

}
#endif// STRING_UTILS_H
