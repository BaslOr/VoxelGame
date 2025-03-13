#pragma once
#include <exception>
#include <string>
#include <stdint.h>
#include <ostream>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Cubes {

    class Error : public std::exception {
    public:
        Error(const std::string& what)
            : _what(what)
        {	}

        inline virtual char const* what() const override {
            return _what.c_str();
        }

    private:
        std::string _what;
    };

    class FailedToOpenFileError : public Error {
    public:
        FailedToOpenFileError(const char* filePath)
            : Error(filePath)
        { }
    };

    class NoAPISelectedError : public Error {
    public:
        NoAPISelectedError()
            : Error("No API is selected!")
        {}
    };

    class APINotSupportedError : public Error {
    public:
        APINotSupportedError(const char* APIType)
            : Error(std::string(APIType) + " is not (fully) supported yet")
        {}
    };

    class VendorAPIInitilizationError : public Error {
    public:
        VendorAPIInitilizationError(const char* APIName)
            : Error("Failed to initialize " + std::string(APIName))
        { }
    };

}
