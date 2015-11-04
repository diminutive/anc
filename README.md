# anc
tiny minimal dumb Rcpp NetCDF package

The NetCDF4 format from NASA consists of a file with two groups

"level-3_binned_data" and "processing_control

(Groups act like a file to the classic NetCDF library, and so a file/group is like a single classic file.)

The "level-3_binned_data" has multiple variables which of "compound type". This just means that they can contain data of different types, like a basic table. 

BinList - this is a "row" for every populated bin
         nobs  nscenes , time_rec (int16)
         bin_num, flags_set (int32)
         sel_cat (int8)
         weights (float32)

Variables  - these are "paired" sum and sum_sq values (float32, I think)
e.g. the "RRS" files contain Angstrom, Aot_869, Rrs_412, etc. (depends on the platform/sensor)
    the "CHL" files contain chlor_a (and so on)
    

BinIndex - a "row" for the bin scheme (this is too basic to bother reading from the file)


We need a way to 

- determine what variables we expect (probably just let R do all this based on file name)
- develop readers for each of the different types (int16, int32, float32) - again R can drive which read type by expected variable name



Check that floating point is always 32-bit? 
