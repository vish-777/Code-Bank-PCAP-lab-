#include<stdio.h>
#include "mpi.h"

void ErrorHandler(int error_code){
	if(error_code!=MPI_SUCCESS){
		char error_string[100];
		int len_err_str,error_class;
		MPI_Error_class(error_code,&error_class);
		MPI_Error_string(error_class,error_string,&len_err_str);
		fprintf(stderr,"\n\n%s %d",error_string,len_err_str);
		MPI_Error_string(error_code,error_string,&len_err_str);
		fprintf(stderr,"\nHELLO_ERRORCODE %s",error_string);
	}
}

int main(int argc,char *argv[]){
	int rank,size,error_code;

	error_code=MPI_Init(&argc,&argv);
	MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);

	error_code=MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Errhandler_set(MPI_COMM_WORLD,MPI_ERRORS_RETURN);

	error_code=MPI_Comm_size(MPI_COMM_WORLD,&size);
	ErrorHandler(error_code);

	MPI_Finalize();
	return 0;

}

