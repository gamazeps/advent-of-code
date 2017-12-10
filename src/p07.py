import collections
import random

def parse_input(fname):
    graph = collections.defaultdict(dict)
    f = open(fname, 'r')
    lines = f.readlines()
    for line in lines:
        tokens = line.strip().split(" ")
        children = list(map(lambda x: x.strip(','), tokens[3:]))
        graph[tokens[0]]["weight"] = int(tokens[1].strip('()'))
        graph[tokens[0]]["children"] = children
        for node in children:
            graph[node]["father"] = tokens[0]

    return graph

def find_root(graph):
    node = list(graph.keys())[0] #grab a random node
    while graph[node].get("father", None):
        node = graph[node]["father"]
    return node 

def recursive_weight(graph, node):
    res = graph[node]["weight"]
    for n in graph[node]["children"]:
        res += recursive_weight(graph, n)
    return res

def is_balanced(graph, node):
    weights = collections.defaultdict(list)
    for n in graph[node]["children"]:
        weights[recursive_weight(graph, n)].append(n)
    if len(weights.keys()) <= 1:
        return (True, None)
    else:
        for k in weights:
            if len(weights[k]) == 1:
                return (False, weights[k][0])

def find_unbalanced(graph, root, target = None):
    (balanced, n) = is_balanced(graph, root)
    if balanced:
        return target - recursive_weight(graph, root) + graph[root]["weight"]
    else:
        for e in graph[root]["children"]:
            if e != n:
                target = recursive_weight(graph, e)
                break
        return find_unbalanced(graph, n, target)


def main():
    g = parse_input("data/p07.in")
    print(find_root(g))
    print(recursive_weight(g, find_root(g)))
    print(is_balanced(g, find_root(g)))
    print(find_unbalanced(g, find_root(g)))

if __name__ == "__main__":
    main()

