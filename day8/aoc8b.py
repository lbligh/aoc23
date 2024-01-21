import re
from numpy import lcm


def checker(nodes):
    """returns true if all nodes end in Z"""
    return all(i[2] == "Z" for i in nodes)


def main():
    """MAIN"""
    nodes = {}
    snodes = []
    with open("input.txt", "r", encoding="UTF-8") as file:
        for lineno, line in enumerate(file):
            if lineno > 1:
                # print(lineno, line.strip())
                reg = re.split(r"(\w{3})\W+(\w{3})\W+(\w{3})", line.strip())
                nodes[reg[1]] = (reg[2], reg[3])
                if reg[1][2] == "A":
                    snodes.append(reg[1])
            if lineno == 0:
                lrlist = line.strip()

    print(snodes)
    print(lrlist)
    counts = [0 for _ in snodes]

    for i, _ in enumerate(snodes[:]):
        while snodes[i][2] != "Z":
            for inst in lrlist:
                if snodes[i][2] == "Z":
                    break
                snodes[i] = nodes[snodes[i]][0 if inst == "L" else 1]

                counts[i] += 1
    print(snodes)
    print(counts)

    print(lcm.reduce(counts))


if __name__ == "__main__":
    main()
