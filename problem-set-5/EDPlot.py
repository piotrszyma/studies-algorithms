import os, matplotlib.pyplot as plt, numpy as np, sys

generate_max = False

if len(sys.argv) > 1:
    generate_max = True


def generate_plot(filename, label_desc, color):
    file = open(filename, 'r')

    x_axis = []
    y_axis = []
    for line in file:
        x_axis.append(line.split(" ")[0])
        y_axis.append(line.split(" ")[1])

    x_axis = np.asarray(x_axis)
    y_axis = np.asarray(y_axis)

    plt.plot(x_axis, y_axis, color, ms=2.5, label=label_desc)

    plt.legend(bbox_to_anchor=(0.1, 0.9), loc=2, borderaxespad=0.)


def create_plot():
    generate_plot('ED-aver.txt', 'average', 'ro')
    # generate_plot('os-rank-min.txt', 'minimum', 'g')
    # generate_plot('os-rank-max.txt', 'maximum', 'b')
    # generate_plot('../cmake-build-debug/min.txt', 'min', 'g')
    # if generate_max:
    #     generate_plot('../cmake-build-debug/max.txt', 'max', 'b')

    plt.xlabel("Max size of word")
    plt.ylabel("Number of comparisons")
    plt.title("LCS algorithm average complexity")

    iter = 0
    while os.path.isfile("ED_plot(" + str(iter) + ").png"):
        iter += 1

    plt.savefig("ED_plot(" + str(iter) + ").png")


create_plot()
