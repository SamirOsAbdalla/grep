#include <iostream>
#include <string>

int match_pattern(const std::string &regexp, const std::string &text);
bool match_character_group(const std::string &regexp, const char &text)
{
    for (auto c : regexp)
    {
        if (c == text)
        {
            return true;
        }
    }

    return false;
}

bool matchplus(char c, const std::string &regexp, const std::string &text)
{

    std::string tmp = text;

    while (tmp.length() > 0 && tmp[0] == c)
    {

        if (match_pattern(regexp, tmp))
        {
            return true;
        }

        tmp = tmp.substr(1);
    }
    return 0;
}
int match_pattern(const std::string &regexp, const std::string &text)
{

    if (regexp.size() == 0)
    {

        return 1;
    }

    if (regexp.size() > 1 && regexp[1] == '+')
    {
        return matchplus(regexp[0], regexp.substr(0, 1) + regexp.substr(2), text);
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
    else if (regexp[0] == '$' and regexp.length() == 1)
    {
        return text.length() == 0;
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
            if (!match_character_group(regexp.substr(2, first_closing_bracket_pos - 1), text[0]))
            {
                return match_pattern(regexp.substr(first_closing_bracket_pos + 1), text.substr(1));
            }

            return 0;
        }

        if (match_character_group(regexp.substr(1, first_closing_bracket_pos - 1), text[0]))
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

    // return match_pattern(regexp, text.substr(1));
    return 0;
}

int match(const std::string &regexp, std::string &text)
{

    // We need this initial check because the pattern must come at the beginning of the text
    if (regexp[0] == '^')
    {
        return match_pattern(regexp.substr(1), text);
    }
    else if (regexp[0] == '+')
    {
        throw std::runtime_error("invalid starting operator");
    }

    int index = 0;
    do
    {

        if (match_pattern(regexp, text))
        {
            return 1;
        }
        text = text.substr(1);
    } while (text != "");

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
            printf("Match\n");
            return 0;
        }
        else
        {
            printf("No Match\n");
            return 1;
        }
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
