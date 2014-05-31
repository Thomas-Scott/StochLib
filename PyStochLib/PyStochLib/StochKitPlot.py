import matplotlib.pyplot as pp
import numpy as np
import warnings
import random

def plotStats(inputFileDirectory,indices):
    # plot means and means +/- 1 standard deviations
    # inputFileDirectory: path to "stats" output directory
    # indices is a vector of species indices to plot

    # Example to run the function from $STOCHKIT_HOME
    # assuming ran dimer decay example model
    # plotStats('./models/examples/dimer_decay_output/stats',[1,2,3])
    # where [1,2,3] specifies printing species indexes 1,2 and 3

    meansFileName = inputFileDirectory+"/means.txt"
    
    if (min(indices)<1):
        raise Exception('Indices must be positive integers.')
        
    #check that all indices are integers
    for i in indices:
        if not(isinstance(i,(int,long))):
            raise Exception('Indices must be integers.')
    
    originalIndices = indices
    indices = sorted(set(indices))

    if (len(indices)!=len(originalIndices)):
        warnings.warn("Deleted "+str(len(originalIndices)-len(indices))+" duplicate indices")

    # see if file contains column labels
    f = open(meansFileName, 'r')
    dataline1 = f.readline()
        
    splitDataLine1 = dataline1.split("\t") # note contains '\n' as last element
    if splitDataLine1[0]=='time':
        hasLabels=True
    else:
        hasLabels=False

    # build a list of species labels
    speciesLabels = []
    if hasLabels:
        for i in indices:
            speciesLabels.append(splitDataLine1[i])
    else:
        for i in indices:
            speciesLabels.append("S"+str(i))

    variancesFileName = inputFileDirectory+"/variances.txt"

    # read in means and variances data
    if hasLabels:
        meansData = np.loadtxt(meansFileName,skiprows=1)
        variancesData = np.loadtxt(variancesFileName,skiprows=1)
    else:
        meansData = np.loadtxt(meansFileName)
        variancesData = np.loadtxt(variancesFileName)
        
    colors = [  (0,0,1), (1,0,0), (0,1,0), (1,0,1), \
        (0,1,1), (0,0,0), (1,1,0), (0.6377,0.9577,0.2407), \
        (0.8754, 0.5181, 0.9436), (0.6951, 0.0680, 0.2548)]

    if (len(indices)<=len(colors)):
        colorCounter=0
        for i in range(0,len(indices)):
            plotLine = pp.plot(meansData[:,0],meansData[:,indices[i]])
            pp.setp(plotLine,color=colors[colorCounter],label=speciesLabels[i])
            plotLine = pp.plot(meansData[:,0],np.array(meansData[:,indices[i]])+np.sqrt(np.array(variancesData[:,indices[i]])))
            pp.setp(plotLine,color=colors[colorCounter],linestyle='--')
            plotLine = pp.plot(meansData[:,0],np.array(meansData[:,indices[i]])-np.sqrt(np.array(variancesData[:,indices[i]])))
            pp.setp(plotLine,color=colors[colorCounter],linestyle='--')
            colorCounter+=1
    else:
        # we have more indexes than colors...
        for i in range(0,len(colors)):
            plotLine = pp.plot(meansData[:,0],meansData[:,indices[i]],label=speciesLabels[i])
            pp.setp(plotLine,color=colors[i])
            plotLine = pp.plot(meansData[:,0],np.array(meansData[:,indices[i]])+np.sqrt(np.array(variancesData[:,indices[i]])))
            pp.setp(plotLine,color=colors[i],linestyle='--')
            plotLine = pp.plot(meansData[:,0],np.array(meansData[:,indices[i]])-np.sqrt(np.array(variancesData[:,indices[i]])))
            pp.setp(plotLine,color=colors[i],linestyle='--')
        for i in range(len(colors),len(indices)):
            # plot the remaining indices in a random color
            randomColor = [random.uniform(0,1),random.uniform(0,1),random.uniform(0,1)]
            plotLine = pp.plot(meansData[:,0],meansData[:,indices[i]],label=speciesLabels[i])
            pp.setp(plotLine,color=randomColor)
            plotLine = pp.plot(meansData[:,0],np.array(meansData[:,indices[i]])+np.sqrt(np.array(variancesData[:,indices[i]])))
            pp.setp(plotLine,color=randomColor,linestyle='--')
            plotLine = pp.plot(meansData[:,0],np.array(meansData[:,indices[i]])-np.sqrt(np.array(variancesData[:,indices[i]])))
            pp.setp(plotLine,color=randomColor,linestyle='--')
    
    pp.ylabel("population")
    pp.xlabel("time")
    pp.title("stats plot")
    pp.legend()
    pp.show()
    
#plotStats("/Users/sanft/Dropbox/StochKit2.0.7/models/examples/dimer_decay_output/stats/",[2,1.1])
#plotStats("/Users/sanft/Dropbox/StochKit2.0.7/models/examples/bad_path/stats/",[2,1])
# plotStats("/Users/sanft/Dropbox/StochKit2.0.7/models/examples/dimer_decay_output_labels/stats/",[2,3])
# plotStats("/Users/sanft/Dropbox/StochKit2.0.7/models/examples/dimer_decay_output/stats/",[2,3])
# plotStats("/Users/sanft/Dropbox/StochKit2.0.7/models/examples/dimer_decay_output/stats/",[2,3])
#plotStats("/Users/sanft/Dropbox/StochKit2.0.7/models/examples/heat_shock_mass_action_output/stats",range(1,15))
#plotStats("/Users/sanft/Dropbox/StochKit2.0.7/models/examples/heat_shock_mass_action_output/stats",[1,2,3,4,5,8,9,11,12,13,14,15,18,19])
