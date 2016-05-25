import csv
import numpy as np
import matplotlib.pyplot as plt
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn import manifold

reader = csv.reader(open("semantic_similarity_matrix_reduced/matrix.csv","r"),delimiter=',')
data = list(reader)

dists = []
count = 0
for d in data:
    print "Row: ",count,d[count]
    dists.append(map(float,d[0:-1]))
    count += 1
vect = TfidfVectorizer(min_df=1)
tfidf = vect.fit_transform(dists)

mds = manifold.MDS(n_components=2, dissimilarity="precomputed",random_state=6)
results = mds.fit(tfidf * tfidf.T).A

coords = results.embedding_

plt.subplots_adjust(bottom = 0.1)
plt.scatter(
    coords[:, 0], coords[:,1], marker = 'o'
)

plt.show()
