import matplotlib.pyplot as plt
import networkx as nx
import time


def print_graph(nodes, edges, nodeList_infected, edges_distance):
    G = nx.Graph()
    G.add_nodes_from(nodes)
    G.add_edges_from(edges)

    position = nx.circular_layout(G)

    nx.draw_networkx_nodes(G, position, nodelist=nodes, node_color="y")
    nx.draw_networkx_nodes(G, position, nodelist=nodeList_infected, node_color="b")

    nx.draw_networkx_edges(G, position)
    nx.draw_networkx_labels(G, position)
    nx.draw_networkx_edge_labels(G, position, edge_labels=edges_distance, font_color='red')

    plt.show()


def infection_spread_adjacent(nodes, edges, nodeList_infected, edges_distance):
    print_graph(nodes, edges, nodeList_infected, edges_distance)

    time.sleep(5)

    new_infected = []
    for infected in nodeList_infected:
        if len(new_infected) == len(nodeList_infected):
            break

        for node in nodeList_infected:
            if node not in new_infected:
                new_infected.append(node)
        for edge in edges:
            if infected in edge:
                # print(edge[1])
                if edge[1] not in nodeList_infected:
                    nodeList_infected.append(edge[1])
                if edge[0] not in nodeList_infected:
                    nodeList_infected.append(edge[0])

        print_graph(nodes, edges, nodeList_infected, edges_distance)
        time.sleep(5)

    print(nodeList_infected)


def get_absolute_distance(nodeList_infected, edges_distance):

    infect_dict = {nodeList_infected[0]: 0}
    new_infected = []

    for infected in nodeList_infected:
        if len(new_infected) == len(nodeList_infected):
            break

        for node in nodeList_infected:
            if node not in new_infected:
                new_infected.append(node)
        for edge in edges_distance:
            if infected in edge:
                # print(edge[1])
                if edge[1] not in nodeList_infected:
                    nodeList_infected.append(edge[1])
                    infect_dict[edge[1]] = infect_dict[infected] + edges_distance[edge]

                if edge[0] not in nodeList_infected:
                    nodeList_infected.append(edge[0])
                    infect_dict[edge[0]] = infect_dict[infected] + edges_distance[edge]

    return infect_dict


def infection_spread_distance(nodes, edges, edges_distance, speed, infect_dict):
    t = 0
    distance = 0
    infected_list = []

    while distance <= max(list(edges_distance.values())):

        for city in infect_dict.keys():
            if infect_dict[city] <= distance:
                infected_list.append(city)

        print_graph(nodes, edges, infected_list, edges_distance)
        infected_list.clear()

        t = t+1
        distance = distance + speed
        time.sleep(5)


if __name__ == "__main__":

    nodes = ['Atlanta', 'Boston', 'Boulder', 'Cheyenne', 'Chicago', 'Cleveland', 'Disneyland', 'Key West',
             'Miami', 'New Orleans', 'New York', 'Portland', 'San Francisco', 'Seattle', 'Yakima']
    edges = [('Atlanta', 'Miami'), ('Atlanta', 'New Orleans'), ('Boston', 'Chicago'), ('Boston', 'Cleveland'),
             ('Boston', 'New York'), ('Boulder', 'Chicago'), ('Cheyenne', 'Portland'), ('Cheyenne', 'Yakima'),
             ('Chicago', 'Cleveland'), ('Disneyland', 'Portland'), ('Disneyland', 'San Francisco'),
             ('Key West', 'Miami'), ('Miami', 'New Orleans'), ('Portland', 'San Francisco'), ('Portland', 'Seattle'),
             ('Portland', 'Yakima'), ('Seattle', 'Yakima')]
    nodeList_infected = []
    edges_distance = {('Atlanta', 'Miami'): 663, ('Atlanta', 'New Orleans'): 487, ('Boston', 'Chicago'): 982,
                        ('Boston', 'Cleveland'): 640, ('Boston', 'New York'): 215, ('Boulder', 'Chicago'): 1130,
                        ('Cheyenne', 'Portland'): 1162,  ('Cheyenne', 'Yakima'): 1095, ('Chicago', 'Cleveland'): 344,
                        ('Disneyland', 'Portland'): 989, ('Disneyland', 'San Francisco'): 408, ('Key West', 'Miami'): 159,
                        ('Miami', 'New Orleans'): 864, ('Portland', 'San Francisco'): 635, ('Portland', 'Seattle'): 173,
                        ('Portland', 'Yakima'): 185, ('Seattle', 'Yakima'): 142}

    print_graph(nodes, edges, nodeList_infected, edges_distance)

    time.sleep(5)

    # provide infected city
    infected_city = 'Atlanta'
    nodeList_infected.append(infected_city)

    # code for adjacent city bases infection spread
    # infection_spread_adjacent(nodes, edges, nodeList_infected, edges_distance)

    # code for speed based infection spread
    speed = 500
    infect_dict = get_absolute_distance(nodeList_infected, edges_distance)
    infection_spread_distance(nodes, edges, edges_distance, speed, infect_dict)