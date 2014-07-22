#! /usr/bin/env python
# encoding: utf-8

# Copyright Steinwurf ApS 2011-2013.
# Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
# See accompanying file LICENSE.rst or
# http://www.steinwurf.com/licensing

from fifi import *


simple_api_template = """
class {classname}(object):
    \"\"\"Finite field number class for {name}.\"\"\"
    range = range(2**{degree})
    field = {implementation}_{name}()
    def __init__(self, number):
        super({classname}, self).__init__()
        self.number = number

    def __convert(self, b):
            if type(b) is int:
                return {classname}(b)
            return b

    def __add__(self, b):
        b = self.__convert(b)
        return {classname}({classname}.field.add(self.number, b.number))

    def __sub__(self, b):
        b = self.__convert(b)
        return {classname}({classname}.field.subtract(self.number, b.number))

    def __mul__(self, b):
        b = self.__convert(b)
        return {classname}({classname}.field.multiply(self.number, b.number))

    def __div__(self, b):
        b = self.__convert(b)
        return {classname}({classname}.field.divide(self.number, b.number))

    def __truediv__(self, b):
        return self.__div__(b)

    def __invert__(self):
        return {classname}({classname}.field.invert(self.number))

    def __str__(self):
        return str(self.number)
"""

fields = {
    'binary': {
        'classname': 'B',
        'degree': 1
    },
    'binary4': {
        'classname': 'B4',
        'degree': 4
    },
    'binary8': {
        'classname': 'B8',
        'degree': 8
    },
    'binary16': {
        'classname': 'B16',
        'degree': 16
    },
}

for name, field in fields.items():
    exec(simple_api_template.format(
        name=name,
        implementation='simple_online',
        **field))
