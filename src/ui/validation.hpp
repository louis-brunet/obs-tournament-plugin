#pragma once

#include "src/ui/dialogs/error-dialog.hpp"
#include <cstdio>
#include <stdexcept>
#include <vector>

class Validation {
public:
    template<typename... FormatArgs>
    static bool validate(bool isValid, const char *errorFormat,
                         FormatArgs... errorFormatArgs)
    {
        if (!isValid) {
            auto messageSize =
                std::snprintf(nullptr, 0, errorFormat, errorFormatArgs...);
            if (messageSize < 0) {
                throw std::runtime_error(
                    "[Validation::validate] messageSize is negative");
            }
            std::vector<char> buf(messageSize +
                                  1); // NOTE: +1 for null terminator
            std::sprintf(buf.data(), errorFormat,
                         errorFormatArgs...); // certain to fit

            auto errorDialog = new ErrorDialog(nullptr, buf.data());
            errorDialog->show();

            return false;
        }
        return true;
    }
};
