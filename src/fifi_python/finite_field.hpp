// Copyright Steinwurf ApS 2011-2014.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <functional>

#include <boost/python/args.hpp>

#include <fifi/fifi_utils.hpp>

#include <Python.h>

namespace fifi_python
{
    PyObject* to_python_buffer(const std::string& item)
    {
        #if PY_MAJOR_VERSION >= 3
        return PyBytes_FromStringAndSize(item.c_str(), item.length());
        #else
        return PyString_FromStringAndSize(item.c_str(), item.length());
        #endif
    }

    template<class FiniteField, class Function>
    PyObject* region_arithmetic(const FiniteField& finite_field,
        Function arithmetic, const std::string& dest, const std::string& src)
    {
        typedef typename FiniteField::value_type value_type;
        typedef typename FiniteField::field_type field_type;

        assert(dest.length() == src.length());

        std::string dest_copy = dest;
        uint32_t length = fifi::size_to_length<field_type>(dest_copy.length());
        arithmetic(finite_field, (value_type*)dest_copy.c_str(),
            (value_type*)src.c_str(), length);
        return to_python_buffer(dest_copy);
    }

    template<class FiniteField>
    PyObject* region_add(const FiniteField& finite_field,
        const std::string& dest, const std::string& src)
    {
        return region_arithmetic(finite_field,
            std::mem_fn(&FiniteField::region_add), dest, src);
    }

    template<class FiniteField>
    PyObject* region_subtract(const FiniteField& finite_field,
        const std::string& dest, const std::string& src)
    {
        return region_arithmetic(finite_field,
            std::mem_fn(&FiniteField::region_subtract), dest, src);
    }

    template<class FiniteField>
    PyObject* region_multiply(const FiniteField& finite_field,
        const std::string& dest, const std::string& src)
    {
        return region_arithmetic(finite_field,
            std::mem_fn(&FiniteField::region_multiply), dest, src);
    }

    template<class FiniteField>
    PyObject* region_divide(const FiniteField& finite_field,
        const std::string& dest, const std::string& src)
    {
        return region_arithmetic(finite_field,
            std::mem_fn(&FiniteField::region_divide), dest, src);
    }

    template<class FiniteField>
    PyObject* region_multiply_constant(const FiniteField& finite_field,
        const std::string& dest, typename FiniteField::value_type constant)
    {
        typedef typename FiniteField::value_type value_type;
        typedef typename FiniteField::field_type field_type;

        std::string dest_copy = dest;
        uint32_t length = fifi::size_to_length<field_type>(dest_copy.length());

        finite_field.region_multiply_constant((value_type*)dest_copy.c_str(),
            constant, length);
        return to_python_buffer(dest_copy);
    }

    template<class FiniteField>
    PyObject* region_multiply_add(const FiniteField& finite_field,
        const std::string& dest, const std::string& src,
        typename FiniteField::value_type constant)
    {
        typedef typename FiniteField::value_type value_type;
        typedef typename FiniteField::field_type field_type;

        std::string dest_copy = dest;
        uint32_t length = fifi::size_to_length<field_type>(dest_copy.length());

        finite_field.region_multiply_add((value_type*)dest_copy.c_str(),
            (value_type*)src.c_str(), constant, length);
        return to_python_buffer(dest_copy);
    }

    template<class FiniteField>
    PyObject* region_multiply_subtract(const FiniteField& finite_field,
        const std::string& dest, const std::string& src,
        typename FiniteField::value_type constant)
    {
        typedef typename FiniteField::value_type value_type;
        typedef typename FiniteField::field_type field_type;

        std::string dest_copy = dest;
        uint32_t length = fifi::size_to_length<field_type>(dest_copy.length());

        finite_field.region_multiply_subtract((value_type*)dest_copy.c_str(),
            (value_type*)src.c_str(), constant, length);
        return to_python_buffer(dest_copy);
    }



    template<template<class> class Arithmetic, class Field>
    void finite_field(const std::string& arithmetic, const std::string& field)
    {
        using namespace boost::python;

        std::string name = arithmetic + std::string("_") + field;

        typedef typename Field::value_type value_type;
        typedef Arithmetic<Field> finite_field_type;

        class_<finite_field_type>(name.c_str(), "A finite field implementation")
        .def("add", &finite_field_type::add, args("a", "b"),
            "Returns the sum of two field elements.\n\n"
            "\t:param a: The augend.\n"
            "\t:param b: The addend.\n"
            "\t:returns: The sum of a and b.\n")
        .def("subtract", &finite_field_type::subtract, args("a", "b"),
            "Returns the difference of two field elements.\n\n"
            "\t:param a: The minuend.\n"
            "\t:param b: The subtrahend.\n"
            "\t:return: The difference of a and b.\n")
        .def("multiply", &finite_field_type::multiply, args("a", "b"),
            "Returns the product of two field elements.\n\n"
            "\t:param a: The multiplicand.\n"
            "\t:param b: The multiplier.\n"
            "\t:return: The product of a and b.\n")
        .def("divide", &finite_field_type::divide, args("a", "b"),
            "Returns the quotient of two field elements.\n\n"
            "\t:param a: The numerator.\n"
            "\t:param b: The denominator.\n"
            "\t:return: The quotient of a and b.\n")
        .def("invert", &finite_field_type::invert, arg("a"),
            "Returns inverse of a field element.\n\n"
            "\t:param a: Element to invert.\n"
            "\t:return: The inverse of the field element.")

        .def("packed_add", &finite_field_type::packed_add, args("a", "b"),
            "Returns the sum of two field elements. If the field's value type "
            "can represent multiple elements it is assumed that multiple field "
            "elements are stored in the operands, e.g., that 8 field elements "
            "are stored in a byte-sized value type of a binary field.\n\n"
            "\t:param: a The augend(s).\n"
            "\t:param b: The addend(s).\n"
            "\t:return: The sum(s) of a and b.\n")
        .def("packed_subtract", &finite_field_type::packed_subtract,
            args("a", "b"),
            "Returns the difference of two field elements. If the field's "
            "value type can represent multiple elements it is assumed that "
            "multiple field elements are stored in the operands, e.g., that 8 "
            "field elements are stored in a byte-sized value type of a binary "
            "field.\n\n"
            "\t:param: a The minuend(s).\n"
            "\t:param b: The subtrahend(s).\n"
            "\t:return: The difference(s) of a and b.\n")
        .def("packed_multiply", &finite_field_type::packed_multiply,
            args("a", "b"),
            "Returns the product of two field elements. If the field's value "
            "type can represent multiple elements it is assumed that multiple "
            "field elements are stored in the operands, e.g., that 8 field "
            "elements are stored in a byte-sized value type of a binary "
            "field.\n\n"
            "\t:param: a The multiplicand(s).\n"
            "\t:param b: The multiplier(s).\n"
            "\t:return: The product(s) of a and b.\n")
        .def("packed_divide", &finite_field_type::packed_divide, args("a", "b"),
            "Returns the quotient of two field elements. If the field's value "
            "type can represent multiple elements it is assumed that multiple "
            "field elements are stored in the operands, e.g., that 8 field "
            "elements are stored in a byte-sized value type of a binary "
            "field.\n\n"
            "\t:param: a The numerator(s).\n"
            "\t:param b: The denominator(s).\n"
            "\t:return: The quotient(s) of a and b.\n")
        .def("packed_invert", &finite_field_type::packed_invert, arg("a"),
            "Returns inverse of a field element. If the field's value type can "
            "represent multiple elements it is assumed that multiple field "
            "elements are stored in the operand, e.g., that 8 field elements "
            "are stored in a byte-sized value type of a binary field.\n\n"
            "\t:param a: Element(s) to invert.\n"
            "\t:return: The inverse of the field element(s).\n")

        .def("region_add", &region_add<finite_field_type>, args("a", "b"),
            "Adds two field element buffers. It is assumed that the buffers "
            "contains \"packed\" values, i.e., that, if possible, multiple "
            "field elements are stored in the same value type.\n\n"
            "\t:param a: The buffer containing the augends.\n"
            "\t:param b: The buffer containing the addends.\n"
            "\t:returns: A buffer containing the sums.\n")
        .def("region_subtract", &region_subtract<finite_field_type>,
            args("a", "b"),
            "Subtracts two field element buffers. It is assumed that the "
            "buffers contains \"packed\" values, i.e., that, if possible, "
            "multiple field elements are stored in the same value type.\n\n"
            "\t:param a: The buffer containing the minuends.\n"
            "\t:param b: The buffer containing the subtrahends.\n"
            "\t:returns: A buffer containing the differences.\n")
        .def("region_multiply", &region_multiply<finite_field_type>,
            args("a", "b"),
            "Multiplies two field element buffers. It is assumed that the "
            "buffers contains \"packed\" values, i.e., that, if possible, "
            "multiple field elements are stored in the same value type.\n\n"
            "\t:param a: The buffer containing the multiplicands.\n"
            "\t:param b: The buffer containing the multipliers.\n"
            "\t:returns: A buffer containing the products.\n")
        .def("region_divide", &region_divide<finite_field_type>, args("a", "b"),
            "Divides two field element buffers. It is assumed that the buffers"
            "contains \"packed\" values, i.e., that, if possible, multiple "
            "field elements are stored in the same value type.\n\n"
            "\t:param a: The buffer containing the numerators.\n"
            "\t:param b: The buffer containing the denominators.\n"
            "\t:returns: A buffer containing the quotients.\n")

        .def("region_multiply_constant",
            &region_multiply_constant<finite_field_type>, args("a", "constant"),
            "Multiplies a field element buffer with a constant. It is assumed "
            "that the buffer contains \"packed\" values, i.e., that, if "
            "possible, multiple field elements are stored in the same value "
            "type.\n\n"
            "\t:param a: The buffer containing the multiplicands.\n"
            "\t:param constant: The constant multiplier.\n"
            "\t:returns: A buffer containing the products.\n")
        .def("region_multiply_add",
            &region_multiply_add<finite_field_type>, args("a", "b", "constant"),
            "Multiplies a field element buffer with a constant, and afterwards "
            "adds the product to a second buffer. It is assumed that the "
            "buffers contains \"packed\" values, i.e., that, if possible, "
            "multiple field elements are stored in the same value type.\n"
            "The operation is: a + (constant * b).\n\n"
            "\t:param a: The buffer containing the augends.\n"
            "\t:param b: The buffer containing the multiplicands.\n"
            "\t:param constant: The constant multiplier.\n"
            "\t:returns: A buffer containing the sums.\n")
        .def("region_multiply_subtract",
            &region_multiply_subtract<finite_field_type>,
            args("a", "b", "constant"),
            "Multiplies a field element buffer with a constant, and afterwards "
            "subtracts the product from a second buffer. It is assumed that "
            "the buffers contains \"packed\" values, i.e., that, if possible, "
            "multiple field elements are stored in the same value type.\n"
            "The operation is: a - (constant * b).\n\n"
            "\t:param a: The buffer containing the minuends.\n"
            "\t:param b: The buffer containing the multiplicands.\n"
            "\t:param constant: The constant multiplier.\n"
            "\t:returns: A buffer containing the differences.\n")


        .add_property("alignment", &finite_field_type::alignment,
            "The region alignment required for the buffers "
            "used in the finite field computations. The buffers passed to the "
            "arithmetic functions should have their memory aligned according "
            "to the value returned by this function.\n\n")
        .add_property("max_alignment", &finite_field_type::max_alignment,
            "The maximum region alignment requirement of the stack. By "
            "complying with this requirement the highest performance can be "
            "achieved.\n\n")
        .add_property("granularity", &finite_field_type::granularity,
            "The buffer length granularity, i.e., length (number of "
            "value_type elements) by which the buffer must be divisible.\n\n")
        .add_property("max_granularity", &finite_field_type::max_granularity,
            "The maximum granularity requirement of the stack. By "
            "complying with this requirement the highest performance can be "
            "achieved.\n\n")
        ;
    }
}
