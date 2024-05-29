#ifndef TP_FINAL_ERRORS_H
#define TP_FINAL_ERRORS_H

#include <stdexcept>
#include <string>

struct BadParamsErr: public std::runtime_error {
    BadParamsErr(): std::runtime_error("Bad parameters") {}
    explicit BadParamsErr(const std::string& message): std::runtime_error(message) {}
};

#endif  // TP_FINAL_ERRORS_H
