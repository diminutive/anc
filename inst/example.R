
f1 <- "/rdsi/PRIVATE/home/mdsumner/Git/rancid/data/S20030602003090.L3b_MO_ST92_CHL.nc"
f2 <- "/rdsi/PRIVATE/home/mdsumner/Git/rancid/data/O1997001.L3b_DAY_CHL.nc"

f3 <- "/rdsi/PRIVATE/data/eclipse.ncdc.noaa.gov/pub/OI-daily-v2/NetCDF/1981/AVHRR/avhrr-only-v2.19810901.nc"
anc:::allgroups(f1)
anc:::allgroups(f2)
anc:::allgroups(f3)


nc <- anc:::Rnc_open(f1)
groups <- anc:::Rnc_inq_grps(nc)
anc:::Rnc_inq(nc)
anc:::Rnc_inq(groups[1])
anc:::Rnc_inq(groups[2])
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

