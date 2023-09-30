from random import randint
import sys


def main(argv: list[str]):
    # we assume that there are 2 additional command line arguments passed to
    # this scrit. The first is the number of points to generate and the second
    # is the range of values, from [0,n] that will be included in the x and y
    # values.
    if len(argv) <= 2:
        print("not enough parameters provided!")
        return -1
    try:
        number_of_points = int(argv[1])
        if number_of_points <= 0:
            print("The provided first argument was not a positive integer!")
            raise Exception
        point_range = int(argv[2])
        if point_range <= 2:
            print(
                "The provided point reange was too small! Provide an integer"
                + "greater than 2"
            )
            raise Exception

    except Exception:
        return -1

    for _ in range(number_of_points):
        print(f"{randint(0,point_range)},{randint(0,point_range)}")
    return 0

if __name__ == "__main__":
    main(sys.argv)
