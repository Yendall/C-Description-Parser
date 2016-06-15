
Acknowledgements:
------
##### C++ CSV Parser Header:
###### Rakesh G. Karanth

##### C++ Data Pre-Processor Header:
###### Max Yendall & Georgia Clark

##### Python Cosine/Semantic Similarity:
###### Max Yendall & Georgia Clar


Pipeline:
------
1. Condense data down to meaningful words using filters and output the data into new condense_files ✓
2. Create vectors with combined words from the data set for each field. ✓
3. Compute the Cosine Similarity between data sets ✓
4. Normalize the Cosine Similarity and cluster it as a distance metric ✓
5. Tag untagged data based on Cosine Distance Metric ✓
6. Compute the Semantic Similarity between data sets ✓
7. Normalize the Semantic Similarity and cluster it as a distance metric ✓
8. Tag untagged data based on Semantic Similarity Metric ✓

Usage:
------
### C++ Pre-Processor:

##### Location:
###### Root Directory
##### Mandatory Command:
###### make (Makefile)
##### Usage:
###### ./data_parser --p

### Python Semantic REST API:

##### Location:
###### /python-processing_algorithms/semantic_similarity_algorithms
##### Usage:
###### python semantic_REST_similarity.py

### Python Semantic Similarity Processor:

##### Pre-Requisites:
###### Must have individual data files in CSV format (can be changed to suit implementation)
##### Location:
###### /python-processing_algorithms/semantic_similarity_matrix
##### Usage:
###### python semantic_similarity.py


