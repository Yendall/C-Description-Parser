
Acknowledgements:
------
C++ CSV Parser Header       : Rakesh G. Karanth

C++ Data Categorisation     : Max Yendall & Georgia Clark

TODO:
------
1. Condense data down to meaningful words using filters and output the data into new condense_files ✓
2. Create vectors with combined words from the data set for each field. ✓
3. Create a duplicate data set and compare each data entry against each other by taking the frequency of occurence in the combined vector for each individual field.
4. Multiply the frequency of each occurence against each other to find the similarity value for each word
5. Normalise the similarity value Σ x[i] * y[i]. Normalise Function: wi = xi - (min(x) / (max(x)-min(x)))
6. Find the Euclidean Distance between the normalised vector values
7. ~~Get a similarity value by taking the Cosin value of the Euclidean Distance (1 - Cosin)~~
