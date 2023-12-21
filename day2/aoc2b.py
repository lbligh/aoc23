def main():
    """MAIN"""

    count = 0

    with open("input.txt", "r", encoding="UTF-8") as file:
        for game in file:
            min_red = 0
            min_blue = 0
            min_green = 0

            print(game.strip())
            _, rest = game.strip().split(":")
            # game_id = int(id_str.split(" ")[1])
            runs = [
                [y.strip().split(" ") for y in x.strip().split(",")]
                for x in rest.split(";")
            ]
            for run in runs:
                for color in run:
                    if color[1] == "red":
                        if int(color[0]) > min_red:
                            min_red = int(color[0])
                    if color[1] == "green":
                        if int(color[0]) > min_green:
                            min_green = int(color[0])
                    if color[1] == "blue":
                        if int(color[0]) > min_blue:
                            min_blue = int(color[0])
            print(min_red, min_green, min_blue)
            count += min_red * min_green * min_blue
    print(count)


if __name__ == "__main__":
    main()
