import matplotlib.pyplot as plt
import numpy as np
import os


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

generate_plot('quick_sort_comps.txt', 'quick sort comps', 'r')
generate_plot('merge_sort_improved_comps.txt', 'merge sort improved comps', 'g')
generate_plot('quick_sort_comps.txt', 'quick sort comps', 'b')
generate_plot('merge_sort_comps.txt', 'merge sort comps', 'y')

plt.xlabel("Array size")
plt.ylabel("comps")
plt.title("Relation between comps and array size")

if not os.path.exists("plots"):
    os.makedirs("plots")

plt.savefig('plots/comps_output.pdf')
plt.savefig('plots/comps_output.png')
