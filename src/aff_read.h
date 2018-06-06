#ifndef _AFF_READ_H
#define _AFF_READ_H

int aff_read_key ( double _Complex * z, char*filename, char*key, const int key_length );

int aff_read_key_list ( double _Complex * z, char*filename, char**key_list, const int key_num, const int key_length );

#endif
