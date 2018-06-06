## interface function for AFF read

AffReadKey <- function ( filename, key, key_length=0 ) {

  if ( missing ( filename ) )
    stop ( "need AFF filename" )

  if ( missing ( key ) )
    stop ( "need key" )

  if ( missing ( key_length ) )
    stop ( "need length of data key" )

  if ( !is.character(filename) || !is.character(key) )
    stop("wrong argument types!\n")

  if ( key_length <= 0 )
    stop ( "key length must be positive" )

  return(.Call( "aff_read_key_interface", as.character(filename), as.character(key), as.integer(key_length) ) )
}
