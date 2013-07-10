#!/usr/local/bin/python

#	-m  model name
#	-t  simulation time
#	-r  number of realizations
#	-i  number of intervals
#	-f  --force tells driver to overwrite existing output dir
#	
#	outdir "--out-dir" give output directory name
#	stats "--no-stats"
#	traj "--keep-trajectories"
#	hist "--keep-histograms"

import PyStochLib

def ssaDirectSerial(model_name="",parallel=False):
	if(model_name!=""):
		if(parallel==False):
			print "Running ssa_direct_serial..."
			PyStochLib.ssaDirectSerial(model_name)
			print "Done"
		elif(parallel==True):
			print "Running ssa_direct_serial in parallel..."
			PyStochLib.parallelSSADirectSerial(model_name)
			print "Done"
	else:
		print "Not a model..."

def count():
	PyStochLib.count()