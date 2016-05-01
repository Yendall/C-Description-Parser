from requests import get

# Define the swoogle API for similarity
sss_url = "http://swoogle.umbc.edu/SimService/GetSimilarity"

# Function which uses the Stanford Web Base corpus and returns a similarity between two phrases
# @return: Semantic Similarity between the two phrases
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
    
print(sss('A small violin is being played by a girl','a child is performing on a tiny instrument'))