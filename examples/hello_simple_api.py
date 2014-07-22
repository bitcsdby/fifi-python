from fifi_simple_api import B4


def main():
    a = B4(13)
    b = B4(7)

    print("{a} + {b} = {result}".format(a=a, b=b, result=a + b))
    print("{a} - {b} = {result}".format(a=a, b=b, result=a - b))
    print("{a} * {b} = {result}".format(a=a, b=b, result=a * b))
    print("{a} / {b} = {result}".format(a=a, b=b, result=a / b))
    print("~{a} = {result}".format(a=a, result=~a))

if __name__ == '__main__':
    main()
