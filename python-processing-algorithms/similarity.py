import os
import csv
import scipy
import glob
import numpy as np
import matplotlib.pyplot as plt

from sklearn.manifold import MDS
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.metrics.pairwise import cosine_similarity
from scipy.cluster.hierarchy import ward, dendrogram


# Rename a file if it exists. Replace it with the new filename passed in
# @return: void
def rename_file(old_filename,new_filename):
    path = '../data/idv_data/data_set/'
    if os.path.isfile(path+old_filename):
        old_file = path + old_filename
        new_file = path + new_filename
        os.rename(old_file,new_file)
    
# Obtain colour from given id
# @return: Colour as a string
def get_colour(id):
    switcher = {
        'Food_&_Wine' : '#458b74' , # Dark Aqua
        'Education' : '#8a2be2', # Blue Violet
        'History_&_Culture' : '#98f5ff', #Light Blue
        'Architecture' : '#ee3b3b', # Red
        'For_Couples' : '#66cd00', # Green
        'Photography': '#ffb90f', # Yellow
        'Livability_Research' : '#caff70', # Light Green
        'Kids_Friendly' : '#ff8c00', # Orange
        'Outdoor_&_Nature' : '#ff1493', # Pink
        'Shopping' : '#8b0a50', # Deep Pink
        'Sports_&_Leisure' : '#104e8b', # Dark Blue
        'Host_With_Car' : '#cd8c95', # Light Pink 
        'Extreme_Fun' : '#ee9572', # Salmon
        'Events' : '#cd919e', # Soft Pink
        'Health_&_Beauty' : '#6c7b8b', # Slate Gray
        'Private_Group' : '#008b45' # Spring Green
    }
    
    return switcher.get(id, '#858585') # Light Gray
     
# Obtain tag from given id
# @return: Tag as a string
def get_tag(id):
    switcher = {
        '201' : 'Food_&_Wine',
        '211' : 'Education',
        '221' : 'History_&_Culture',
        '231' : 'Architecture',
        '241' : 'For_Couples',
        '251' : 'Photography',
        '261' : 'Livability_Research',
        '271' : 'Kids_Friendly',
        '281' : 'Outdoor_&_Nature',
        '291' : 'Shopping',
        '301' : 'Sports_&_Leisure',
        '311' : 'Host_With_Car',
        '321' : 'Extreme_Fun',
        '331' : 'Events',
        '341' : 'Health_&_Beauty',
        '351' : 'Private_Group'
    }
    
    return switcher.get(id, 'Untagged')

# Calculate the Cosine Similairity, normalize the values into a distance metric in the form of
# a distance matrix. Then begin Multi-Dimensional Clustering given the distance matrix, with
# pre-computed parameters which will be used to generate a Scatter Plot and Dendrogram.
# @return: Scatter Plot and Dendogram generated in Matplotlib.pyplot
def calculate_and_cluster():
    
    # Variables for storing the data
    data_list = {}
    tag_list = {}
    counter = 0
    index = 0
    ptr = ""

    # Parse the CSV file (this will be denoted by a string variable)
    with open('../data/condensed_data/complete_data.csv','rb') as csvfile:
        reader = csv.reader(csvfile,delimiter=',')
        for row in reader:
            data_list[counter] = ''.join(row)
            counter +=1
            
    counter = 0        
    # Loop through data in range
    for data in range(0,len(data_list)):
        # Split the last token in the string
        split = data_list[data].split(" ")[-1:]
        # Maintain old file name (partial)
        file_old = str(counter) + '.txt'
        # Create a new file name with the tag appended
        file_new = str(counter) + '_' + get_tag(split[0]) + '.txt'
        # Rename the file for later use in color co-ordination
        rename_file(file_old,file_new)
        # Append the tag list so we can reference the tag later for colour
        tag_list[str(counter)] = get_tag(split[0])
        # Iterate the counter
        counter += 1
            
    # Filenames for training a corpus (appended with tag)
    filenames = glob.glob('../data/idv_data/data_set/*.txt')
    
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

    # Calculate cosine similarity
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

    # N Components: plotting points in a two-dimensional plane
    # Dissimilirity: "precomputed" because of the Distance Matrix
    # Random state is fixed so we can reproduce the plot.
    mds = MDS(n_components=2, dissimilarity="precomputed", random_state=1)

    pos = mds.fit_transform(dist)  # shape (n_components, n_samples)
    xs, ys = pos[:, 0], pos[:, 1]

    # short versions of filenames:
    names = [os.path.basename(fn).replace('.txt', '') for fn in filenames]
    
    # Loop through the points, label approriately and scatter
    for x, y, name in zip(xs, ys, names):
        color = 'orange'
        plt.scatter(x, y, s=100,c=get_colour(name.split('_',1)[1]))
        # plt.text(x,y,name.split('_', 1)[0])
    plt.show()

    # Create a denodrogram
    #linkage_matrix = ward(dist)

    # match dendrogram to that returned by R's hclust()
    #dendrogram(linkage_matrix, orientation="right")

    #plt.tight_layout()
    #plt.show()

# Start the main function when the program begins
if __name__ == "__main__":
    calculate_and_cluster()