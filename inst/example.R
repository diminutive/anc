nc <- anc:::Rnc_open(f1)
groups <- anc:::Rnc_inq_grps(nc)

for (i in seq_along(groups)) {
  print(anc:::Rnc_inq_grpname(groups[i]))
  ##[1] "level-3_binned_data"
  ##[1] "processing_control"
}

groups2 <- anc:::Rnc_inq_grps(groups[2])
for (i in seq_along(groups2)) {
  print(anc:::Rnc_inq_grpname(groups2[i]))
  ##[1] "input_parameters"
}

anc:::Rnc_close(nc)

