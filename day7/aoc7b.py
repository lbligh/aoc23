from functools import total_ordering
import numpy as np


hand_rankings = "J23456789TQKA"
hand_types = ["HC", "1P", "2P", "3oK", "FH", "4oK", "5oK"]


@total_ordering
class Hand:
    def __init__(self, hand_str, bid):
        self.hand_str = hand_str
        set_hand = set(self.hand_str)
        self.bid = bid

        # print(set_hand)
        # len of 1 = 5 of a kind
        # len of 2 = 4 of a kind or full house
        # len of 3 = 3 of a kind or 2 pair
        # len of 4 = one pair
        # len of 5 = high card
        if "J" not in set_hand:
            match len(set_hand):
                case 1:
                    self.type = 6
                case 2:
                    if (
                        self.hand_str.count(list(set_hand)[0]) == 1
                        or self.hand_str.count(list(set_hand)[0]) == 4
                    ):
                        self.type = 5
                    else:
                        self.type = 4
                case 3:
                    three_of_kind = 0
                    for card in set_hand:
                        if self.hand_str.count(card) == 3:
                            three_of_kind = 1
                    self.type = 3 if three_of_kind else 2
                case 4:
                    self.type = 1
                case 5:
                    self.type = 0
        else:
            jokers = self.hand_str.count("J")
            match len(set_hand):
                case 1:  # all jokers so 5oK
                    self.type = 6
                case 2:  # jokers and another card so 5oK
                    self.type = 6
                case 3:  # either full house or 4 of kind
                    if jokers == 1:
                        cards = [
                            self.hand_str.count(card)
                            for card in list(set_hand)
                            if card != "J"
                        ]
                        if cards[0] == cards[1]:
                            self.type = 4
                        else:
                            self.type = 5
                    else:
                        self.type = 5
                case 4:
                    self.type = 3
                case 5:
                    self.type = 1
            print(self)

    def __eq__(self, other):
        # print("In Equal")
        return self.hand_str == other.hand_str

    def __lt__(self, other):
        # print("In LT")
        if self == other:
            return False
        elif self.type < other.type:
            return True
        elif self.type > other.type:
            return False
        else:
            for s_char, o_char in zip(self.hand_str, other.hand_str):
                if hand_rankings.index(s_char) < hand_rankings.index(o_char):
                    return True
                elif hand_rankings.index(s_char) > hand_rankings.index(o_char):
                    return False

    def __str__(self):
        return f"Hand: {self.hand_str}, Bid: {self.bid}, Type: {hand_types[self.type]}"


def main():
    """MAIN"""

    with open("input.txt", "r", encoding="UTF-8") as file:
        hands = np.array(
            [
                Hand(line.strip().split(" ")[0], int(line.strip().split(" ")[1]))
                for line in file
            ],
            dtype=Hand,
        )

    count = 0

    for rank, hand in enumerate(sorted(hands)):
        print(hand, (rank + 1) * hand.bid)
        count += (rank + 1) * hand.bid

    print(count)


if __name__ == "__main__":
    main()
