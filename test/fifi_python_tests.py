#! /usr/bin/env python
# encoding: utf-8

import unittest
import yaml

import fifi


def read_yaml(file_path):
    """
    Reads a yaml file
    """
    with open(file_path) as data_file:
        return yaml.load(data_file)

data = read_yaml('data.yaml')

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
                    if type(args[0]) is str:
                        print args
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
