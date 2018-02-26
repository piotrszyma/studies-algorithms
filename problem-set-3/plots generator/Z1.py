# wielkość tablicy danych
# losowe, posortowane malejąco
# z logiem, bez loga
# czy generowanie wykresu

# ./radixsort
# [n: wielkość tablicy]
# [0: losowe, 1: posortowane malejąco]
# [0: z logiem, 1: bez loga]
# [0: nie generuj wykresu, 1: generuj wykres]

import os, matplotlib.pyplot as plt, numpy as np


def generate_plot(filename, label_desc, color):
    file = open(filename, 'r')

    x_axis = []
    y_axis = []
    for line in file:
        x_axis.append(line.split(" ")[0])
        y_axis.append(line.split(" ")[1])

    x_axis = np.asarray(x_axis)
    y_axis = np.asarray(y_axis)

    plt.plot(x_axis, y_axis, color, linewidth=0.9, label=label_desc)

    plt.legend(bbox_to_anchor=(0.1, 0.9), loc=2, borderaxespad=0.)


def create_plot():
    generate_plot('radix_sort_comps.txt', 'radix sort comps', 'r')
    generate_plot('radix_sort_swaps.txt', 'radix sort swaps', 'g')

    plt.xlabel("Array size")
    plt.ylabel("Number of operations")
    plt.title("Number of swaps and comparisons in RADIX SORT")

    if not os.path.exists("plots"):
        os.makedirs("plots")

    iter = 0
    while os.path.isfile("plots/radix_sort" + str(iter) + ".png"):
        iter += 1

    plt.savefig("plots/radix_sort_" + str(iter) + ".png")



print("RADIX SORT - analysis of algorithm")
O_SIZE = O_SORT = O_LOG = O_GRAPH = -1
while O_SIZE < 0 or O_SIZE > 500000:
    O_SIZE = int(input("Enter array size: [0 -  5*10^6] "))
while O_SORT < 0 or O_SORT > 1:
    O_SORT = int(input("Enter array order: [0: rand, 1: desc] "))
while O_LOG < 0 or O_LOG > 1:
    O_LOG = int(input("Display log?: [0: no, 1: yes] "))
while O_GRAPH < 0 or O_GRAPH > 1:
    O_GRAPH = int(input("Generate graph?: [0: no, 1: yes] "))

os.system("radixsort.exe " + str(O_SIZE) + " " + str(O_SORT) + " " + str(O_LOG) + " " + str(O_GRAPH))

if O_GRAPH:
    create_plot()
