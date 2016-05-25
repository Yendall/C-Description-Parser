import numpy as np
from sklearn.manifold import MDS
from sklearn.metrics import euclidean_distances
from sklearn.datasets import make_classification

data, labels = make_classification()
mds = MDS(n_components=2)

similarities = euclidean_distances(data.astype(np.float64))
print similarities
print np.abs(similarities - similarities.T).max()
mds.fit(data.astype(np.float64))

similarities = euclidean_distances(data.astype(np.float32))
print np.abs(similarities - similarities.T).max()
print similarities

mds.fit(data.astype(np.float32))
