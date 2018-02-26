import random, string, LCS as lcs, ED as ed

f = open("ED-aver.txt", "w")

NUM_OF_TESTS_FOREACH = 10

for word_size in range(5, 100, 10):
    sum_of_operations = 0
    for test in range(0, NUM_OF_TESTS_FOREACH):
        w1_len = random.randint(1, word_size)
        w2_len = random.randint(1, word_size)
        w1 = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(w1_len))
        w2 = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(w2_len))
        edist = ed.ED()
        edist.edit_distance(w1, w2)
        sum_of_operations += edist.operations

    aver_num_of_operations = sum_of_operations / NUM_OF_TESTS_FOREACH
    out = str(word_size) + " " + str(round(aver_num_of_operations, 2)) + "\n"
    f.write(out)
