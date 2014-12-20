#include <Rcpp.h>
#include <netcdf.hh>
using namespace Rcpp;

const char* RstringToChar(CharacterVector str) {
  std::string str1 = Rcpp::as<std::string>(str); 
  return str1.c_str();
}   


//As in the previous example, a single call opens the existing
//netCDF dataset, returning a netCDF ID. This netCDF ID is given to
//the nc_inq routine, which returns the number of dimensions, the
//number of variables, the number of global attributes, and the ID
//of the unlimited dimension, if there is one.
//
//All the inquire functions are inexpensive to use and require no
//I/O, since the information they provide is stored in memory when
//a netCDF dataset is first opened.
//
//Dimension IDs use consecutive integers, beginning at 0. Also
//dimensions, once created, cannot be deleted. Therefore, knowing
//the number of dimension IDs in a netCDF dataset means knowing all
//the dimension IDs: they are the integers 0, 1, 2, ...up to the
//number of dimensions. For each dimension ID, a call to the
//inquire function nc_inq_dim returns the dimension name and
//length.
//
//Variable IDs are also assigned from consecutive integers 0, 1, 2,
//... up to the number of variables. These can be used in
//nc_inq_var calls to find out the names, types, shapes, and the
//number of attributes assigned to each variable.
//
//Once the number of attributes for a variable is known, successive
//calls to nc_inq_attname return the name for each attribute given
//the netCDF ID, variable ID, and attribute number. Armed with the
//attribute name, a call to nc_inq_att returns its type and
//length. Given the type and length, you can allocate enough space
//to hold the attribute values. Then a call to a member of the
//nc_get_att family returns the attribute values.
//
//Once the IDs and shapes of netCDF variables are known, data
//values can be accessed by calling a member of the nc_get_var1
//family for single values, or members of the nc_get_var,
//nc_get_vara, nc_get_vars, or nc_get_varm for various kinds of
//array access.
//
//         nc_open                   /* open existing netCDF dataset */
//           ...
//         nc_inq                    /* find out what is in it */
//              ...
//            nc_inq_dim             /* get dimension names, lengths */
//              ...
//            nc_inq_var             /* get variable names, types, shapes */
//                 ...
//               nc_inq_attname      /* get attribute names */
//                 ...
//               nc_inq_att          /* get attribute types and lengths */
//                 ...
//               nc_get_att          /* get attribute values */
//                 ...
//            nc_get_var             /* get values of variables */
//              ...
//         nc_close                  /* close netCDF dataset */



  
//' Discover what's there. 
//' 
//' Open the file and list what is in it. 
//' @param dsn datasource name, file name or URL
//' @export
// [[Rcpp::export]]
List onc(CharacterVector dsn) {
  int ncid;  
  int status_open;
  int status_close;
  status_open = nc_open(RstringToChar(dsn), NC_NOWRITE, &ncid); 
  
  List open = List::create(Rcpp::Named("ncid") = ncid, 
                           Rcpp::Named("status") = status_open); 
  
  // are there groups?
  int numgrps; 
  int status_grps;
  status_grps = nc_inq_grps(ncid, &numgrps, NULL);

  int grpid; 
  int status_grpopen; 
  status_grpopen = nc_inq_ncid(ncid, "level-3_binned_data", &grpid); 
    // do this later
  List grps = List::create(Rcpp::Named("numgrps") = numgrps, 
                           Rcpp::Named("status") = status_grps); 
  
 
  int status_igroup;
  int ndims, nvars, ngatts, unlimdimid;
  status_igroup = nc_inq(grpid, &ndims, &nvars, &ngatts, &unlimdimid); 
  
//  int status_inq, ndims, nvars, ngatts, unlimdimid;
//  status_inq = nc_inq(ncid, &ndims, &nvars, &ngatts, &unlimdimid);
//  
  List inq = List::create(Rcpp::Named("ndims") = ndims, 
                          Rcpp::Named("nvars") = nvars,
                          Rcpp::Named("ngatts") = ngatts, 
                          Rcpp::Named("unlimdimid") = unlimdimid, 
                          Rcpp::Named("status") = status_igroup); 
      
  grps["inq"] = inq; 
  
//  int status_inq_dim; 
//  List dims = List::create();
//  
//
//  char idimname[NC_MAX_NAME + 1]; 
//  
//  
//  //char *idimname_p = idimname; 
//  size_t idimlength;
//  
//  for (idim = 0; idim < ndims)
//  status_inq_dim = nc_inq_dim(ncid, idim, idimname, &idimlength); 
// 
// //    printf("%s", &idimname[0]);
// 
//  dims[idimdname] = List::create(Rcpp::Named("dimid") = idim, 
//                                Rcpp::Named("idimname") = mkString(idimname),
//                                Rcpp::Named("idimlength") = idimlength, 
//                                Rcpp::Named("status") = status_inq_dim
//                                );
//  

  status_close = nc_close(ncid); 

  List close = List::create(Rcpp::Named("status") = status_close); 
  
  List out = List::create(Rcpp::Named("open") = open, 
                          Rcpp::Named("grps") = grps,
                          Rcpp::Named("close") = close);
  return out;
}
         
      

//' Open.  
//'
//' Open the file. 
//' @param dsn data source name, file name or URL
//' @export
//' @examples 
//' f1 <- "/rdsi/PRIVATE/home/mdsumner/Git/rancid/data/S20030602003090.L3b_MO_ST92_CHL.nc"
//' f2 <- "/rdsi/PRIVATE/home/mdsumner/Git/rancid/data/O1997001.L3b_DAY_CHL.nc"
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