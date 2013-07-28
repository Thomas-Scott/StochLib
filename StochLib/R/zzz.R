
## Up until R 2.15.0, the require("methods") is needed but (now)
## triggers an warning from R CMD check
#.onLoad <- function(libname, pkgname){
#    #require("methods")  ## needed with R <= 2.15.0
#    loadRcppModules()
#}


## For R 2.15.1 and later this also works. Note that calling loadModule() triggers
## a load action, so this does not have to be placed in .onLoad() or evalqOnLoad().


# # Borrowed code from the Cairo zzz.R script
# .First.lib <- function(libname, pkgname) {
#     ## add our libs to the PATH
#     if (.Platform$OS.type=="windows") {
#         .setenv <- if (exists("Sys.setenv")) Sys.setenv else Sys.putenv
#         lp<-gsub("/","\\\\",paste(libname,pkgname,"libs",sep="/"))
#         cp<-strsplit(Sys.getenv("PATH"),";")
#         if (! lp %in% cp) .setenv(PATH=paste(lp,Sys.getenv("PATH"),sep=";"))
#     }
#     library.dynam("StochLib", pkgname, libname)
#     loadModule("StochLib",TRUE)
# 	packageStartupMessage("Welcome to StochLib",
#                           utils::packageDescription("StochLib", field="Version"),
#                           appendLF = TRUE)
# }

# .onLoad <- .First.lib

loadModule("StochLib",TRUE)