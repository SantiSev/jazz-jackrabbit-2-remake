#ifndef TP_FINAL_ERRORS_H
#define TP_FINAL_ERRORS_H

#include <stdexcept>
#include <string>

struct BadParams: public std::runtime_error {
    BadParams(): std::runtime_error("Bad parameters") {}
    explicit BadParams(const std::string& message): std::runtime_error(message) {}
};

struct FileDoesNotExist: public std::runtime_error {
    FileDoesNotExist(): std::runtime_error("Inexistent file") {}
    explicit FileDoesNotExist(const std::string& message): std::runtime_error(message) {}
};

#endif  // TP_FINAL_ERRORS_H
