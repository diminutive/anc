## are there groups
allgroups <- function(dsn) {
  inc <- Rnc_open(dsn)
  ## any groups? 
  groupids <- groupnames <- NULL; 
  
  while(TRUE) {
    groups <- unlist(lapply(inc, function(x) Rnc_inq_grps(x)))
    if (length(groups) < 1) break; 
    groupids <- c(groupids, groups)
    inc <- groups
  }

  if (length(groupids) < 1) return(NULL)
  list(groups = groupids, names = sapply(groupids, Rnc_inq_grpname))
}

## if no groups, main is only "group"
## allvars <- function(dsn) {}

