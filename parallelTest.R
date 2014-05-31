##Test Script
library("StochLib")
##parallelSSADirectSerial("-m examples/dimer_decay.xml -t 10 -r 10000 -f -p 2 -i 10 --keep-trajectories")
ssaLdmSerial("-m examples/dimer_decay.xml -t 10 -r 10000 -f -p 2 -i 10 --keep-trajectories")
