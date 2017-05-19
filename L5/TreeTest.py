import random, Tree as T, sys

sys.setrecursionlimit(10000)  # 10000 is an example, try with different values


def my_shuffle(array):
    random.shuffle(array)
    return array


f = open("os-rank.txt", "w")
f_min = open("os-rank-min.txt", "w")
f_max = open("os-rank-max.txt", "w")

tree_operations_sum = 0
tree_operations_max = 0
tree_operations_min = sys.maxsize
NUM_OF_TESTS_FOREACH = 1
for array_size in range(5, 1000, 10):
    array = [i + 1 for i in range(array_size)]
    tree = T.Tree()

    for element in array:
        tree.insert(element)

    for i in range(0, NUM_OF_TESTS_FOREACH):
        random.shuffle(array)
        tree.os_select(tree.root, random.randint(1, array_size))
        tree_operations_sum += tree.operations
        if tree_operations_max < tree.operations:
            tree_operations_max = tree.operations
        if tree_operations_min > tree.operations:
            tree_operations_min = tree.operations
        tree.clear_operations_counter()

    tree_operations_sum /= NUM_OF_TESTS_FOREACH

    out = str(array_size) + " " + str(round(tree_operations_sum, 2)) + "\n"
    f.write(out)
    out_min = str(array_size) + " " + str(round(tree_operations_min, 2)) + "\n"
    f_min.write(out_min)
    out_max = str(array_size) + " " + str(round(tree_operations_max, 2)) + "\n"
    f_max.write(out_max)

    tree_operations_max = 0
    tree_operations_min = sys.maxsize

f.close()
