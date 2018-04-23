#ifndef HEADER_gubg_chai_Regex_hpp_ALREADY_INCLUDED
#define HEADER_gubg_chai_Regex_hpp_ALREADY_INCLUDED

#include <regex>
#include <iostream>

namespace gubg { namespace chai { 

    class Regex
    {
    public:
        Regex() { }
        Regex(const std::string &pattern): pattern_(pattern) { }
        Regex(const Regex &rhs): pattern_(rhs.pattern_) { }

        void assign(const std::string &pattern)
        {
            pattern_ = pattern;
            regex_.assign(pattern_);
        }

        bool matches(const std::string &str) const
        {
            return std::regex_search(str, regex_);
        }

    private:
        std::string pattern_;
        std::regex regex_{pattern_};
    };

} } 

#endif
