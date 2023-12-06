#include <iostream>
#include <string>

bool betweenBrackets(const std::string &pattern)
{
    return pattern.size() > 1 && pattern[0] == '[' && pattern[pattern.size() - 1] == ']';
}

bool doesContainDigits(const std::string &input_line, const std::string &pattern)
{
    for (auto c : input_line)
    {
        if (isdigit(c))
        {
            return true;
        }
    }

    return false;
}

bool doesContainAlphaNum(const std::string &input_line, const std::string &pattern)
{
    for (auto c : input_line)
    {
        if (isalnum(c))
        {
            return true;
        }
    }

    return false;
}

bool isNotInGroup(char inputChar, const std::string &group)
{
    // Loop over each character in the group and return false if inputChar is found.
    for (char c : group)
    {
        if (inputChar == c)
        {
            return false;
        }
    }
    return true;
}

bool match_pattern(const std::string &input_line, const std::string &pattern)
{
    if (pattern.length() == 1)
    {
        return input_line.find(pattern) != std::string::npos;
    }
    else if (pattern == "\\d")
    {
        return doesContainDigits(input_line, pattern);
    }
    else if (pattern == "\\w")
    {
        return doesContainAlphaNum(input_line, pattern);
    }
    else if (betweenBrackets(pattern))
    {
        if (pattern[1] == '^')
        {
            int index = 2;
            while (index < pattern.size() && pattern[index] != ']')
            {
                if (!isNotInGroup(pattern[index], input_line))
                {
                    return false;
                }
                index += 1;
            }

            return true;
        }
        else
        {
            for (auto c : pattern)
            {
                if (input_line.find(c) != std::string::npos)
                {
                    return true;
                }
            }
            return false;
        }
    }
    else
    {
        throw std::runtime_error("Unhandled pattern " + pattern);
    }
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
        if (match_pattern(input_line, pattern))
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
