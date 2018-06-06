#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <complex.h>
#include <math.h>
#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>
#include <Rdefines.h>

#include "aff_read.h"

SEXP aff_read_key_interface ( SEXP filename_, SEXP key_, SEXP key_length_  ) {

/* int aff_read_key ( double _Complex * z, char*filename, char*key, int key_length ) */


  PROTECT( filename_   = AS_CHARACTER(filename_) );

  PROTECT( key_        = AS_CHARACTER(key_) );

  PROTECT( key_length_ = AS_INTEGER(key_length_) );

  char * filename = R_alloc ( strlen( CHAR( STRING_ELT(filename_, 0))), sizeof(char) ); 

  char * key      = R_alloc ( strlen( CHAR( STRING_ELT(key_, 0))), sizeof(char) ); 

  const int key_length = INTEGER_POINTER(key_length_)[0];

  strcpy( filename, CHAR(STRING_ELT(filename_, 0))); 

  strcpy( key,      CHAR(STRING_ELT(key_,      0))); 

  SEXP res;
  Rcomplex * resp;
  double _Complex *ires = (double _Complex *)malloc ( key_length * sizeof(double _Complex) );
  if ( ires == NULL ) {
    fprintf ( stderr, "[aff_read_key_interface] Error, ires is NULL\n");
    return(R_NilValue);
  }
  PROTECT(res = NEW_COMPLEX(key_length));
  resp = COMPLEX_POINTER(res);

  // TEST
  //fprintf ( stdout, "# [aff_read_key_interface] filename is %s\n", filename );
  //fprintf ( stdout, "# [aff_read_key_interface] key      is %s\n", key );
  // END OF TEST


  int exitstatus = aff_read_key ( ires, filename, key, key_length );
  if ( exitstatus != 0  ) {
    fprintf ( stderr, "[aff_read_key_interface] Error from aff_read_key, status was %d\n", exitstatus );
    return(R_NilValue);
  }

  for ( int k = 0; k < key_length; k++ ) {
    resp[k].r = creal( ires[k] );
    resp[k].i = cimag( ires[k] );
  }

  free ( ires );

  UNPROTECT(4);
  return(res);

}
