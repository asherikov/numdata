/**
    @file
    @author  Alexander Sherikov

    @copyright 2024 Alexander Sherikov, Licensed under the Apache License,
    Version 2.0. (see @ref LICENSE or http://www.apache.org/licenses/LICENSE-2.0)

    @brief
*/

#include <double-conversion/double-to-string.h>

#include "numdata/numdata.h"


namespace numdata::impl
{
    class Formatter
    {
    protected:
        double_conversion::DoubleToStringConverter converter_;


    public:
        Formatter()
          : converter_(
                  double_conversion::DoubleToStringConverter::EMIT_TRAILING_DECIMAL_POINT
                          | double_conversion::DoubleToStringConverter::EMIT_POSITIVE_EXPONENT_SIGN,
                  "inf",
                  "nan",
                  'e',
                  /*decimal_in_shortest_low=*/0,
                  /*decimal_in_shortest_high=*/1,
                  /*max_leading_padding_zeroes_in_precision_mode=*/0,
                  /*max_trailing_padding_zeroes_in_precision_mode=*/0,
                  /*min_exponent_width=*/0)
        {
        }


        template <typename t_Float>
        void put(std::ostreambuf_iterator<char> s, t_Float v) const
        {
            const int buf_size = 32; // double_conversion::DoubleToStringConverter::kBase10MaximalLength + 1;
            char buffer[buf_size];
            double_conversion::StringBuilder builder(buffer, buf_size);

            // Returns true if the conversion succeeds. The conversion always succeeds
            // except when the input value is special and no infinity_symbol or
            // nan_symbol has been given to the constructor.
            converter_.ToShortest(v, &builder);
            // builder.Finalize(); // destroys position information

            std::copy(buffer, buffer + builder.position(), s);
        }
    };
}  // namespace numdata::impl


namespace numdata
{
    Facet::Facet(std::size_t refs) : Parent(refs)
    {
        formatter_ = std::make_shared<impl::Formatter>();
    }


    Facet::Parent::iter_type Facet::do_put(
            Facet::Parent::iter_type s,
            std::ios_base &f,
            Facet::Parent::char_type fill,
            double v) const
    {
        formatter_->put(s, v);
        return (s);
    }


    std::ostream &operator<<(std::ostream &s, const On &)
    {
        if (std::has_facet<std::num_put<char>>(s.getloc()))
        {
            std::locale L(s.getloc(), new Facet());
            s.imbue(L);
        }
        return (s);
    }


    std::ostream &operator<<(std::ostream &s, const Off &)
    {
        if (std::has_facet<Facet>(s.getloc()))
        {
            std::locale L(s.getloc(), new std::num_put<char>());
            s.imbue(L);
        }
        return (s);
    }
}  // namespace numdata
