import os
import scipy
import glob
import numpy as np
import matplotlib.pyplot as plt

from sklearn.manifold import MDS
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity


# Filenames for training a corpus
filenames = glob.glob('../data/idv_data/activity_set/*.txt')

# Transform the data files into a vocabulary vector
vectorizer = CountVectorizer(input='filename')
dtm = vectorizer.fit_transform(filenames)
vocab = vectorizer.get_feature_names()

# for reference, note the current class of `dtm`
type(dtm)
# Create a sparse matrix
scipy.sparse.csr.csr_matrix
dtm = dtm.toarray()  # convert to a regular array
vocab = np.array(vocab)

# "by hand"
n, _ = dtm.shape

dist = np.zeros((n, n))

for i in range(n):
    for j in range(n):
        x, y = dtm[i, :], dtm[j, :]
        dist[i, j] = np.sqrt(np.sum((x - y)**2))
        
# Use the Cosine similarity to compute the distance between points

# Normalize the cosine similarity
dist = 1 - cosine_similarity(dtm)

np.round(dist, 2)

# Normalise the cosine similartity using the dot product of each vector
norms = np.sqrt(np.sum(dtm * dtm, axis=1, keepdims=True))

dtm_normed = dtm / norms

similarities = np.dot(dtm_normed, dtm_normed.T)

np.round(similarities, 2)

# two components as we're plotting points in a two-dimensional plane
# "precomputed" because we provide a distance matrix
# we will also specify `random_state` so the plot is reproducible.
mds = MDS(n_components=2, dissimilarity="precomputed", random_state=1)

pos = mds.fit_transform(dist)  # shape (n_components, n_samples)

xs, ys = pos[:, 0], pos[:, 1]

# short versions of filenames:
names = [os.path.basename(fn).replace('.txt', '') for fn in filenames]

# two components as we're plotting points in a two-dimensional plane
# "precomputed" because we provide a distance matrix
# we will also specify `random_state` so the plot is reproducible.
mds = MDS(n_components=2, dissimilarity="precomputed", random_state=1)

pos = mds.fit_transform(dist)  # shape (n_components, n_samples)
xs, ys = pos[:, 0], pos[:, 1]

# short versions of filenames:
names = [os.path.basename(fn).replace('.txt', '') for fn in filenames]

# color-blind-friendly palette
for x, y, name in zip(xs, ys, names):
    color = 'orange'
    plt.scatter(x, y, c=color)
    # plt.text(x, y, name)

plt.show()

# Create a denodrogram
# from scipy.cluster.hierarchy import ward, dendrogram

# linkage_matrix = ward(dist)

# match dendrogram to that returned by R's hclust()
# dendrogram(linkage_matrix, orientation="right")

# plt.tight_layout()  # fixes margins

# plt.show()