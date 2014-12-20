#include <Rcpp.h>
#include <netcdf.h>

using namespace Rcpp;

void ERR(int status) {
  if (status < NC_NOERR) {
    fprintf(stderr, "%s\n", nc_strerror(status));
    exit(-1);
  }
}
// f1 <- "/rdsi/PRIVATE/home/mdsumner/Git/rancid/data/S20030602003090.L3b_MO_ST92_CHL.nc"
// f2 <- "/rdsi/PRIVATE/home/mdsumner/Git/rancid/data/O1997001.L3b_DAY_CHL.nc"

// [[Rcpp::export]]
int Rnc_open(CharacterVector dsn) {
  int ncid;
  int status; 
  std::string fname0 = Rcpp::as<std::string>(dsn); 
  status = nc_open(fname0.c_str(), NC_NOWRITE, &ncid);
   
  return ncid;   
}

// [[Rcpp::export]]
int Rnc_inq_grps(int ncid) {
  int numgrps; 
  int status; 
  status = nc_inq_grps(ncid, &numgrps, NULL);
  return numgrps; 
}



