#include <iostream>
#include <string>

// bool doesContainDigits(const std::string &input_line, const std::string &pattern)
// {
//     for (auto c : input_line)
//     {
//         if (isdigit(c))
//         {
//             return true;
//         }
//     }

//     return false;
// }

// bool doesContainAlphaNum(const std::string &input_line, const std::string &pattern)
// {
//     for (auto c : input_line)
//     {
//         if (isalnum(c))
//         {
//             return true;
//         }
//     }

//     return false;
// }

// bool isNotInGroup(char inputChar, const std::string &group)
// {
//     // Loop over each character in the group and return false if inputChar is found.
//     for (char c : group)
//     {
//         if (inputChar == c)
//         {
//             return false;
//         }
//     }
//     return true;
// }

// bool match_pattern(const std::string &input_line, const std::string &pattern)
// {
//     if (pattern.length() == 1)
//     {
//         return input_line.find(pattern) != std::string::npos;
//     }
//     else if (pattern == "\\d")
//     {
//         return doesContainDigits(input_line, pattern);
//     }
//     else if (pattern == "\\w")
//     {
//         return doesContainAlphaNum(input_line, pattern);
//     }
//     else if (betweenBrackets(pattern))
//     {
//         return matchCharacterGroup(input_line, pattern.substr(1, pattern.size() - 2));
//     }
//     else
//     {
//         throw std::runtime_error("Unhandled pattern " + pattern);
//     }
// }
// bool regexp_between_brackets(const std::string &regexp)
// {
//     return regexp.size() > 1 && regexp[0] == '[' && regexp[regexp.size() - 1] == ']';
// }

bool match_character_group(const std::string &regexp, const std::string &text)
{
    return text.find_first_of(regexp) != std::string::npos;
}

int match_pattern(const std::string &regexp, const std::string &text)
{

    if (regexp.size() == 0)
    {

        return 1;
    }
    if (text.size() == 0)
    {
        return 0;
    }

    if (regexp.substr(0, 2) == "\\d")
    {
        if (isdigit(text[0]))
        {
            return match_pattern(regexp.substr(2), text.substr(1));
        }
        return match_pattern(regexp, text.substr(1));
    }
    else if (regexp.substr(0, 2) == "\\w")
    {
        if (isalnum(text[0]))
        {
            return match_pattern(regexp.substr(2), text.substr(1));
        }
        return match_pattern(regexp, text.substr(1));
    }
    else if (regexp[0] == '[')
    {
        auto first_closing_bracket_pos = regexp.find("]");
        if (first_closing_bracket_pos == std::string::npos)
        {
            throw std::runtime_error("bad brackets bub");
        }

        bool are_brackets_negated = (regexp.substr(0, 2) == "[^");
        if (are_brackets_negated)
        {
            if (!match_character_group(regexp.substr(2, first_closing_bracket_pos - 1), text))
            {
                return match_pattern(regexp.substr(first_closing_bracket_pos + 1), text.substr(1));
            }

            return 0;
        }

        if (match_character_group(regexp.substr(1, first_closing_bracket_pos - 1), text))
        {
            return match_pattern(regexp.substr(first_closing_bracket_pos + 1), text.substr(1));
        }
        else
        {
            return 0;
        }
    }

    if (regexp[0] == text[0])
    {
        return match_pattern(regexp.substr(1), text.substr(1));
    }
    return match_pattern(regexp, text.substr(1));
}

int match(const std::string &regexp, std::string &text)
{
    int index = 0;

    do
    {

        if (match_pattern(regexp, text))
        {
            printf("1\n");
            return 1;
        }
        text = text.substr(1);
    } while (text != "");

    printf("0\n");
    return 0;
}

int main(int argc, char *argv[])
{
    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cout << "Logs from your program will appear here" << std::endl;

    if (argc != 3)
    {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    if (flag != "-E")
    {
        std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }

    std::string input_line;
    std::getline(std::cin, input_line);

    try
    {
        if (match(pattern, input_line))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
