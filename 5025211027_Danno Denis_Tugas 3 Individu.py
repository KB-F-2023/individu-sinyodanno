from typing import Dict, List

def constraints(node: str, color: str, assignment: Dict[str, str], graph: Dict[str, List[str]]) -> bool:
    return all(assignment.get(neighbor) != color for neighbor in graph[node])

def backtrack(assignment: Dict[str, str], graph: Dict[str, List[str]],
              domain: Dict[str, List[str]]) -> Dict[str, str]:
    if len(assignment) == len(graph):
        return assignment
    for node, neighbors in graph.items():
        if node not in assignment:
            for color in domain[node]:
                if constraints(node, color, assignment, graph):
                    assignment[node] = color
                    result = backtrack(assignment, graph, domain)
                    if result:
                        return result
                    del assignment[node]
            break
    return None

def solve_map_coloring(graph: Dict[str, List[str]], colors: List[str]) -> Dict[str, str]:
    domain = {node: set(colors) for node in graph}
    return backtrack({}, graph, domain)

graph = {
    'WA': ['NT', 'SA'],
    'NT': ['WA', 'SA', 'Q'],
    'SA': ['WA', 'NT', 'Q', 'NSW', 'V'],
    'Q': ['NT', 'SA', 'NSW'],
    'NSW': ['Q', 'SA', 'V'],
    'V': ['SA', 'NSW']
}

colors = {'red', 'green', 'blue'}

solution = solve_map_coloring(graph, colors)

print(solution)