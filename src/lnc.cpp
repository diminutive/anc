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
// anc:::Rnc_inq_grps(anc:::Rnc_open(f1))
// [[Rcpp::export]]
int Rnc_open(CharacterVector dsn) {
  int ncid;
  int status; 
  std::string fname0 = Rcpp::as<std::string>(dsn); 
  status = nc_open(fname0.c_str(), NC_NOWRITE, &ncid);  
  return ncid;   
}
// [[Rcpp::export]]
IntegerVector Rnc_inq_grps(int ncid) {
  int numgrps; 
  int status; 
  //int *ncids; 
  
  status = nc_inq_grps(ncid, &numgrps, NULL);
  int *ncids = new int[numgrps];
  status = nc_inq_grps(ncid, NULL, ncids); 
  IntegerVector grpids(numgrps); 
  for (int i = 0; i < numgrps; i++) grpids[i] = ncids[i]; 
  return grpids; 
}
// [[Rcpp::export]]
CharacterVector Rnc_inq_grpname(int grpid) {
  char name_in[1];
  int status; 
  status = nc_inq_grpname(grpid, name_in); 
  CharacterVector cnames = name_in; 
  return cnames; 
}

// [[Rcpp::export]]
void Rnc_close(int ncid) {
  int status = nc_close(ncid); 
}



