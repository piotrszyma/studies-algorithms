# podaj rozmiar tablicy
# czy ma być losowe różnowartościowe czy nie?
# podaj numer szukanej statystyki pozycyjnej
# czy ma być log?
# czy generowanie statystyk

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

    plt.plot(x_axis, y_axis, color, ms=0.5, label=label_desc)

    plt.legend(bbox_to_anchor=(0.1, 0.9), loc=2, borderaxespad=0.)


def create_plot():
    # NEXT FIG:
    generate_plot('qs_mm_100_100000.txt', 'quick sort & mm pivot average', 'r')
    generate_plot('qs_rand_100_100000.txt', 'quick sort & random pivot average', 'g')
    generate_plot('qs_mm_100_100000_min.txt', 'quick sort & mm pivot min', 'b')
    generate_plot('qs_rand_100_100000_min.txt', 'quick sort & random pivot min', 'c')
    generate_plot('qs_mm_100_100000_max.txt', 'quick sort & mm pivot max', 'y')
    generate_plot('qs_rand_100_100000_max.txt', 'quick sort & random pivot max', 'm')

    plt.xlabel("Array size")
    plt.ylabel("Number of operations")
    plt.title("Quick sort with median of medians and random - operations number comparison")

    iter = 0
    while os.path.isfile("plots/qs_mm_rand_" + str(iter) + ".png"):
        iter += 1
    plt.savefig("qs_mm_rand_" + str(iter) + ".png")

create_plot()
#
# print("RANDOMIZED SELECT, SELECT - analysis of algorithms")
# O_SIZE = O_SORT = O_LOG = O_GRAPH = O_SEARCHED = -1
#
# while O_SIZE < 0 or O_SIZE > 500000:
#     O_SIZE = int(input("Enter array size: [0 -  5*10^6] "))
#
# while O_SORT < 0 or O_SORT > 1:
#     O_SORT = int(input("Enter array type: [0: permutation, 1: rand] "))
#
# while O_SEARCHED < 0 or O_SEARCHED > 500000:
#     O_SEARCHED = int(input("Searched index?: [0 - arraySize] "))
#
# while O_LOG < 0 or O_LOG > 1:
#     O_LOG = int(input("Display log?: [0: no, 1: yes] "))
#
# while O_GRAPH < 0 or O_GRAPH > 1:
#     O_GRAPH = int(input("Generate graph?: [0: no, 1: yes] "))
#
# os.system(
#     "select.exe " + str(O_SIZE) + " " + str(O_SORT) + " " + str(O_SEARCHED) + " " + str(O_LOG) + " " + str(O_GRAPH))
#
# if O_GRAPH:
#     create_plot()
