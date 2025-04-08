#pragma once
#include <functional>
#include <string>
#include <tuple>
#include <variant>

#define NLOHMANN_JSON_NOEXCEPTION

#include <external/json/single_include/nlohmann/json.hpp>

using json = nlohmann::json;

namespace {
    struct ErrorData;
    struct ErrorSub;

    struct Error {
        enum class Type { InvalidSize, InvalidType, SubError };

        std::variant<ErrorData, ErrorSub> error;

        Error(Type type, std::string& msg) : error(ErrorData(msg, type)) {
        }

        Error(Error& err, std::string& msg) : error(ErrorSub(msg, err)) {
        }

        template <typename E, typename A>
        Error invalidSize(E expected, A actual) {
            std::string msg =
                "Expected " + std::to_string(expected) + ", got " + std::to_string(actual);
            return Error(Type::InvalidSize, msg);
        }
    };

    struct ErrorData {
        Error::Type type;
        std::string message;

        std::string to_string() const {
            switch (type) {
            case Error::Type::InvalidSize:
                return "Invalid size: " + message;
            case Error::Type::InvalidType:
                return "Invalid type: " + message;
            default:
                return "Unknown error: " + message;
            }
        }

        ErrorData(std::string& msg, Error::Type type) : message(msg), type(type) {
        }
    };

    struct ErrorSub {
        Error& error;
        std::string message;

        ErrorSub(std::string& msg, Error& err) : message(msg), error(err) {
        }
    };
}; // namespace
