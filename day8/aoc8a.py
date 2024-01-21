import re


def main():
    """MAIN"""
    nodes = {}
    with open("input.txt", "r", encoding="UTF-8") as file:
        for lineno, line in enumerate(file):
            if lineno > 1:
                # print(lineno, line.strip())
                reg = re.split(r"(\w{3})\W+(\w{3})\W+(\w{3})", line.strip())
                nodes[reg[1]] = (reg[2], reg[3])
            if lineno == 0:
                lrlist = line.strip()
    count = 0
    node = "MCA"
    while node[2] != "Z":
        for inst in lrlist:
            if node[2] == "Z":
                break
            node = nodes[node][0 if inst == "L" else 1]
            count += 1

    print(count)


if __name__ == "__main__":
    main()
