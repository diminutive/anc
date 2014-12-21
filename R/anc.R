## are there groups
allgroups <- function(dsn) {
  inc0 <- inc <- Rnc_open(dsn)
  on.exit(Rnc_close(inc0))
 ## any groups? 
  groupids <- groupnames <- NULL; 
  
  while(TRUE) {

    
    groups <- unlist(lapply(inc, function(x) Rnc_inq_grps(x)))
  if (length(groups) < 1) break; 
    groupids <- c(groupids, groups)
    inc <- groups
  }
  if (length(groupids) < 1) {
    groupids <- inc0
    groupnames <- make.names(basename(dsn))
  } else {
    sapply(groupids, Rnc_inq_grpname)
  }
 gg <- list(groups = groupids, names = groupnames)
 qq <- lapply(gg$groups, Rnc_inq)
 names(qq) <- gg$names
  qq
  
}

