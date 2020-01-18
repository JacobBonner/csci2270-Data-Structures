import matplotlib.pyplot as plt
import networkx as nx
import time
import sys

def print_graph(nodes, edges, nodeList_infected):
    G = nx.Graph()
    G.add_nodes_from(nodes)
    G.add_edges_from(edges)

    position = nx.circular_layout(G)

    nx.draw_networkx_nodes(G, position, nodelist=nodes, node_color="lightgrey")
    nx.draw_networkx_nodes(G, position, nodelist=nodeList_infected, node_color="green")

    nx.draw_networkx_edges(G, position)
    nx.draw_networkx_labels(G, position)

    plt.show()


if __name__ == "__main__":

    nodeList_infected = []

    myfile = open(sys.argv[1])
    nodes = eval(next(myfile))
    edges = eval(next(myfile))
    print_graph(nodes, edges, nodeList_infected)
    steps = eval(next(myfile))
    for x in steps:
    	nodeList_infected = x
    	print_graph(nodes, edges, nodeList_infected)