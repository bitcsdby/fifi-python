#! /usr/bin/env python
# encoding: utf-8

import unittest

import fifi


class TestEncodeDecode(unittest.TestCase):

    def test_encode_decode_simple(self):
        finite_field = fifi.simple_online_binary()
        result = finite_field.add(1, 1)
        expected = 0
        self.assertEqual(result, expected)


def main():
    unittest.main()

if __name__ == "__main__":
    main()
