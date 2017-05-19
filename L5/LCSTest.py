import random, string, LCS as lcs

f = open("LCS-aver.txt", "w")

NUM_OF_TESTS_FOREACH = 50

for word_size in range(5, 2000, 50):
    sum_of_operations = 0
    for test in range(0, NUM_OF_TESTS_FOREACH):
        w1_len = random.randint(1, word_size)
        w2_len = random.randint(1, word_size)
        w1 = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(w1_len))
        w2 = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(w2_len))
        num_of_operations = lcs.longest_common_subsequence(w1, w2)
        sum_of_operations += num_of_operations

    aver_num_of_operations = sum_of_operations / NUM_OF_TESTS_FOREACH
    out = str(word_size) + " " + str(round(aver_num_of_operations, 2)) + "\n"
    f.write(out)
