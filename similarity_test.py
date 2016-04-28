import nltk
from nltk.corpus import wordnet as wn
n=wn.synsets('nice')
g=wn.synsets('good')
[g[i].path_similarity(n[0]) for i in range(len(g))]
