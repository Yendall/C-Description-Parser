from requests import get
import csv

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
        print 'Error in getting similarity for %s: %s' % ((s1,s2), response)
        return 0.0
    
# Function which begins the tokenisation of sets and begins returning similarities in a map
# @return: void
def parse_data():
    
    # Variables for storing the data
    counter = 0
    data_list = {}
    data_map = {}
    
    # Parse the CSV file (this will be denoted by a string variable)
    with open('data/condensed_description_set.csv','rb') as csvfile:
        reader = csv.reader(csvfile,delimiter=',')
        for row in reader:
            data_list[counter] = ''.join(row)
            counter +=1
    
    # Populate the data map with key = index, value = list_copy
    for x in range(0,len(data_list)):
        data_map[x] = data_list

    # Iterate through the data map and fetch the similarity for each pair
    for key,value in data_map.iteritems():
        print key
        print '-------NEW_SENTENCE-------'
        for x in range(0,len(value)):
            print sss(data_list[key],value[x])
              
# Start the main function when the program begins
if __name__ == "__main__":
    parse_data()
    