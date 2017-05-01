#include <Rcpp.h>
#include <netcdf.hh>

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
List Rnc_get_vara(int ncid) {
  
    List out = List::create(); 

  int status; 
  int nvals =  3473362;
  
  // float dp[nvals]; 
  int varid = 1; 
  float *sum_buf=NULL;
 // unsigned char *bin_buf=NULL;
  // nvals, start and count refer to the index of the compound type
  // in this case each element consists of two floats (sum and sumsq)
  sum_buf = (float *) calloc(nvals * 2, 2*sizeof(float));
 // bin_buf = (unsigned char *) calloc(nvals * 16, 8*16); 
  printf("%i\n", nvals); 
  static size_t start[] = {0}; /* start at first value */
  static size_t count[] = {nvals};
  status = nc_get_vara(ncid, varid, start, count,  sum_buf);
 
  NumericVector Rvals(nvals * 2); 
  for (int i = 0; i < (nvals * 2); i++) Rvals[i] = sum_buf[i]; 

  out["chlor_a"] = Rvals; 
  //out["binlist"] = bin_buf; 
  
  return out; 
  
}
// once we have a given ID (group-less file, or specific group)
// find its ndims
// [[Rcpp::export]]
List Rnc_inq(int grpid) {
  int status; 
  int ndims, nvars, ngatts, unlimdimid;
  status = nc_inq(grpid, &ndims, &nvars, &ngatts, &unlimdimid); 
  
  if (ndims < 1) return List::create();
  size_t ilen; 
  char recname[NC_MAX_NAME+1];
  
  // int nc_inq_dim     (int ncid, int dimid, char* name, size_t* lengthp);
  IntegerVector dimlens(ndims);
  CharacterVector dnames(ndims); 
  //printf("%i\n", ndims); 
  for (int idim = 0; idim < ndims; idim++) {
    status = nc_inq_dim(grpid, idim, recname, &ilen); 
    dimlens[idim] = ilen; 
    dnames[idim] = recname; 
  }
  
  
  //   int nc_inq_var(int ncid, int varid, char *name, nc_type *xtypep, int *ndimsp, int dimids[], int *nattsp);
  // var dims somehow IntegerVector lens(nvars);
  CharacterVector vnames(nvars); 
  
  //?? vtypes? CharacterVector vtypes(nvars); 
  int  var_dimids[NC_MAX_VAR_DIMS];
  
  int var_natts; 
  int var_ndim; 
  nc_type var_type; 
  for (int ivar = 0; ivar < nvars; ivar++) {
    status = nc_inq_var(grpid, ivar, recname, &var_type, &var_ndim, var_dimids, &var_natts); 
    vnames[ivar] = recname; 
    
   // printf("%s %i\n", recname, var_type); 
  }
  
  
  
  IntegerVector R_dimids(var_ndim); 
  for (int ii = 0; ii < var_ndim; ii++) R_dimids[ii] = var_dimids[ii]; 
  List out = List::create(); 
  out["dims"] = List::create(Named("length") = dimlens, Named("name") = dnames);
  out["vars"] = List::create(Named("varnames") = vnames, 
  Named("natts") = var_natts, 
  Named("dimIDs") = R_dimids); 
  out["ngatts"] = ngatts; 
  out["unlimdimid"] = unlimdimid;
  return out; 
  
}

// [[Rcpp::export]]
void Rnc_close(int ncid) {
  int status = nc_close(ncid); 
}



