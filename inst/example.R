dd <- getOption("default.datadir")

f <- c("../rancid/data/S20030602003090.L3b_MO_ST92_CHL.nc", 
       "../rancid/data/O1997001.L3b_DAY_CHL.nc", 
       "/rdsi/PRIVATE/data/eclipse.ncdc.noaa.gov/pub/OI-daily-v2/NetCDF/1981/AVHRR/avhrr-only-v2.19810901.nc", 
               "/rdsi/PRIVATE/bathymetry/etopo1/ETOPO1_Ice_g_gdal.grd", 
               "/rdsi/PRIVATE/bathymetry/etopo2/ETOPO2v2c_f4.nc")


ag <- anc:::allgroups(f[1])
nc <- anc:::Rnc_open(f[1])
grpid <- anc:::Rnc_inq_grps(nc)[1]

x <- anc:::Rnc_get_vara(grpid)
head(x[[1]])
## NumericVector Rnc_get_var_double(int ncid, int varid, int nvals) {
##binlistsize <- 
vname <- "chlor_a"
ivar <- which(ag[[1]]$vars$varnames == vname) - 1

anc:::Rnc_get_var1_float(grpid)


//nc_inq_ncid(  ncid, "Level-3 Binned Data", grpid);
//status = nc_get_var1( grpid, binindex_id, &indexp, binindex_buf);


system("grep BinList S20030602003090.L3b_MO_ST92_CHLALL.txt", intern = TRUE)
[1] "  \tbinListType BinList(binListDim) ;"                         
[2] "   BinList = {84522, 1, 1, 1, 0}, {84523, 2, 1, 1.414214, 0}, "
> system("grep chlor_a S20030602003090.L3b_MO_ST92_CHLALL.txt", intern = TRUE)
[1] "\t\t:units = \"chlor_a:mg m^-3\" ;"                                            
[2] "  \tbinDataType chlor_a(binDataDim) ;"                                         
[3] "   chlor_a = {1.057405, 1.118105}, {2.814226, 5.638368}, {3.419775, 6.78676}, "

system("grep BinIndex S20030602003090.L3b_MO_ST92_CHLALL.txt", intern = TRUE)
[1] "  \tbinIndexType BinIndex(binIndexDim) ;"                                  
[2] "   BinIndex = {1, 0, 0, 3}, {4, 0, 0, 9}, {13, 0, 0, 16}, {29, 0, 0, 2


ag <- anc:::allgroups(f[1])

for (i in seq_along(f)) print(anc:::allgroups(f[i]))



list.files()
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

