from fifi_simple_api import B16


def main():
    a = B16(13)
    b = B16(7)

    print("{a} + {b} = {result}".format(a=a, b=b, result=a + b))
    print("{a} - {b} = {result}".format(a=a, b=b, result=a - b))
    print("{a} * {b} = {result}".format(a=a, b=b, result=a * b))
    print("{a} / {b} = {result}".format(a=a, b=b, result=a / b))
    print("~{a} = {result}".format(a=a, result=~a))

if __name__ == '__main__':
    main()
