import numpy as np


def main():
    """MAIN"""
    test = set(".1234567890")
    count = 0
    poss_gears = {}
    with open("input.txt", "r", encoding="UTF-8") as file:
        lines = ["." + line.strip() + "." for line in file]
        for line_no, line in enumerate(lines):
            offset = 0
            print(line_no)
            for char_idx, char in enumerate(line):
                if offset == 0:
                    if char.isnumeric():
                        i = char_idx
                        number = ""
                        sub_string = ""
                        while line[i].isnumeric():
                            number += line[i]
                            # print(line[i])
                            for temp in lines[line_no - 1 : line_no + 2]:
                                sub_string += temp[i - 1 : i + 2]

                            i += 1

                        offset = i - char_idx

                        sub_array = np.array(
                            [
                                list(temp[char_idx - 1 : char_idx + offset + 1])
                                for temp in lines[line_no - 1 : line_no + 2]
                            ],
                            dtype=str,
                        )
                        sub_set = set(sub_string)

                        if not sub_set.issubset(test):
                            # is a part number
                            if "*" in sub_set:
                                # could be a gear so get location
                                # print(sub_set)
                                # print(sub_array)
                                sub_xs, sub_ys = np.where(sub_array == "*")
                                sub_xs += line_no - 1
                                sub_ys += char_idx - 1
                                for coord in zip(sub_xs, sub_ys):
                                    poss_gears[coord] = poss_gears.setdefault(
                                        coord, list()
                                    )
                                    poss_gears[coord].append(int(number))
                                    # d[i % 10] = d.setdefault(i % 10, 0) + 1
                else:
                    offset -= 1

    print(poss_gears)
    for key in poss_gears.keys():
        if len(poss_gears[key]) == 2:
            count += poss_gears[key][0] * poss_gears[key][1]
    print(count)


if __name__ == "__main__":
    main()
