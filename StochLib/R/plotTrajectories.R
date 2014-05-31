plotTrajectories <- function(inputFileDirectory,startn,endn,indices) {
  # plot trajectory output
  # plot trajectory number startn through endn from
  # the trajectories.txt file in inputFileDirectory
  # indices indicate which species to plot. For example,
  # to plot trajectories of 4th,7th, and 10th species
  # set indices=c(4, 7,10).
  
  # Example to run the function from $STOCHKIT_HOME
  # plotTrajectories('./models/examples/dimer_decay_output/trajectories',0,9,c(1,2,3))
  # where 0,9 means trajectories 0 through 9 (note trajectory indexes start at 0)
  # and where c(1,2,3) means species indexes 1,2,3 (note species indexes start at 1)

  if ((round(startn)!=startn) | (round(endn) != endn)) {
    stop('Need integer numbers for input file indexing')
  }
  if (startn > endn) {
    stop('start file index is larger than the end file index')
  }
  if (length(indices)==0) {
    stop('indices vector must not be empty')
  }
  
  # Check to make sure that the indices are integers
  if (sum((round(indices)==indices)) != length(indices)) {
    stop('Indexes must be integers')
  }
  
  # Check to make sure that the indices are greater than 0
  if (min(indices)<=0) {
    stop('Indexes must be positive integers')
  }
  
  # Check to eliminate duplicate indices
  indices2 = unique(indices);
  if (length(indices2)!=length(indices)) {
    warning(paste("removing ",length(indices) - length(indices2), " duplicate indexes."))
    indices=indices2;
  }
  
  indices = indices+1; # add 1 to account for the time column
  indices = sort(indices);
  len_indices =length(indices);
 
  # PROCESSED TO HERE...
    
  #read the first line of the first file
  #and check for headers (labels)  
  fileName <- paste(inputFileDirectory,"/trajectory",startn,".txt",sep="")
  line1 <- strsplit(readLines(fileName,n=1),split="\t")[[1]]
  if (line1[1]=="time") {
    hasLabels=TRUE
  }
  else {
    hasLabels=FALSE
  }
  
  #plot data...
  fileName <- paste(inputFileDirectory,"/trajectory",startn,".txt",sep="")
  trajData <- read.table(fileName,header=hasLabels)[,c(1,indices)]
  #give (slightly) more meaningful labels if none
  if (!hasLabels) {
    names(trajData) <- c("time",names(trajData)[1:(length(trajData)-1)])
  }

  trajDataMelted <- melt(trajData,id="time")
  p <- qplot(time,value,data=trajDataMelted,colour=variable,geom="line") + ylab("population") + ggtitle("trajectory plot")
  
  # plot the rest of the trajectories!
  if (startn < endn) {
    for (i in (startn+1):endn) {
      fileName <- paste(inputFileDirectory,"/trajectory",i,".txt",sep="")
      trajData <- read.table(fileName,header=hasLabels)[,c(1,indices)]
      #give (slightly) more meaningful labels if none
      if (!hasLabels) {
        names(trajData) <- c("time",names(trajData)[1:(length(trajData)-1)])
      }
      
      trajDataMelted2 <- melt(trajData,id="time")
      p <- p + geom_line(data=trajDataMelted2)
    }
  }
  return(p)
}