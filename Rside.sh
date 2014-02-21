R CMD INSTALL StochLib
##R -f "StochLib Test.R"
R -f "parallelTest.R"
echo "NOTES:"
echo "~/ contains output folder. Will update later."
echo "If build failed try changing ~/.R/Makevars to include the following: CXX = g++-4.2"
