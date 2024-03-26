Introduction
============

If you are annoyed by `std::setprecision(std::numeric_limits<long double>::digits10 + 1)`
this tool may be for you. It is in a draft state and should be used with care.

The purpose of `numdata` is to print floating point numbers to streams in a
better way than it is possible using standard tools. It is based on
`std::locale::facet` mechanism
(<https://en.cppreference.com/w/cpp/locale/locale/facet>) and Google
`double-conversion` library (<https://github.com/google/double-conversion>).


Features
========

- Prints floating point numbers in minimal representation that allows to parse
  them without ambiguity.
- Prints trailing `.` for integer values reducing value type ambiguity in the
  output.
- Does not produce excessive 0 values.
- Non-invasive.
- May actually work faster than standard output
  (<https://github.com/miloyip/dtoa-benchmark>), not verified.


Usage
=====

```
#include <numdata/numdata.h>

...
double a = 0.1;
std::cout << numdata::On;
std::cout << a;
std::cout << numdata::Off;
...
```


Output example
==============

See `test/demo.cpp`

```
numdata:
 0.
 inf
 nan
 2.2250738585072014e-308
 1.7976931348623157e+308
 1.
 1e+11
 1.111111e-1
 1e-15
 3.000020000001e-1

default:
 0
 inf
 nan
 2.22507e-308
 1.79769e+308
 1
 1e+11
 0.111111
 1e-15
 0.300002

std::scientific:
 0.000000e+00
 inf
 nan
 2.225074e-308
 1.797693e+308
 1.000000e+00
 1.000000e+11
 1.111111e-01
 1.000000e-15
 3.000020e-01

std::setprecision:
 0
 inf
 nan
 2.225073858507201383e-308
 1.797693134862315708e+308
 1
 100000000000
 0.1111111000000000043
 1.000000000000000078e-15
 0.300002000000100022

std::showpoint + std::setprecision:
 0.000000000000000000
 inf
 nan
 2.225073858507201383e-308
 1.797693134862315708e+308
 1.000000000000000000
 100000000000.0000000
 0.1111111000000000043
 1.000000000000000078e-15
 0.3000020000001000220
```


Notes
=====

- Facet inherits from `std::num_put` which lacks specialization for `float`
  type, i.e., such values are converted to `double`.
- `double-conversion` is not the fastest library, see, e.g.,
  <https://github.com/jk-jeon/dragonbox>, but others generally lack features
  required by `numdata`.

