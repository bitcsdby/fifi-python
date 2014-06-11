// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <boost/python.hpp>
#include <boost/python/register_ptr_to_python.hpp>
#include <boost/python/docstring_options.hpp>

#include <fifi/binary.hpp>
#include <fifi/binary4.hpp>
#include <fifi/binary8.hpp>
#include <fifi/binary16.hpp>

#include <fifi/extended_log_table.hpp>
#include <fifi/full_table.hpp>
#include <fifi/log_table.hpp>
#include <fifi/optimal_prime.hpp>
#include <fifi/simple_online.hpp>

#include "finite_field.hpp"

namespace fifi_python
{
    BOOST_PYTHON_MODULE(fifi)
    {
        using namespace fifi;

        boost::python::docstring_options doc_options;
        doc_options.disable_signatures();

        finite_field<extended_log_table, binary16>(
            "extended_log_table", "binary16");
        finite_field<extended_log_table, binary4>(
            "extended_log_table", "binary4");
        finite_field<extended_log_table, binary8>(
            "extended_log_table", "binary8");

        finite_field<full_table, binary4>("full_table", "binary4");
        finite_field<full_table, binary8>("full_table", "binary8");

        finite_field<log_table, binary16>("log_table", "binary16");
        finite_field<log_table, binary4>("log_table", "binary4");
        finite_field<log_table, binary8>("log_table", "binary8");

        finite_field<optimal_prime, prime2325>("optimal_prime", "prime2325");

        finite_field<simple_online, binary16>("simple_online", "binary16");
        finite_field<simple_online, binary4>("simple_online", "binary4");
        finite_field<simple_online, binary8>("simple_online", "binary8");
        finite_field<simple_online, binary>("simple_online", "binary");
    }
}
