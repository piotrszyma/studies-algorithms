import matplotlib.pyplot as plt
import numpy as np
import os
import sys


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
    generate_plot('quick_sort_' + plot_type + '.txt', 'quick sort ' + plot_type, 'r')
    generate_plot('merge_sort_' + plot_type + '.txt', 'merge sort ' + plot_type, 'g')
    if len(sys.argv) < 3:
        generate_plot('insertion_sort_' + plot_type + '.txt', 'insertion sort ' + plot_type, 'b')

    plt.xlabel("Array size")
    plt.ylabel("Swaps")
    plt.title("Relation between " + plot_type + " and array size")

    if not os.path.exists("plots"):
        os.makedirs("plots")

    name = "plot"
    iter = 0
    while os.path.isfile("plots/" + name + "_" + str(iter) + ".png"):
        iter += 1

    plt.savefig("plots/" + name + "_" + str(iter) + ".png")


generate_plot("sec_merge_sort_swaps.txt", 'merge sort swaps', 'r')
generate_plot("sec_merge_sort_impr_swaps.txt", 'merge sort improved swaps', 'g')
generate_plot("sec_quick_sort_swaps.txt", 'quick sort swaps', 'b')
generate_plot("sec_quick_sort_impr_swaps.txt", 'quick sort  improved swaps', 'y')
plt.xlabel("Array size")
plt.ylabel("Swaps")

if not os.path.exists("plots"):
    os.makedirs("plots")

name = "plot"
iter = 0
while os.path.isfile("plots/" + name + "_" + str(iter) + ".png"):
    iter += 1

plt.savefig("plots/" + name + "_" + str(iter) + ".png")
