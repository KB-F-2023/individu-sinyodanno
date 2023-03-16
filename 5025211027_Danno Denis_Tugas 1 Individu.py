#Danno Denis Dhaifullah 5025211027

def find_path(graph, start, goal):
    def heuristic(nodeA, nodeB):
        x1, y1 = graph[nodeA]['pos']
        x2, y2 = graph[nodeB]['pos']
        return ((x2 - x1) ** 2 + (y2 - y1) ** 2) ** 0.5

    g = {start: 0}
    f = {start: heuristic(start, goal)}
    visited = set()
    parents = {}

    while f:
        current = min(f, key=f.get)
        if current == goal:
            path = []
            while current in parents:
                path.append(current)
                current = parents[current]
            path.append(start)
            path.reverse()
            return path

        visited.add(current)
        del f[current]

        for neighbor, cost in graph[current]['edges'].items():
            if neighbor in visited:
                continue
            new_g = g[current] + cost
            if neighbor not in f or new_g < g[neighbor]:
                g[neighbor] = new_g
                f[neighbor] = new_g + heuristic(neighbor, goal)
                parents[neighbor] = current

    return None


def print_path_info(graph, start, goal):
    path = find_path(graph, start, goal)
    if path is not None:
        print(f"The shortest path from {start} to {goal} is:")
        print(" -> ".join(path))
        for node in graph:
            if node != goal:
                sld = heuristic(node, goal)
                print(f'SLD from {node} to {goal}: {sld:.2f}')
    else:
        print(f"No path found from {start} to {goal}.")


if __name__ == "__main__":
    g = {
        'A': {'pos': (0, 0), 'edges': {'B': 1, 'C': 3, 'D': 7}},
        'B': {'pos': (1, 2), 'edges': {'E': 5}},
        'C': {'pos': (3, 4), 'edges': {'F': 2}},
        'D': {'pos': (5, 6), 'edges': {'G': 1, 'H': 2}},
        'E': {'pos': (3, 1), 'edges': {'H': 3}},
        'F': {'pos': (5, 3), 'edges': {'H': 5}},
        'G': {'pos': (7, 7), 'edges': {'H': 2}},
        'H': {'pos': (8, 8), 'edges': {}}
    }

    s = input("Enter the start node: ")
    e = input("Enter the end node: ")

    print_path_info(g, s, e)