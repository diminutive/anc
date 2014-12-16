
#include <Rcpp.h>
//ffing kidding me
#include <netcdf.hh>
using namespace Rcpp;

// [[Rcpp::export]]
List rcpp_hello_world() {

    CharacterVector x = CharacterVector::create( "foo", "bar" )  ;
    NumericVector y   = NumericVector::create( 0.0, 1.0 ) ;
    List z            = List::create( x, y ) ;

    return z ;
}


// [[Rcpp::export]]
List boogietastic(CharacterVector filename) {
  std::string fname = Rcpp::as<std::string>(filename);
     int  status;                           /* error status */
     int ncid;                              /* netCDF ID */
//     int rh_id;                             /* variable ID */
//     static size_t rh_index[] = {1, 2, 3};  /* where to get value from */
//     double rh_val;                         /* where to put it */
//        ...
     status = nc_open(fname.c_str(), NC_NOWRITE, &ncid);
     
     List z = List::create(status);
     return z;
}
//     if (status != NC_NOERR) handle_error(status);
//        ...
//     status = nc_inq_varid (ncid, "rh", &rh_id);
//     if (status != NC_NOERR) handle_error(status);
//        ...
//     status = nc_get_var1_double(ncid, rh_id, rh_index, &rh_val);
//     if (status != NC_NOERR) handle_error(status);