#include "HW.hpp"
#include <unistd.h>

int main()
{
    MyLittleTrie book {"o", "a", "b", "book", "boost", "booking", "bo", "laptop", "boo", "cat", "catty",
    "lord", "of", "the", "rings", "stalker", "string", "dragon", "fly", "dragonfly"};
    
    std::cout  << "\033[32mEnter a prefix or enter 42 to exit\033[0m" << std::endl;
    std::string pref;
    while (true) {
        std::getline(std::cin, pref);
        try {
            if (int exit = std::stoi(pref) == 42) {
                break;
            }
        } catch (std::invalid_argument const& ex)
        {
            std::cout  << "\033[32myour input: \033[0m" << pref << std::endl;
            book.searchByPref(pref);
            std::cout << std::endl;
        }
    }
    std::cout  << "\033[32mBy!\033[0m" << pref << std::endl;
    return 0;
}