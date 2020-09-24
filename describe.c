/* Processed by ecpg (12.3) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "describe.pgc"
#include "describe.h"
#include <stdio.h>
#include <stdlib.h>


#line 1 "C:/PostgreSQL/12/include/sqlda.h"
#ifndef ECPG_SQLDA_H
#define ECPG_SQLDA_H

#ifdef _ECPG_INFORMIX_H

#include "sqlda-compat.h"
typedef struct sqlvar_compat sqlvar_t;
typedef struct sqlda_compat sqlda_t;

#else

#include "sqlda-native.h"
typedef struct sqlvar_struct sqlvar_t;
typedef struct sqlda_struct sqlda_t;

#endif

#endif							/* ECPG_SQLDA_H */

#line 5 "describe.pgc"

sqlda_t *sqlda;

/* exec sql whenever sqlerror  call error ( ) ; */
#line 8 "describe.pgc"


void error()
{
    fprintf(stdout, "sqlcode: %ld\n", sqlca.sqlcode);
    fprintf(stdout, "sqlstate: %5s\n", sqlca.sqlstate);
    fprintf(stdout, "sqlerrm: %s\n", sqlca.sqlerrm.sqlerrmc);

    exit(1);
}

// ecpgtype.h
// name of `enum ECPGttype`
const char* nameOf(int type)
{
    static const char* types[] = {
        "",
        "text",             // ECPGt_char
        "",                 // ECPGt_unsigned_char
        "smallint",         // ECPGt_short
        "",                 // ECPGt_unsigned_short
        "int",              // ECPGt_int
        "",                 // ECPGt_unsigned_int
        "int4",             // ECPGt_long
        "",                 // ECPGt_unsigned_long
        "bigint",           // ECPGt_long_long
        "",                 // ECPGt_unsigned_long_long
        "boolean",          // ECPGt_bool
        "double precision", // ECPGt_float
        "double precision", // ECPGt_double
        "text",             // ECPGt_varchar
        "text",             // ECPGt_varchar2
        "numeric",          // ECPGt_numeric
        "decimal",          // ECPGt_decimal
        "date",             // ECPGt_date
        "timestamp",        // ECPGt_timestamp
        "interval",         // ECPGt_interval
        "",                 // ECPGt_array
        "",                 // ECPGt_struct
        "",                 // ECPGt_union
        "",                 // ECPGt_descriptor
        "",                 // ECPGt_char_variable
        "",                 // ECPGt_const
        "",                 // ECPGt_EOIT
        "",                 // ECPGt_EORT
        "",                 // ECPGt_NO_INDICATOR
        "text",             // ECPGt_string
        "",                 // ECPGt_sqlda
        "",                 // ECPGt_bytea
    };

    return types[type];
}

int describe(const Config* config)
{
    /* exec sql begin declare section */
        
         
         
        
    
#line 65 "describe.pgc"
 char conn [ 1024 ] = "" ;
 
#line 66 "describe.pgc"
 const char * user = config -> user ;
 
#line 67 "describe.pgc"
 const char * pass = config -> pass ;
 
#line 68 "describe.pgc"
 const char * query = config -> query ;
/* exec sql end declare section */
#line 69 "describe.pgc"


    sprintf_s(conn, sizeof(conn), "tcp:postgresql://%s:%s/%s", config->host, config->port, config->db);

    { ECPGconnect(__LINE__, 0, conn , user , pass , NULL, 0); 
#line 73 "describe.pgc"

if (sqlca.sqlcode < 0) error ( );}
#line 73 "describe.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "set CLIENT_ENCODING to 'UTF-8'", ECPGt_EOIT, ECPGt_EORT);
#line 75 "describe.pgc"

if (sqlca.sqlcode < 0) error ( );}
#line 75 "describe.pgc"


    { ECPGprepare(__LINE__, NULL, 0, "stmt", query);
#line 77 "describe.pgc"

if (sqlca.sqlcode < 0) error ( );}
#line 77 "describe.pgc"

    { ECPGdescribe(__LINE__, 0, 0, NULL, "stmt",
	ECPGt_sqlda, &sqlda, 0L, 0L, 0L, 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 78 "describe.pgc"


    printf("[");

    for (int i = 0; i < sqlda->sqld; i++)
    {
        sqlvar_t v = sqlda->sqlvar[i];
        printf("{\"type\": \"%s\", \"size\": %d, \"name\": \"%s\"}%s", nameOf(v.sqltype), v.sqllen, v.sqlname.data, ((i + 1) < sqlda->sqld ? "," : ""));
    }

    printf("]");

    { ECPGdisconnect(__LINE__, "CURRENT");
#line 90 "describe.pgc"

if (sqlca.sqlcode < 0) error ( );}
#line 90 "describe.pgc"


    return 0;
}
