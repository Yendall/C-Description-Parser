import numpy as np
from sklearn.feature_extraction.text import CountVectorizer
import scipy
import glob

# Filenames for training a corpus
# filenames = ['data/austen-bronte/Austen_Emma.txt',
#             'data/austen-bronte/Austen_Pride.txt',
#             'data/austen-bronte/Austen_Sense.txt',
#             'data/austen-bronte/CBronte_Jane.txt',
#             'data/austen-bronte/CBronte_Professor.txt',
#             'data/austen-bronte/CBronte_Villette.txt']
filenames = glob.glob('data/idv_data/title_set/*.txt')


# Transform the data files into a vocabulary vector
vectorizer = CountVectorizer(input='filename')
dtm = vectorizer.fit_transform(filenames)
vocab = vectorizer.get_feature_names()
print 
# for reference, note the current class of `dtm`
type(dtm)
scipy.sparse.csr.csr_matrix
dtm = dtm.toarray()  # convert to a regular array
vocab = np.array(vocab)

# use the standard Python list method index(...)
# list(vocab) or vocab.tolist() will take vocab (an array) and return a list
house_idx = list(vocab).index('house')

print dtm[0, house_idx]

# using NumPy indexing will be more natural for many
# in R this would be essentially the same, dtm[1, vocab == 'house']
print dtm[0, vocab == 'house']

# "by hand"
n, _ = dtm.shape

dist = np.zeros((n, n))

for i in range(n):
    for j in range(n):
        x, y = dtm[i, :], dtm[j, :]
        dist[i, j] = np.sqrt(np.sum((x - y)**2))
        

from sklearn.metrics.pairwise import euclidean_distances

dist = euclidean_distances(dtm)

np.round(dist, 1)

# *Pride and Prejudice* is index 1 and *Jane Eyre* is index 3
filenames[1] == 'data/austen-bronte/Austen_Pride.txt'
filenames[3] == 'data/austen-bronte/CBronte_Jane.txt'
# the distance between *Pride and Prejudice* and *Jane Eyre*
print dist[1, 3]

# which is greater than the distance between *Jane Eyre* and *Villette* (index 5)
print dist[1, 3] > dist[3, 5]

from sklearn.metrics.pairwise import cosine_similarity

dist = 1 - cosine_similarity(dtm)

np.round(dist, 2)

# the distance between *Pride and Prejudice* (index 1)
# and *Jane Eyre* (index 3) is
dist[1, 3]

# which is greater than the distance between *Jane Eyre* and
# *Villette* (index 5)
dist[1, 3] > dist[3, 5]

norms = np.sqrt(np.sum(dtm * dtm, axis=1, keepdims=True))  # multiplication between arrays is element-wise

dtm_normed = dtm / norms

similarities = np.dot(dtm_normed, dtm_normed.T)

np.round(similarities, 2)
# similarities between *Pride and Prejudice* and *Jane Eyre* is
print similarities[1, 3]

import os  # for os.path.basename

import matplotlib.pyplot as plt

from sklearn.manifold import MDS

# two components as we're plotting points in a two-dimensional plane
# "precomputed" because we provide a distance matrix
# we will also specify `random_state` so the plot is reproducible.
mds = MDS(n_components=2, dissimilarity="precomputed", random_state=1)

pos = mds.fit_transform(dist)  # shape (n_components, n_samples)

xs, ys = pos[:, 0], pos[:, 1]

# short versions of filenames:
# convert 'data/austen-bronte/Austen_Emma.txt' to 'Austen_Emma'
names = [os.path.basename(fn).replace('.txt', '') for fn in filenames]

import os  # for os.path.basename
import matplotlib.pyplot as plt
from sklearn.manifold import MDS

# two components as we're plotting points in a two-dimensional plane
# "precomputed" because we provide a distance matrix
# we will also specify `random_state` so the plot is reproducible.
mds = MDS(n_components=2, dissimilarity="precomputed", random_state=1)

pos = mds.fit_transform(dist)  # shape (n_components, n_samples)
xs, ys = pos[:, 0], pos[:, 1]

# short versions of filenames:
# convert 'data/austen-bronte/Austen_Emma.txt' to 'Austen_Emma'
names = [os.path.basename(fn).replace('.txt', '') for fn in filenames]

# color-blind-friendly palette
for x, y, name in zip(xs, ys, names):
    color = 'orange' if "Austen" in name else 'skyblue'
    plt.scatter(x, y, c=color)
    plt.text(x, y, name)

plt.show()

# Create a denodrogram
# from scipy.cluster.hierarchy import ward, dendrogram

# linkage_matrix = ward(dist)

# match dendrogram to that returned by R's hclust()
# dendrogram(linkage_matrix, orientation="right", labels=names)

# plt.tight_layout()  # fixes margins

# plt.show()