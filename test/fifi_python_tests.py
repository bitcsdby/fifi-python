#! /usr/bin/env python
# encoding: utf-8

import json
import os
import unittest

import fifi


DATA_FILE_NAME = 'data.json'


def read_json(file_path):
    """
    Reads a json file
    """
    with open(file_path) as data_file:
        return json.load(data_file)

file_path = os.path.join(
    os.path.dirname(os.path.abspath(__file__)), DATA_FILE_NAME)

data = read_json(file_path)

fields = {
    'binary': [
        fifi.simple_online_binary
    ],
    'binary4': [
        fifi.extended_log_table_binary4,
        fifi.full_table_binary4,
        fifi.log_table_binary4,
        fifi.simple_online_binary4
    ],
    'binary8': [
        fifi.extended_log_table_binary8,
        fifi.full_table_binary8,
        fifi.log_table_binary8,
        fifi.simple_online_binary8
    ],
    'binary16': [
        fifi.extended_log_table_binary16,
        fifi.log_table_binary16,
        fifi.simple_online_binary16
    ],
    'prime2325': [
        fifi.optimal_prime_prime2325
    ],
}


class TestOperations(unittest.TestCase):

    def do_test(self, operation):
        for field in fields:
            for implementation in fields[field]:
                finite_field = implementation()

                if not hasattr(finite_field, operation):
                    return

                test_data = data[field].get(operation, [])

                for d in test_data:
                    args = []
                    args.append(d['input1'])
                    if 'input2' in d:
                        args.append(d['input2'])
                    expected = d['result']
                    result = getattr(finite_field, operation)(*args)
                    self.assertEqual(result, expected)

    def test_add(self):
        self.do_test('add')

    def test_multiply(self):
        self.do_test('multiply')

    def test_divide(self):
        self.do_test('divide')

    def test_invert(self):
        self.do_test('invert')

    def test_packed_add(self):
        self.do_test('packed_add')

    def test_packed_multiply(self):
        self.do_test('packed_multiply')

    def test_packed_divide(self):
        self.do_test('packed_divide')

    def test_packed_invert(self):
        self.do_test('packed_invert')


def main():
    unittest.main()

if __name__ == "__main__":
    main()
