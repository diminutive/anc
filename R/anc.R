allgroups <- function(dsn) {
  inc <- Rnc_open(dsn)
  ## any groups? 
  groupids <- groupnames <- NULL; 
  
  while(TRUE) {
    groups <- unlist(sapply(inc, Rnc_inq_grps))
    if (length(groups) < 1) break; 
    groupids <- c(groupids, groups)
    inc <- groups
  }
  if (length(groups) < 1) return(NULL)
  list(groups = groupids, names = sapply(groupids, Rnc_inq_grpname))
}