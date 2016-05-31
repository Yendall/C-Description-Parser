from requests import get
from functools import partial
from multiprocessing.pool import ThreadPool as Pool
import csv
import sys

# Track the data index
DataTracker = 0
# list of POIs
DataList = []
# similarity matrix
Matrix = {}
# Define the swoogle API for similarity
sss_url = "http://swoogle.umbc.edu/SimService/GetSimilarity"

# Function which uses the Stanford Web Base corpus and returns a similarity between two phrases
# @param:   s1 = first phrase, s2 = second phrase
# @return:  Semantic Similarity between the two phrases
def sss(s1, s2, type='relation', corpus='webbase'):
    # Call the REST API and ask for a return
    try:
        # Success state
        response = get(sss_url, params={'operation':'api','phrase1':s1,'phrase2':s2,'type':type,'corpus':corpus})
        return float(response.text.strip())
    except:
        # Error state
        return 0.0

# Function which begins the tokenisation of sets and begins returning similarities in a map
# @return: void
def parse_data():
    # Variables for storing the data
    counter = 0
    # Parse the CSV file (this will be denoted by a string variable)
    with open('../data/combined_data/combined_set.csv','rb') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            DataList.append(''.join(row))
            counter +=1

# Function which harvests the data lists and returns the API result as a map of values
# @return: Map of Similarities
def harvester(text, case):
    X = case[DataTracker]
    response = sss(str(X), text)
    return response

# Start the main function when the program begins
if __name__ == "__main__":
    # Define stdout
    orig_stdout = sys.stdout
    parse_data()
    List = DataList
    partial_harvester = partial(harvester, case=List)

    pool = Pool(processes=10)
    case_data = List
    print "I am processing.... I will take a long time... Make a coffee... Watch Game of Thrones"
    for x in range(0,len(DataList)):
        print "Processing row: ",DataTracker
        # Set the DataTracker variable to the index iterable in the DataList
        DataTracker = x
        # Open the file associated with the DataTracker
        _file = open(str(x)+".txt","w+")
        # Redirect stdout to the file
        sys.stdout = _file
        print pool.map(partial_harvester, case_data, 64)
        sys.stdout = orig_stdout
        _file.close()
    pool.close()
    pool.join()