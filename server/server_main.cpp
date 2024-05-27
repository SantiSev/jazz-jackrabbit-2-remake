#include <iostream>

int main(int argc, const char* argv[]) {
    try {
        int output = -1;
        const char* servname = nullptr;

        if (argc == 2) {
            servname = argv[1];
        } else {
            std::cerr << "Bad program call. Expected " << argv[0] << " <servname>\n";
            return output;
        }

        std::cout << "Hello, server: " << servname << " World!" << std::endl;

        output = 0;
        return output;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
