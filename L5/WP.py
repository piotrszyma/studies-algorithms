import ED as ed


# WP - WordPrompter


def prompt():
    f = open("words.txt", "r").readlines()

    for w in f:
        w.strip("\n")

    while 1:
        word = input("Input part of the word: ")

        def word_ed(str1):
            editer = ed.ED()
            return editer.edit_distance(str1, word)

        words = [s.strip("\n") for s in f if s.startswith(word.lower())]
        words.sort(key=word_ed)

        for word in words[:4]:
            print(word, end=" ")
        if len(words) == 0:
            print("Word not found in dictionary", end=" ")

        print()
