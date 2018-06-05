## interface function for AFF read

AffReadKeyList <- function ( filename, key_list, key_length=0 ) {

  if ( missing ( filename ) )
    stop ( "need AFF filename" )

  if ( missing ( key_list ) )
    stop ( "need list of keys" )

  if ( missing ( key_length ) )
    stop ( "need length of data key" )

  if ( !is.character(filename) || !is.character(key_list) || !is.integer(key_length) )
    stop("wrong argument types!\n")

  if ( key_length <= 0 )
    stop ( "key length must be positive" )

  key_num <- length( key_list )
  if ( key_num == 0 )
    stop ( "number of keys is zero" )

  return(.Call( "aff_read_key_list_interface", as.character(filename), as.character(key_list), as.integer(key_num), as.integer(key_length) ) )
}
