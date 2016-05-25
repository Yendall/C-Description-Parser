import csv
import numpy as np
import matplotlib.pyplot as plt
from sklearn import manifold

reader = csv.reader(open("semantic_similarity_matrix_reduced/matrix.csv","r"),delimiter=',')
data = list(reader)

dists = []
count = 0
for d in data:
    print "Row: ",count,d[count]
    dists.append(map(float,d[0:-1]))
    count += 1

adist = np.array(dists)
amax = np.amax(dists)
adist /= amax

mds = manifold.MDS(n_components=2, dissimilarity="precomputed",random_state=6)
results = mds.fit(adist.astype(np.float64))

coords = results.embedding_

plt.subplots_adjust(bottom = 0.1)
plt.scatter(
    coords[:, 0], coords[:,1], marker = 'o'
)

plt.show()