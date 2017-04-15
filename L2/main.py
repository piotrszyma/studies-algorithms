from subprocess import call
import subprocess
import os
import sys

call(["gcc", "Z1L2.c", "-o", "out.exe"])
print("Running C program to count swaps & comparisons...")
call(["./out.exe"])
print("Generating plots...")
print("Generating swaps graph...")
call(["py", "plot_swaps.py"])
print("Generating comparisons graph...")
call(["py", "plot_comps.py"])
print("Graphs generated...")
subprocess.Popen('explorer ".\plots"')

if len(sys.argv) == 1:
    filename = "new"
else:
    filename = sys.argv[1]

os.renames("./plots/swaps_plot.pdf", "./plots/" + filename + "_swaps.pdf")
os.renames("./plots/swaps_plot.png", "./plots/" + filename + "_swaps.png")
os.renames("./plots/comps_plot.pdf", "./plots/" + filename + "_comps.pdf")
os.renames("./plots/comps_plot.png", "./plots/" + filename + "_comps.png")
