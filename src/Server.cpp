#include <iostream>
#include <string>

bool match_pattern(const std::string &input_line, const std::string &pattern)
{
    if (pattern.length() == 1)
    {

        return input_line.find(pattern) != std::string::npos;
    }
    else if (pattern == "\\d")
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
    else if (pattern == "\\w")
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
