# Import logging so I can track what is happening in computation
import logging
logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO)

# Import gensim. We need the copora model, general models and similarity libraries
from gensim import corpora, models, similarities

# Declare a test document vector
documents = ["Human machine interface for lab abc computer applications",
              "A survey of user opinion of computer system response time",
              "The EPS user interface management system",
              "System and human system engineering testing of EPS",
              "Relation of user perceived response time to error measurement",
              "The generation of random binary unordered trees",
              "The intersection graph of paths in trees",
              "Graph minors IV Widths of trees and well quasi ordering",
              "Graph minors A survey"]

# Remove common words and tokenize the vector
stoplist = set('for a of the and to in'.split())
texts = [[word for word in document.lower().split() if word not in stoplist]
        for document in documents]

# Remove words that only appear once in the documents vector
from collections import defaultdict
frequency = defaultdict(int)
for text in texts:
    for token in text:
        frequency[token] += 1
        
texts = [[token for token in text if frequency[token] > 1]
        for text in texts]

from pprint import pprint

# Begin dictionary defining
dictionary = corpora.Dictionary(texts)
dictionary.save('tmp/deerwest.dict')

# This will print the dictionary and the frequency of words within the vectors
# print(dictionary.token2.id)

# Create a sparse matrix of occurences against the dictionary
new_doc = "Human computer iteraction"
new_vec = dictionary.doc2bow(new_doc.lower().split())