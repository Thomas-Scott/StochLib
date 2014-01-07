##Test Script
library("StochLib")
parallelSSADirectSerial("-m dimer_decay.xml -t 10 -r 1000 -f -p 4 --keep-trajectories")
