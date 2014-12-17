
#include <Rcpp.h>
#include <netcdf.hh>
using namespace Rcpp;


//' Open.  
//'
//' Open the file. 
//' @param dsn data source name, file name or URL
//' @export
//' @examples 
//' f1 <- "/rdsi/PRIVATE/home/mdsumner/Git/rancid/data/O1997001.L3b_DAY_CHL.nc"
//' open_input_ncdf4(f1)
// [[Rcpp::export]]
List open_input_ncdf4(CharacterVector dsn) {
  
  std::string fname = Rcpp::as<std::string>(dsn);
  int  
  status_open, 
  status_grpid, 
  status_dimid, 
  status_nrows, 
  status_binindex_id, 
  status_binlist_id, 
  status_bindata_id;                           /* error status */
  
  int dimid;
  int grpid; 
  size_t nrows;
  int binindex_id;
  int binlist_id; 
  int bindata_id; 
  
  int ncid;                              /* netCDF ID */
  status_open = nc_open(fname.c_str(), NC_NOWRITE, &ncid); 
  // in smigen.cpp "level-3 binned data" is title case
  status_grpid = nc_inq_ncid(  ncid, "level-3_binned_data", &grpid);
  status_dimid = nc_inq_dimid( grpid, "binIndexDim", &dimid);
  status_nrows = nc_inq_dimlen( grpid, dimid, &nrows);
  status_binindex_id = nc_inq_varid( grpid, "BinIndex", &binindex_id);
  status_binlist_id = nc_inq_varid( grpid, "BinList", &binlist_id);
  // where is the chlor_a_sum and ssq? 
  status_bindata_id = nc_inq_varid(grpid, "chlor_a", &bindata_id);
  //  if ( status != NC_NOERR) {
  //    // don't know what "endl" is (iostream?)
  //    //cout << "Product \"" << pname << "\" not found in input file" << endl;
  //    exit(1);
  //  }
  
  //read_attrs(-ncid, meta_l3b);
  
  List out = List::create();
  out["status_open"] = status_open;
  out["status_grpid"] =  status_grpid;
  out["status_dimid"] =  status_dimid;
  out["status_nrows"] =  status_nrows;
  out["status_binindex_id"] =  status_binindex_id;
  out["status_binlist_id"] =  status_binlist_id;
  out["status_bindata_id"] =  status_bindata_id;
  
  out["ncid"] = ncid;
  out["grpid"] = grpid;
  out["dimid"] = dimid;
  out["nrows"] = nrows;
  out["binindex_id"] = binindex_id;
  out["binlist_id"] = binlist_id;
  out["bindata_id"] = bindata_id;
 
  return out;
}

//' Open.  
//'
//' Open the file. 
//' @param dsn data source name, file name or URL
//' @examples
//' nc_open(raadtools::sstfiles()$fullname[1])
//' ## problem file: "http://www.auscover.org.au/thredds/dodsC/auscover/lpdaac-csiro/lpdaac-mosaics/c5/v1-hdf4/aust/MOD13Q1.005/2014.11.17/MOD13Q1.2014.321.aust.005.b01.250m_ndvi.hdf.gz"
//' f <- "http://www.auscover.org.au/thredds/dodsC/auscover/lpdaac-csiro/lpdaac-mosaics/c5/v1-hdf4/aust/MOD13Q1.005/2014.11.17/MOD13Q1.2014.321.aust.005.b01.250m_ndvi.hdf.gz"
//' nc_open(f)
//' @export
// [[Rcpp::export]]
List nc_open(CharacterVector dsn) {
  std::string fname = Rcpp::as<std::string>(dsn);
  int  status;                           /* error status */
  int ncid;                              /* netCDF ID */
  status = nc_open(fname.c_str(), NC_NOWRITE, &ncid); 
  
  List out = List::create();
  out["status"] = status;
  out["ncid"] = ncid;
  return out;
}

//' Inquire about a variable in a data set. 
//' 
//' Variable in a dataset. 
//' @param dsn filename or URL
//' @param varname variable name
//' @export
//  [[Rcpp::export]]
List nc_inq_var(CharacterVector dsn, CharacterVector varname) {
  std::string fname = Rcpp::as<std::string>(dsn);
  std::string vname = Rcpp::as<std::string>(varname);
  int  var_id;                        /* variable ID */
  nc_type type;                   /* variable type */
  int status;
  int ncid; 
  int ndims;                      /* number of dims */
  int dimids[NC_MAX_VAR_DIMS];   /* dimension IDs */
  int natts;                       /* number of attributes */
  
  status = nc_open(fname.c_str(), NC_NOWRITE, &ncid);
  
  status = nc_inq_varid(ncid, vname.c_str(), &var_id);
  //if (status != NC_NOERR) handle_error(status);
  status = nc_inq_var(ncid, var_id, 0, &type, &ndims, dimids, &natts);
  nc_close(ncid); 
  
  
  List out = List::create();
  out["status"] = status;
  out["ncid"] = ncid;
  out["var_id"] = var_id;
  out["type"] = type;
  out["ndims"] = ndims;
  //  out["dimids"] = Rdimids;
  out["natts"] = natts;
  
  return out;
  
  
}


//' Inquire about a dataset. 
//' 
//' About a dataset. 
//' @param dsn filename or URL
//' @export
// [[Rcpp::export]]
List nc_inq(CharacterVector dsn) {
  std::string fname = Rcpp::as<std::string>(dsn);
  int status, ncid, ndims, nvars, ngatts, unlimdimid;
  status = nc_open(fname.c_str(), NC_NOWRITE, &ncid);
  //if (status != NC_NOERR) handle_error(status);
  status = nc_inq(ncid, &ndims, &nvars, &ngatts, &unlimdimid);
  nc_close(ncid); 
  //if (status != NC_NOERR) handle_error(status);
  List out = List::create();
  out["status"] = status;
  out["ncid"] = ncid;
  out["ndims"] = ndims;
  out["nvars"] = nvars;
  out["ngatts"] = ngatts;
  out["unlimdimid"] = unlimdimid;
  
  return out;
}



//' Test.  
//'
//' test. 
//' @param filename data source name, file name or URL
//' @export
//' @examples
//' nctest(raadtools::sstfiles()$fullname[1])
// [[Rcpp::export]]
List nctest(CharacterVector filename) {
  std::string fname = Rcpp::as<std::string>(filename);
  int  status;                           /* error status */
  int ncid;                              /* netCDF ID */
  //     int rh_id;                             /* variable ID */
  //     static size_t rh_index[] = {1, 2, 3};  /* where to get value from */
  //     double rh_val;                         /* where to put it */
  status = nc_open(fname.c_str(), NC_NOWRITE, &ncid);
  
  List z = List::create();
  z["status"] = status;
  z["ncid"] = ncid;
  return z;
}



//     if (status != NC_NOERR) handle_error(status);
//        ...
//     status = nc_inq_varid (ncid, "rh", &rh_id);
//     if (status != NC_NOERR) handle_error(status);
//        ...
//     status = nc_get_var1_double(ncid, rh_id, rh_index, &rh_val);
//     if (status != NC_NOERR) handle_error(status);