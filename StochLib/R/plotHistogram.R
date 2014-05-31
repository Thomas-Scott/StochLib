plotHistogram <- function(inputFileName) {
  # plot a histogram by reading from a histogram file
  # example call from $STOCHKIT_HOME directory:
  # plotHistogram('./models/examples/dimer_decay_output/histograms/hist_S2_3.dat')
  # the histogram file naming convention is: hist_S<species index>_<time interval>,
  # the above prints a histogram of the 2nd species (species indexes starts at 1)
  # at the 3rd time interval (time indexes starts at 0)
  
  # read in the lines 
  lines <- strsplit(readLines(inputFileName),split="\t")
  sID <- lines[[1]][1] # species ID
  time = as.numeric(lines[[1]][2]) # time
  sInd = as.numeric(lines[[1]][2]) # species index
  tInd = as.numeric(lines[[1]][3]) # time index

  lb = as.numeric(lines[[2]][1]) # lower bound
  ub = as.numeric(lines[[2]][2]) # upper bound
  width = as.numeric(lines[[2]][3]) # width
  bsize = as.numeric(lines[[2]][4]) # number of bins

  # read in the third line (bin counts)
  data = as.numeric(lines[[3]])
  # error checking
  if (bsize!=length(data)) {
    stop('retrieved size of bins are not equal to the number of bins in the data line')
  }

  dataRange <- seq(lb,ub,by=width)
  bincenters <- (dataRange[-1] + dataRange[-length(dataRange)])/2
  df <- data.frame(centers=bincenters,counts=data)
  
  ggplot(dat=df,aes(x=centers,y=counts)) + geom_bar(stat="identity",width=width,colour="dark blue",fill="dark blue") + ylab("Bin Counts") + xlab("Bin Centers") + ggtitle(paste("Species:",sID," Time:",time))
}