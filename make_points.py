import sys
import random


def main(argv: list[str]):
    # we assume that there are 2 additional command line arguments passed to
    # this scrit. The first is the number of points to generate and the second
    # is the range of values, from [-n,n] that will be included in the x and y
    # values.
    if len(argv) <= 2:
        print("not enough parameters provided!")
        return -1
    try:
        number_of_points = int(argv[1])
        if number_of_points <= 0:
            print("The provided first argument was not a positive integer!")
            raise Exception
        n = int(argv[2])
        if n <= 2:
            print(
                "The provided point reange was too small! Provide an integer"
                + "greater than 2"
            )
            raise Exception

    except Exception:
        return -1

    points = set()
    while len(points) < number_of_points:
        points.add(f"{random.random()*2*n - n} {random.random()*2*n - n}")
    for point in points:
        print(point)


if __name__ == "__main__":
    main(sys.argv)
