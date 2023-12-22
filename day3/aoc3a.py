def main():
    """MAIN"""
    test = set(".1234567890")
    count = 0

    with open("input.txt", "r", encoding="UTF-8") as file:
        lines = ["." + line.strip() + "." for line in file]
        for line_no, line in enumerate(lines):
            offset = 0
            print(line)
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

                        sub_set = set(sub_string)
                        # print(sub_string, sub_set)
                        if not sub_set.issubset(test):
                            print(int(number), " is a part number")
                            count += int(number)
                else:
                    offset -= 1
    print(count)


if __name__ == "__main__":
    main()
