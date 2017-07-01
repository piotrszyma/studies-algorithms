import sys
import os
import random

m_file_name = "input.txt"
m_graph_max_size = 20
m_number_of_tests = 10


# for j in range(graph_size):
# print(input_graph)

def generate_graph(number_of_tests):
    for i in range(number_of_tests):
        graph_size = random.randint(1, graph_max_size)
        graph_vertexes_number = random.randint(graph_size - 1, graph_size * (graph_size - 1) * 0.5)
        input_graph = generate_vertexes(graph_size, graph_vertexes_number)
        # safe to file
        # run with this file
        # save input/output to file


def generate_vertexes(graph_size, graph_vertexes_number):
    input_graph = ""
    input_graph += str(graph_size) + "\n"
    input_graph += str(graph_vertexes_number) + "\n"

    for i in range(graph_vertexes_number):


    return input_graph
