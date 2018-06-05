#include <stdlib.h>
#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>
#include <Rdefines.h>

#include "aff_read.h"

SEXP aff_read_key_list_interface ( SEXP filename_, SEXP key_list_, SEXP key_num_, SEXP key_length_  ) {
/* int aff_read_key_list ( double _Complex * z, char*filename, char**key_list, int key_num, int key_length ) */

  

  PROTECT( filename_   = AS_CHARACTER(filename_   ) );
  PROTECT( key_list_   = AS_CHARACTER(key_list_ ) );
  PROTECT( key_num_    = AS_INTEGER(key_num_    ) );
  PROTECT( key_length_ = AS_INTEGER(key_length_ ) );

  char      *filename  = CHARACTER_POINTER(filename_);
  char      **key_list = CHARACTER_POINTER(key_list_);
  const int key_num    = INTEGER_POINTER(key_num_)[0];
  const int key_length = INTEGER_POINTER(key_length_)[0];

  SEXP res;
  Rcomplex * resp;
  double _Complex *ires = (double _Complex *)malloc ( key_num * key_length * sizeof(double _Complex) );
  if ( ires == NULL ) {
    fprintf ( stderr, "[aff_read_key_list_interface] Error, ires is NULL\n");
    return(NULL);
  }
  PROTECT(res = NEW_COMPLEX(key_num * key_length));
  resp = COMPLEX_POINTER(res);

  int exitstatus = aff_read_key_list ( ires, filename, key_list, key_num, key_length );
  if ( exitstatus != 0  ) {
    fprintf ( stderr, "[aff_read_key_list_interface] Error from aff_read_key_list, status was %d\n", exitstatus );
    return(NULL);
  }

  unsigned int ik = 0;
  for ( int i = 0; i < key_num; i++ ) {
    for ( int k = 0; k < key_length; k++ ) {
      resp[ik].r = creal( ires[ik] );
      resp[ik].i = cimag( ires[ik] );
    }
  }

  free ( ires );

  UNPROTECT(10);
  return(res);

}
