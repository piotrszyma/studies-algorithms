import matplotlib.pyplot as plt
import numpy as np
import os

# MERGE SORT
file = open("insertion_sort_swaps.txt", "r")
x_axis = []
y_axis = []
for line in file:
    x_axis.append(line.split(" ")[0])
    y_axis.append(line.split(" ")[1])

x_axis = np.asarray(x_axis)
y_axis = np.asarray(y_axis)

plt.plot(x_axis, y_axis, 'g', linewidth=0.9, label="Insertion sort")

# MERGE SORT
file = open("merge_sort_swaps.txt", "r")
x_axis = []
y_axis = []
for line in file:
    x_axis.append(line.split(" ")[0])
    y_axis.append(line.split(" ")[1])

x_axis = np.asarray(x_axis)
y_axis = np.asarray(y_axis)

plt.plot(x_axis, y_axis, 'b', linewidth=0.9, label="Merge sort")

# QUICKSORT

file = open("quick_sort_swaps.txt", "r")
x_axis = []
y_axis = []
for line in file:
    x_axis.append(line.split(" ")[0])
    y_axis.append(line.split(" ")[1])

x_axis = np.asarray(x_axis)
y_axis = np.asarray(y_axis)

plt.plot(x_axis, y_axis, 'r', linewidth=0.9, label="Quick sort")
plt.legend(bbox_to_anchor=(0.1, 0.9), loc=2, borderaxespad=0.)
plt.xlabel("Array size")
plt.ylabel("Number of swaps")
plt.title("Relation between number of swaps and array size")
if not os.path.exists("plots"):
    os.makedirs("plots")
plt.savefig('plots/swaps_plot.pdf')
plt.savefig('plots/swaps_plot.png')
