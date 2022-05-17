// Section 20
// Challenge 4
// Identifying palindrome strings using a stack and queue
#include <cctype>
#include <stack>
#include <queue>
#include <iostream>
#include <string>
#include <iomanip>

template<typename T>
void fill(T& t, std::string s)
{
    for(const auto& e:s)
        if(isalpha(e))
            t.push(toupper(e));
}
bool is_palindrome(const std::string& s)
{
    std::stack<char, std::deque<char>> s1;
    std::queue<char, std::deque<char>> q1;
    fill(s1, s);
    fill(q1, s);
    while (!s1.empty() || !q1.empty())
    {
        if (s1.top() != q1.front())
            return false;
        s1.pop();
        q1.pop();
    }
    // You must implement this function.
    // Since we are learning the STL - use a stack and a queue to solve the problem.
    return true;
}

int main()
{
    std::vector<std::string> test_strings{ "a", "aa", "aba", "abba", "abbcbba", "ab", "abc", "radar", "bob", "ana",
        "avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
        "A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!", "This is a palindrome", "palindrome" };

    std::cout << std::boolalpha;
    std::cout << std::setw(8) << std::left << "Result" << "String" << std::endl;
    for (const auto& s : test_strings) {
        std::cout << std::setw(8) << std::left << is_palindrome(s) << s << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

