import networkx as nx
import numpy as np
import pylab as plt
from numpy import genfromtxt
import string
from networkx.drawing.nx_agraph import to_agraph

# Create a Graph
G = nx.Graph()

# Distance Matrix
#X = genfromtxt('matrix.csv',delimiter=',')
#D = 1 - X
#D *= 10
D = [ [0.5,1], [1,0.5]]
labels = {}
for n in range(len(D)):
    for m in range(len(D)-(n+1)):
        G.add_edge(n,n+m+1)
        labels[ (n,n+m+1)] = str(D[n][n+m+1])

pos = nx.spring_layout(G)

nx.draw(G,pos)
nx.draw_networkx_edge_labels(G,pos,edge_labels=labels,font_size=30)
plt.show()