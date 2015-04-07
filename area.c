#ifdef STANDARD
/* STANDARD is defined, don't use any mysql functions */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef __WIN__
typedef unsigned __int64 ulonglong;/* Microsofts 64 bit types */
typedef __int64 longlong;
#else
typedef unsigned long long ulonglong;
typedef long long longlong;
#endif /*__WIN__*/
#else
#include <my_global.h>
#include <my_sys.h>
#if defined(MYSQL_SERVER)
#include <m_string.h>/* To get strmov() */
#else
/* when compiled as standalone */
#include <string.h>
#define strmov(a,b) stpcpy(a,b)
#define bzero(a,b) memset(a,0,b)
#define memcpy_fixed(a,b,c) memcpy(a,b,c)
#endif
#endif
#include <mysql.h>
#include <ctype.h>
#ifdef HAVE_DLOPEN
#if !defined(HAVE_GETHOSTBYADDR_R) || !defined(HAVE_SOLARIS_STYLE_GETHOST)
static pthread_mutex_t LOCK_hostname;
#endif

#include <math.h>
my_bool calculate_time_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *calculate_time(UDF_INIT* initid, UDF_ARGS *args, char* result, unsigned long* length, char* is_null, char* error );

my_bool calculate_time_init(UDF_INIT *initid, UDF_ARGS *args, char *message){
	if(!(args->arg_count == 1)) {
		strcpy(message, "Expected one argument (in seconds)!");
		return 1;
	}

	args->arg_type[0] = INT_RESULT;

	return 0;
}

char *calculate_time(UDF_INIT *initid, UDF_ARGS *args, char *result, 
	unsigned long *length, char *is_null, char *error){

	char da_time[255];
	int seconds = *((int*)(args->args[0]));
	int hours = seconds/3600;
	int min = (seconds%3600)/60;
	int sec = (seconds%3600)%60;

	snprintf(da_time, 255, "%d:%d:%d", hours,min,sec);
	*length = strlen(da_time);
	memcpy(result,da_time,strlen(da_time));
	return result;
}

#endif