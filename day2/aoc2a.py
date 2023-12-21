def main():
    """MAIN"""
    max_red = 12
    max_green = 13
    max_blue = 14

    count = 0

    with open("input.txt", "r", encoding="UTF-8") as file:
        for line in file:
            print(line.strip())
            id_str, rest = line.strip().split(":")
            game_id = int(id_str.split(" ")[1])
            runs = [
                [y.strip().split(" ") for y in x.strip().split(",")]
                for x in rest.split(";")
            ]
            dead = 0
            for run in runs:
                if dead:
                    break
                for color in run:
                    if dead:
                        break
                    if color[1] == "red":
                        if int(color[0]) > max_red:
                            dead = 1
                    elif color[1] == "green":
                        if int(color[0]) > max_green:
                            dead = 1
                    elif color[1] == "blue":
                        if int(color[0]) > max_blue:
                            dead = 1
            if dead:
                print(line.strip(), " is bad")
            else:
                count += game_id
    print(count)


if __name__ == "__main__":
    main()
