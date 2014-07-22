import fifi

simple_api_template = """
class {classname}(object):
    \"\"\"Finite field number class for {name}.\"\"\"
    range = xrange(2**{degree})
    field = fifi.{implementation}_{name}()
    def __init__(self, number):
        super({classname}, self).__init__()
        self.number = number

    def __add__(self, b):
        return {classname}({classname}.field.add(self.number, b.number))

    def __sub__(self, b):
        return {classname}({classname}.field.subtract(self.number, b.number))

    def __mul__(self, b):
        return {classname}({classname}.field.multiply(self.number, b.number))

    def __div__(self, b):
        return {classname}({classname}.field.divide(self.number, b.number))

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

for name, field in fields.iteritems():
    exec(simple_api_template.format(
        name=name,
        implementation='simple_online',
        **field))
