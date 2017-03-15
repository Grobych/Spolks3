#include<stdio.h>
#include<mpi.h>
#include <iostream>
#include <fstream>

using namespace std;

char * matrixAfileName;
char * matrixBfileName;
char * resultfileName;


int rank; //process rank
int size; //number of processes
int i, j, k; //helper variables
double start_time; //hold start time
double end_time; // hold end time
MPI_Status status; // store status of a MPI_Recv
MPI_Request request; //capture request of a MPI_Isend


bool blocking;
int numberOfGroups;

const  int N = 1000;
double** createMatrix(int x, int y){
    double** matrix;
    matrix = new double*[x];
    for (int i = 0 ; i < x ; i++){
        matrix[i] = new double[y];
    }
    return  matrix;
}

double** loadFromFile(char * fileName){
    std::ifstream ifs(fileName);

    int n,m;

    ifs >> m >> n;
    std::cout<< n <<" " <<m<<std::endl;
    double ** A = createMatrix(n,m);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            ifs >> A[i][j];
    return A;
}

//void loadToFile(double ** matrix){
//    std::ofstream f("result.txt");
//    f << N << " " << N << std::endl;
//    for (int i = 0; i < N; i++)
//    {
//        for (int j = 0; j < N; j++)
//        {
//            f << matrix[i][j]<<" ";
//        }
//        f << std::endl;
//    }
//}

void showMatrix(double ** matrix){
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout<< matrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}


bool parseParams(int argc, char * argv[]){
    if (argc!=4) {
        cout << "Invalid number of params" << endl;
        return false;
    }
    else {
        matrixAfileName = argv[1];
        matrixBfileName = argv[2];
        cout << "Matrix 1: " <<matrixAfileName << endl;
        cout << "Matrix 2: " <<matrixBfileName << endl;
        return true;
    }

}

int main(int argc, char *argv[])
{
    if (!parseParams(argc, argv)) return 1;
    int errCode;

    if ((errCode = MPI_Init(&argc, &argv)) != 0)
    {
        MPI_Abort(MPI_COMM_WORLD,errCode);
        return errCode;
    }

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    cout << "Hello from " << rank << " of "<< size<< endl;

    MPI_Finalize();
}


