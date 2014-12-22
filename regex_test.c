// Paul H Alfille 2014 -- test of regex

#include <stdio.h> // for getline
#include <regex.h> // for regex
#include <stdlib.h> // for exit
#include <string.h> // for strlen

#define MAXSUB 7
#define MAXERRORMSG 100

static char getcharnow( void )
{
	char garbage[MAXERRORMSG];
	char c = getchar();
	fgets( garbage, MAXERRORMSG, stdin ) ;
	return c ;
}

static char * regexR( char * regex )
{
	if ( regex != NULL ) {
		return regex ;
	}
	return ".*" ;
}

static char * regexS( char * string )
{
	if ( string != NULL ) {
		return string ;
	}
	return "Hello World!" ;
}

static void trim_newline( char * buffer )
{
	if ( buffer != NULL ) {
		int len = strlen( buffer ) ;
		if ( len == 0 ) {
			return ;
		}
		if ( buffer[len-1] == '\n' ) {
			buffer[len-1] = '\0' ;
		}
	}
}

int main( int argc, char argv[] )
{
	char * regex = NULL ;
	size_t regex_len ;
	char * string = NULL;
	size_t string_len ;
	regex_t regc ;
	int extended = 1 ;
	int regr = regcomp( &regc, regexR(regex), extended?REG_EXTENDED:0 ) ;
	do {
		printf("\n----------------------\n");
		if ( regr == 0 ) {
			regmatch_t pmatch[MAXSUB+1] ;
			
			int reger = regexec( &regc, regexS(string), MAXSUB, pmatch, 0 ) ;
			if ( reger != 0 ) {
				printf("No match\n");
			} else {
				int i ;
				printf("%s\n",regexS(string));
				printf("0    X    1    X    2    X    3    X    4    X    5    X    6    X    7    X    8    X    \n");
				for ( i=0 ; i<MAXSUB ; ++i ) {
					int s = pmatch[i].rm_so ;
					int e = pmatch[i].rm_eo ;
					char * b = regexS(string) ;
					if ( s == -1 ) {
						break ;
					}
					printf("%d:\t%d -> %d  <%.*s>\n",i,s,e,e-s,&b[s]);
				} 
			}			
		} else {
			char rege[MAXERRORMSG+1] ;
			regerror( regr, &regc, rege, MAXERRORMSG ) ;
			printf("XXX Error compiling expression XXX %s\n",rege ) ;
		}
		printf("\nChoosse:\n") ;	
		printf( "1. Regex : <%s>\n",regexR(regex) ) ; 
		printf( "2. String: <%s>\n",regexS(string) ) ;
		printf( "3. Mode  :  %s \n",extended?"Extended":"Basic" ) ;
		switch( getcharnow() ) {
			case 0:
				exit(0) ;
			case '1':
				printf("New regular expression: ");
				getline( &regex, &regex_len, stdin ) ;
				trim_newline( regex ) ;
				if ( regr == 0 ) {
					regfree( &regc ) ;
				}
				regr = regcomp( &regc, regexR(regex), extended?REG_EXTENDED:0 ) ;
				break ;
			case '2':
				printf("New string to test: ");
				getline( &string, &string_len, stdin ) ;
				trim_newline( string ) ;
				break ;
			case '3':
				extended = !extended ;
				break ;
			default :
				break ;
		}		
	} while (1) ;
	return 0 ;
}
