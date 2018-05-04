#!python

import sys

h1 = .1
h2 = .2
h3 = .4
h4 = .2
h5 = .1
h1c = .1
h2c = .75
h3c = .5
h4c = .25
h5c = 0
cGq = .5


def getInput():
    if len(sys.argv) < 2:    
        print('No input given')
        return ''
    else:
        return sys.argv[1]

def calculations(observations):
    global h1, h2, h3, h4, h5
    global h1c, h2c, h3c, h4c, h5c
    global cGq
    for i in range(len(observations)):
        px = ((h1 * h1c) + (h2 * h2c) + (h3 * h3c) + (h4 * h4c) + (h5 * h5c)) 
        if observations[i] == 'C':
            h1 = (h1c * h1 / px)
            h2 = (h2c * h2 / px)
            h3 = (h3c * h3 / px)
            h4 = (h4c * h4 / px)
            h5 = (h5c * h5 / px)
        elif observations[i] == 'L':
            h1 = (((1-h1c) * (h1)) / px)
            h2 = (((1-h2c) * (h2)) / px)
            h3 = (((1-h3c) * (h3)) / px)
            h4 = (((1-h4c) * (h4)) / px)
            h5 = (((1-h5c) * (h5)) / px)
        else:
            """ ¯\_(ツ)_/¯ """
            
        cGq = ((h1 * h1c) + (h2 * h2c) + (h3 * h3c) + (h4 * h4c) + (h5 * h5c))
        return observations
        
def printToFile(output):
    f = open('result.txt', 'w')
    f.write("Observation sequence Q: " + output + '\n')
    f.write("Length of Q: "+ str(len(output)) + '\n\n')
    f.write("P(h1 | Q) = %.5f " %(h1) + '\n')
    f.write("P(h2 | Q) = %.5f " %(h2) + '\n')
    f.write("P(h3 | Q) = %.5f " %(h3) + '\n')
    f.write("P(h4 | Q) = %.5f " %(h4) + '\n')
    f.write("P(h5 | Q) = %.5f " %(h5) + '\n\n')
    f.write("Probability that the next candy we pick will be C, given Q: %.5f " %cGq + '\n')
    f.write("Probability that the next candy we pick will be L, given Q: %.5f " %(1-cGq) + '\n')
    f.close()
    
    print("Oboutputervation sequence Q: " + output)
    print("Length of Q: "+ str(len(output)) + '\n')
    print("P(h1 | Q) = %.5f " %(h1))
    print("P(h2 | Q) = %.5f " %(h2))
    print("P(h3 | Q) = %.5f " %(h3))
    print("P(h4 | Q) = %.5f " %(h4))
    print("P(h5 | Q) = %.5f " %(h5) + '\n')
    print("Probability that the next candy we pick will be C, given Q: %.5f " %cGq)
    print("Probability that the next candy we pick will be L, given Q: %.5f " %(1-cGq))

           
printToFile(calculations(getInput()))