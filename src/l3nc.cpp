//#include <Rcpp.h>
//#include <netcdf.hh>
//
////#ifndef METAL3B_H /* avoid re-inclusion */
////#include "meta_l3b.h"
////#endif
//
//
//using namespace Rcpp;
//
////' @export
//// [[Rcpp::export]]
//int open_input_ncdf4( int ncid, char *pname,  
//  		size_t *nrows, int *grpid, 
//			int *binindex_id, int *binlist_id,
//      int *bindata_id)
//      //, meta_l3bType *meta_l3b)
//{
//  int status;
//  int dimid;
//
//  status = nc_inq_ncid(	ncid, "Level-3 Binned Data", grpid);
//  status = nc_inq_dimid( *grpid, "binIndexDim", &dimid);
//  status = nc_inq_dimlen( *grpid, dimid, nrows);
//
//  status = nc_inq_varid( *grpid, "BinIndex", binindex_id);
//  status = nc_inq_varid( *grpid, "BinList", binlist_id);
//  status = nc_inq_varid( *grpid, pname, bindata_id);
//  if ( status != NC_NOERR) {
//    // don't know what "endl" is (iostream?)
//    //cout << "Product \"" << pname << "\" not found in input file" << endl;
//    exit(1);
//  }
//
//  //read_attrs(-ncid, meta_l3b);
//
//  return 0;
//}