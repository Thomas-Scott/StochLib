plotStats <- function(inputFileDirectory,indices) {
  # plot means and means +/- 1 standard deviations
  # inputFileDirectory: path to "stats" output directory
  # indices is a vector of species indices to plot
  
  # Example to run the function from $STOCHKIT_HOME
  # assuming ran dimer decay example model
  # plotStats('./models/examples/dimer_decay_output/stats',c(1,2,3)
  # where c(1,2,3) specifies printing species indexes 1,2 and 3
  
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
 
  # get file names
  fnameMean = paste(inputFileDirectory,'/means.txt',sep='');
  fnameVar =  paste(inputFileDirectory,'/variances.txt',sep='');
  
  #read the first line of the means file
  #and check for headers (labels)
  line1 <- strsplit(readLines(fnameMean,n=1),split="\t")[[1]]
  if (line1[1]=="time") {
    hasLabels=TRUE
  }
  else {
    hasLabels=FALSE
  }
  
  #get the means data
  meansData <- read.table(fnameMean,header=hasLabels)[,c(1,indices)]
  #give (slightly) more meaningful labels if none
  if (!hasLabels) {
    names(meansData) <- c("time",names(meansData)[1:(length(meansData)-1)])
  }
  #get the variances data
  variancesData <- read.table(fnameVar,header=hasLabels)[,c(1,indices)]
  #give (slightly) more meaningful labels if none
  if (!hasLabels) {
    names(variancesData) <- names(meansData)
  }
  
  #put data into plottable form
  meansDataMelted <- melt(meansData,id="time")
  p <- qplot(time,value,data=meansDataMelted,colour=variable) + geom_line() + ylab("population") + ggtitle("stats plot")
  # create mean+stdev data
  plusStdevData <- meansData
  plusStdevData[,2:ncol(plusStdevData)] <- plusStdevData[,2:ncol(plusStdevData)] + sqrt(variancesData[,2:ncol(variancesData)])
  plusStdevDataMelted <- melt(plusStdevData,id="time")
  p2 <- p + geom_line(dat=plusStdevDataMelted,linetype="dashed")
  # create mean-stdev data
  minusStdevData <- meansData
  minusStdevData[,2:ncol(minusStdevData)] <- minusStdevData[,2:ncol(minusStdevData)] - sqrt(variancesData[,2:ncol(variancesData)])
  minusStdevDataMelted <- melt(minusStdevData,id="time")
  p3 <- p2 + geom_line(dat=minusStdevDataMelted,linetype="dashed")
  return(p3)
}