#ifndef TP_FINAL_ERRORS_H
#define TP_FINAL_ERRORS_H

#include <stdexcept>
#include <string>

namespace engine {
struct BadParams: public std::runtime_error {
    BadParams(): std::runtime_error("Bad parameters") {}
    explicit BadParams(const std::string& message): std::runtime_error(message) {}
};

struct FileNotFound: public std::runtime_error {
    FileNotFound(): std::runtime_error("Inexistent file") {}
    explicit FileNotFound(const std::string& message): std::runtime_error(message) {}
};

struct SDLError: public std::runtime_error {
    SDLError(): std::runtime_error("There was an error in SDL") {}
    explicit SDLError(const std::string& message): std::runtime_error(message) {}
};
}  // namespace engine

#endif  // TP_FINAL_ERRORS_H
