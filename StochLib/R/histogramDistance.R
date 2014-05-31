histogramDistance <- function(inputFileName1,inputFileName2) {
  # plot a histogram by reading form an input file fname 
  # example call from $STOCHKIT_HOME:
  # histogramDistance('./models/examples/dimer_decay_output/histograms/hist_S2_3.dat','../../models/examples/dimer_decay_output2/histograms/hist_S2_3.dat')
  # note that the files have different paths
  
  # read in the lines for the first data 
  lines1 <- strsplit(readLines(inputFileName1),split="\t")
  sID1 <- lines1[[1]][1] # species ID
  time1 = as.numeric(lines1[[1]][2]) # time
  sInd1 = as.numeric(lines1[[1]][2]) # species index
  tInd1 = as.numeric(lines1[[1]][3]) # time index

  lb1 = as.numeric(lines1[[2]][1]) # lower bound
  ub1 = as.numeric(lines1[[2]][2]) # upper bound
  width1 = as.numeric(lines1[[2]][3]) # width
  bsize1 = as.numeric(lines1[[2]][4]) # number of bins

  # read in the third line (bin counts)
  data1 = as.numeric(lines1[[3]])
  # error checking
  if (bsize1!=length(data1)) {
    stop('retrieved size of bins are not equal to the number of bins in the data line')
  }

  dataRange1 <- seq(lb1,ub1,by=width1)
  bincenters1 <- (dataRange1[-1] + dataRange1[-length(dataRange1)])/2
  df1 <- data.frame(centers=bincenters1,counts=data1)

  #read in second file
  lines2 <- strsplit(readLines(inputFileName2),split="\t")
  sID2 <- lines2[[1]][1] # species ID
  time2 = as.numeric(lines2[[1]][2]) # time
  sInd2 = as.numeric(lines2[[1]][2]) # species index
  tInd2 = as.numeric(lines2[[1]][3]) # time index
  
  lb2 = as.numeric(lines2[[2]][1]) # lower bound
  ub2 = as.numeric(lines2[[2]][2]) # upper bound
  width2 = as.numeric(lines2[[2]][3]) # width
  bsize2 = as.numeric(lines2[[2]][4]) # number of bins
  
  # read in the third line (bin counts)
  data2 = as.numeric(lines2[[3]])
  # error checking
  if (bsize2!=length(data2)) {
    stop('retrieved size of bins are not equal to the number of bins in the data line')
  }
  
  dataRange2 <- seq(lb2,ub2,by=width2)
  bincenters2 <- (dataRange2[-1] + dataRange2[-length(dataRange2)])/2
  df2 <- data.frame(centers=bincenters2,counts=data2)
 
  if (sID1!=sID2) {
    warning(paste('Species ID mismatch, ID1:',sID1,", ID2:",sID2))
  }
  if (time1!=time2) {
    warning(paste('Time point mismatch, Time1:',time1,", Time2:",time2))
  }
  if (bsize1!=bsize2) {
    stop('two histograms must have the same number of bins')
  }
  
  # Syncronize the histograms if necessary
  llb1 = lb1 + (which(data1>0)[1]-1)*width1
  llb2 = lb2 + (which(data2>0)[1]-1)*width2
  glb = min(llb1,llb2)
  lub1 = lb1 + (which(data1>0)[length(which(data1>0))])*width1
  lub2 = lb2 + (which(data2>0)[length(which(data2>0))])*width2
  gub = max(lub1,lub2)
  gwidth = max(width1,width2)

  if (glb<0 | glb>gub) {
    stop("error in bounds")
  }
  nlb = floor((glb/gwidth)*gwidth)
  nub = nlb+length(data1)*gwidth
  while (gub > nub) {
    gwidth = gwidth*2
    nlb = floor(glb / gwidth) * gwidth
    nub = nlb + length(data1) * gwidth
  }
  gIwidth = 1/gwidth
  
  his1 = rep(0,length(data1))
  his2 = rep(0,length(data2))

  #data1
  for (i in 0:(length(data1)-1)) {
    if (data1[i+1] != 0) {
      event = lb1+i*width1
      if (nlb>event || event>=nub) {
        stop('invalid new upper and/or lower bound')
      }
      his1[1+floor((event-nlb)*gIwidth)] = his1[1+floor((event-nlb)*gIwidth)]+data1[i+1];
    }
  }
  
  #data2
  for (i in 0:(length(data2)-1)) {
    if (data2[i+1] != 0) {
      event2 = lb2+i*width2
      if (nlb>event2 ||event2>=nub) {
        stop('invalid new upper and/or lower bound')
      }
      his2[1+floor((event2-nlb)*gIwidth)] = his2[1+floor((event2-nlb)*gIwidth)]+data2[i+1]
    }
  }
 
  # plot
  dataRange <- seq(nlb,nub,by=gwidth)
  bincenters <- (dataRange[-1] + dataRange[-length(dataRange)])/2
  df1 <- data.frame(centers=bincenters,counts=his1)
  
  p <- ggplot(dat=df1,aes(x=centers,y=counts)) + geom_bar(stat="identity",width=gwidth,colour="red",fill="red",alpha=.65) + ylab("Bin Counts") + xlab("Bin Centers") + ggtitle(paste("Species:",sID1," Time:",time1))

  df2 <- data.frame(centers=bincenters,counts=his2)
  p2 <- p + geom_bar(dat=df2,stat="identity",width=gwidth,colour="dark blue",fill="dark blue",alpha=.65)
  
  maxCount <- max(his1,his2)
  
  # compute histogram distance
  his1= his1/sum(his1);
  his2= his2/sum(his2);
  
  euclidean_distance = sqrt(sum(abs(his1-his2)^2))
  manhattan_distance = sum(abs(his1-his2))
  p3 <- p2 + annotate("text", size=4, x = (dataRange[length(dataRange)]+dataRange[1])/2, y = maxCount*1.1, label = sprintf("Euclidean d=%2.3f, Manhattan d=%2.3f",euclidean_distance,manhattan_distance))
  return(p3)
}