import pprint, time
startstart = time.clock()

start = time.clock()
import nltk
print "Importing nltk takes", str((time.clock()-start)),"secs"

start = time.clock()
tokenizer = nltk.tokenize.RegexpTokenizer(r'\w+|[^\w\s]+')
tagger = nltk.UnigramTagger(nltk.corpus.brown.tagged_sents())
print "Training time:",str((time.clock()-start)),"secs"


text = """Mr Blobby is a fictional character who featured on Noel
Edmonds' Saturday night entertainment show Noel's House Party,
which was often a ratings winner in the 1990s. Mr Blobby also
appeared on the Jamie Rose show of 1997. He was designed as an
outrageously over the top parody of a one-dimensional, mute novelty
character, which ironically made him distinctive, absurd and popular.
He was a large pink humanoid, covered with yellow spots, sporting a
permanent toothy grin and jiggling eyes. He communicated by saying
the word "blobby" in an electronically-altered voice, expressing
his moods through tone of voice and repetition.

There was a Mrs. Blobby, seen briefly in the video, and sold as a
doll.

However Mr Blobby actually started out as part of the 'Gotcha'
feature during the show's second series (originally called 'Gotcha
Oscars' until the threat of legal action from the Academy of Motion
Picture Arts and Sciences[citation needed]), in which celebrities
were caught out in a Candid Camera style prank. Celebrities such as
dancer Wayne Sleep and rugby union player Will Carling would be
enticed to take part in a fictitious children's programme based around
their profession. Mr Blobby would clumsily take part in the activity,
knocking over the set, causing mayhem and saying "blobby blobby
blobby", until finally when the prank was revealed, the Blobby
costume would be opened - revealing Noel inside. This was all the more
surprising for the "victim" as during rehearsals Blobby would be
played by an actor wearing only the arms and legs of the costume and
speaking in a normal manner.[citation needed]"""

start = time.clock()
tokenized = tokenizer.tokenize(text)
tagged = tagger.tag(tokenized)
print "Tagging time:",str((time.clock()-start)),"secs"

start = time.clock()
tagged.sort(lambda x,y:cmp(x[1],y[1]))
print "Sorting time:",str((time.clock()-start)),"secs"

l = list(set(tagged))
pprint.pprint(l)
print
print "Total time:",str((time.clock()-startstart)),"secs"