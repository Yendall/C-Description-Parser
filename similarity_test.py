from nltk.corpus import wordnet as wn
right = wn.synset('right_whale.n.01')
right.path_similarity(minke)

