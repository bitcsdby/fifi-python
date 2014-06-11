#! /usr/bin/env python
# encoding: utf-8

import unittest

import fifi


class TestEncodeDecode(unittest.TestCase):

    def test_encode_decode_simple(self):
        print "FIFI:"
        print dir(fifi)
        finite_field = fifi.simple_online_binary()
        print "FINITE FIELD:"
        print dir(finite_field)


def main():
    unittest.main()

if __name__ == "__main__":
    main()
