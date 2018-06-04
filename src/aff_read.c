#ifdef HAVE_LHPC_AFF
#include "lhpc-aff.h"
#endif
#include "aff_read.h"
/*****************************************************************************************************************
 * aff_read.c
 *
 * Mo 4. Jun 17:20:53 CEST 2018
 *
 * PURPOSE
 *   open an AFF file
 *   read a list of keys
 *   close the aff file
 *
 * input
 *   filename, name of aff file
 *   key_list, list of char fields with key names
 *   key_num, number of keys to be read
 *   key_lenght, number of complex elements in key
 *****************************************************************************************************************/

int aff_read_key_list ( double _Complex * z, char*filename, char**key_list, int key_num, int key_length ) {
#ifdef HAVE_LHPC_AFF
  int exitstatus;
  struct AffReader_s *affr = NULL;
  struct AffNode_s *affn = NULL, *affdir = NULL;

  // open aff file
  affr = aff_reader (filename);
  if ( const char * aff_status_str = aff_reader_errstr(affr) ) {
    fprintf(stderr, "[aff_read_key_list] Error from aff_reader, status was %s %s %d\n", aff_status_str, __FILE__, __LINE__ );
    return(1);
  } else {
    fprintf(stdout, "# [aff_read_key_list] reading data from aff file %s\n", filename);
  }

  // get root node
  if( (affn = aff_reader_root( affr )) == NULL ) {
    fprintf(stderr, "[aff_read_key_list] Error, aff writer is not initialized %s %d\n", __FILE__, __LINE__);
    return(2);
  }

  // loop on keys in key_list
  uint32_t uitems = key_length;

  for ( int i = 0; i < key_num; i++ ) { 
    affdir = aff_reader_chpath (affr, affn, key_list[i] );
    size_t const offset = i * (size_t)key_length;
    double _Complex zptr = z + offset;
    exitstatus = aff_node_get_complex (affr, affdir, zptr, uitems );
    if( exitstatus != 0 ) {
      fprintf(stderr, "[aff_read_key_list] Error from aff_node_get_complex, status was %d %s %d\n", exitstatus, __FILE__, __LINE__);
      return(3);
    }

  // close aff file
  aff_reader_close (affr);

  return(0);
#else
  return( 100 );
#endif
}  // end of aff_read_key_list
