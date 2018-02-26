import matplotlib.pyplot as plt
import numpy as np
import os
import sys

if sys.argv[1][0] == 's':
    plot_type = 'swaps'
else:
    plot_type = 'comps'


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
    plt.ylabel("swaps")
    plt.title("Relation between " + plot_type + " and array size")

    if not os.path.exists("plots"):
        os.makedirs("plots")

    name = "plot"
    iter = 0
    while os.path.isfile("plots/" + name + "_" + str(iter) + ".png"):
        iter += 1

    plt.savefig("plots/" + name + "_" + str(iter) + ".png")


create_plot()
