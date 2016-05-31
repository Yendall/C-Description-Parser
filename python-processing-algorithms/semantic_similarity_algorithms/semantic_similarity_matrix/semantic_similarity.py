import os
import csv
import numpy as np
from numpy import genfromtxt
import matplotlib.pyplot as plt

from sklearn.manifold import MDS
from sklearn.feature_extraction.text import TfidfVectorizer
from scipy.cluster.hierarchy import ward, dendrogram
from collections import OrderedDict

# Lists for storing the data
global data_list
global data_tag_map
global matrix_list
global data_tagged_list
data_list           = {}
data_tag_map        = {}
data_tagged_list    = {}
matrix_list         = []

# Tag the nearest neighbour to a node and update the global map
# @params: index
# @return: tagged set
def tag_nearest_neighbour(index):
    global matrix_list

    # Track semantic measurement
    semantic_measure = 0.0
    # Track current row ID
    row_id = 0
    # Track the index of the current element in the matrix row
    count = 0

    # Loop through the row of the index we are analysing
    for x in matrix_list[index]:
        # If the element is not itself or if the element is greater than the current semantic measure
        # Assign the semantic measure. Ensure that the element is tagged because we can't inherit from
        # untagged nodes
        if (x != 1.0) and (x > semantic_measure) and get_tagged(str(count)):
            semantic_measure = x
            row_id = count
            split = data_list[row_id].split(" ")[-1:]

            data_tagged_list[index] = True
            data_tag_map[index] = data_tag_map[split[0]]
            print semantic_measure
            print data_tagged_list[index]
            print data_tag_map[index]
            print str(index) + " is now tagged"
        count += 1

# Rename a file if it exists. Replace it with the new filename passed in
# @params: old_filename: String, new_filename : String
# @return: void
def rename_file(old_filename, new_filename):
    path = '../data/idv_data/data_set/'
    if os.path.isfile(path + old_filename):
        old_file = path + old_filename
        new_file = path + new_filename
        os.rename(old_file, new_file)


# Symmetrize matrix
# @params: nparray
# @return: symmetric nparray
def symmetrize(a):
    return a + a.T - np.diag(a.diagonal())


# Obtain colour from the given ID
# @params: id : String
# @return: Colour as a string
def get_colour_tag(id):
    switcher = {
        'Tagged': '#FFFFB7',  # Yellow
    }
    return switcher.get(id, '#d3d3d3')  # Light Gray


# Obtain colour from the given ID
# @params: id : String
# @return: Colour as a string
def get_colour(id):
    switcher = {
        'Food_&_Wine': '#458b74',  # Dark Aqua
        'Education': '#8a2be2',  # Blue Violet
        'History_&_Culture': '#98f5ff',  # Light Blue
        'Architecture': '#ee3b3b',  # Red
        'For_Couples': '#66cd00',  # Green
        'Photography': '#ffb90f',  # Yellow
        'Livability_Research': '#caff70',  # Light Green
        'Kids_Friendly': '#ff8c00',  # Orange
        'Outdoor_&_Nature': '#ff1493',  # Pink
        'Shopping': '#8b0a50',  # Deep Pink
        'Sports_&_Leisure': '#104e8b',  # Dark Blue
        'Host_With_Car': '#cd8c95',  # Light Pink
        'Extreme_Fun': '#ee9572',  # Salmon
        'Events': '#cd919e',  # Soft Pink
        'Health_&_Beauty': '#6c7b8b',  # Slate Gray
        'Private_Group': '#b3d9ff'  # Medium Blue
    }

    return switcher.get(id, '#d3d3d3')  # Light Gray

# Obtain boolean value denoting whether this data set is tagged or not
# @params: id : String
# @return: Bool
def get_tagged(id):
    return data_tagged_list[id]

# Obtain tag from given id
# @params: id : String
# @return: Tag as a string
def get_tag(id):
    switcher = {
        '201': 'Food_&_Wine',
        '211': 'Education',
        '221': 'History_&_Culture',
        '231': 'Architecture',
        '241': 'For_Couples',
        '251': 'Photography',
        '261': 'Livability_Research',
        '271': 'Kids_Friendly',
        '281': 'Outdoor_&_Nature',
        '291': 'Shopping',
        '301': 'Sports_&_Leisure',
        '311': 'Host_With_Car',
        '321': 'Extreme_Fun',
        '331': 'Events',
        '341': 'Health_&_Beauty',
        '351': 'Private_Group'
    }

    return switcher.get(id, 'Untagged')


# Obtain tag set from given id
# @params: id : String
# @return: Tags as a list
def get_tag_set(id):
    tag_list = []
    file_name = id + '.csv'
    with open('../../../data/data_tags/' + file_name, 'rb') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        for row in reader:
            tag_list.append(row)

    return tag_list


# Calculate the Cosine Similairity, normalize the values into a distance metric in the form of
# a distance matrix. Then begin Multi-Dimensional Clustering given the distance matrix, with
# pre-computed parameters which will be used to generate a Scatter Plot and Dendrogram.
# @return: Scatter Plot and Dendogram generated in Matplotlib.pyplot
def calculate_and_cluster():

    global data_list
    global data_tag_map
    global matrix_list
    global data_tagged_list
    counter = 0
    # Parse the CSV file (this will be denoted by a string variable)
    with open('../../../data/sets/complete_set.csv', 'rb') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')
        for row in reader:
            data_list[counter] = ''.join(row)
            counter += 1

    # Loop through data in range
    for data in range(0, len(data_list)):
        # Split the last token in the string
        split = data_list[data].split(" ")[-1:]
        # print split[0], "Tag set: ", get_tag_set(split[0])
        data_tag_map[split[0]] = get_tag_set(split[0])
    od = OrderedDict(sorted(data_tag_map.items()))

    names = []
    counter = 0
    for key, value in od.iteritems():
        # Maintain old file name
        file_old = str(counter) + '.txt'
        tag = ''
        if len(value) == 1:
            tag = 'Tagged'
            names.append(str(counter) + "_" + tag)
            data_tagged_list[str(counter)] = True
        else:
            tag = 'Untagged'
            names.append(str(counter) + "_" + tag)
            data_tagged_list[str(counter)] = False

        # Create new file name with tagged / untagged appended
        file_new = str(counter) + '_' + tag + '.txt'
        # Rename the file for later use in color co-ordination
        rename_file(file_old, file_new)
        counter += 1

    #print data_tag_map
    #print data_tagged_list

    dataNodes = []
    for x in range(0, len(data_list)):
        dataNodes.append(data_list[x])

    # Generate matrix from file
    X = genfromtxt('matrix.csv', delimiter=',')

    # Symmetrize X to ensure the matrix is valid
    X = symmetrize(X)

    # Put matrix in a list for checking
    matrix_list = X.tolist()

    for x in range(0,len(matrix_list)):
        tagged = get_tagged(str(x))
        if(not tagged):
            tag_nearest_neighbour(x)

    # Check symmetry
    print "Symmetric? " + str((X.transpose() == X).all())
    # N Components: plotting points in a two-dimensional plane
    # Dissimilirity: "precomputed" because of the Distance Matrix
    # Random state is fixed so we can reproduce the plot.
    mds = MDS(n_components=2, dissimilarity="precomputed", random_state=1)
    mds.fit(X.astype(np.float64))
    pos = mds.fit_transform(X)  # shape (n_components, n_samples)
    xs, ys = pos[:, 0], pos[:, 1]

    # Set figure size to have dimensions of at least 15 inches for the width.
    # Height can be scaled accordingly.
    plt.figure(figsize=(15, 8))
    plt.subplot(211)

    # Loop through the points, label approriately and scatter
    # Ensure figure size has enough room for legend plotting. Each plot must have a label.
    # In this case, label is the split value denoting the POI tag

    for x, y, name in zip(xs, ys, names):
        plt.scatter(x, y, s=100, c=get_colour_tag(name.split('_', 1)[1]), label=name.split('_', 1)[1])
        plt.text(x,y,name.split('_',1)[0])
    handles, labels = plt.gca().get_legend_handles_labels()
    by_label = OrderedDict(zip(labels, handles))
    legend = plt.legend(by_label.values(), by_label.keys(), loc='lower center', ncol=4, bbox_to_anchor=(0.5, -0.6))

    plt.show()

    # Create a denodrogram
    linkage_matrix = ward(X)

    # match dendrogram to that returned by R's hclust()
    dendrogram(linkage_matrix, orientation="right")
    plt.tight_layout()
    plt.show()


# Start the main function when the program begins
if __name__ == "__main__":
    calculate_and_cluster()