/**
    @file
    @author  Alexander Sherikov

    @copyright 2024 Alexander Sherikov, Licensed under the Apache License,
    Version 2.0. (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#pragma once

#include <memory>
#include <locale>
#include <algorithm>
#include <ostream>


namespace numdata
{
    namespace impl
    {
        class Formatter;
    };


    class Facet : public std::num_put<char>
    {
    protected:
        using Parent = std::num_put<char>;

    protected:
        std::shared_ptr<impl::Formatter> formatter_;

    public:
        Facet(std::size_t refs = 0);

    protected:
        virtual Parent::iter_type do_put(Parent::iter_type s, std::ios_base &f, Parent::char_type fill, double v) const override;
    };


    class On
    {
    };


    class Off
    {
    };


    std::ostream &operator<<(std::ostream &s, const On &);
    std::ostream &operator<<(std::ostream &s, const Off &);
}  // namespace numdata
