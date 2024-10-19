//  ================================================================================
//  ||                                                                            ||
//  ||              esPIC                                                         ||
//  ||              ------------------------------------------------------        ||
//  ||              E L E C T R O S T I C   P A R T I C L E - I N - C E L L       ||
//  ||                                                                            ||
//  ||              D E M O N S T R A T I O N   C O D E                           ||
//  ||              ------------------------------------------------------        ||
//  ||                                                                            ||
//  ||       Developed by: Scott R. Runnels, Ph.D.                                ||
//  ||                     University of Colorado Boulder                         ||
//  ||                                                                            ||
//  ||                For: CU Boulder CSCI 4576/5576 and associated labs          ||
//  ||                                                                            ||
//  ||           Copyright 2020 Scott Runnels                                     ||
//  ||                                                                            ||
//  ||                     Not for distribution or use outside of the             ||
//  ||                     this course.                                           ||
//  ||                                                                            ||
//  ================================================================================

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include "stdio.h"
#include "math.h"
#include "string.h"
#define quote(x) #x

using std :: string;
using std :: vector;
using std :: stringstream;
using std :: cout;
using std :: endl;

#define rLOOP  for ( int r = 1 ; r <= nField    ; ++r )
#define cLOOP  for ( int c = 1 ; c <= bandwidth ; ++c )
#define iLOOP  for ( int i = 1 ; i <= nRealx    ; ++i )
#define jLOOP  for ( int j = 1 ; j <= nRealy    ; ++j )
#define sLOOP  for ( int s = 0 ; s <= nRealx+1  ; ++s )
#define tLOOP  for ( int t = 0 ; t <= nRealy+1  ; ++t )




//typedef  vector<double>          VD;
//typedef  vector<vector<double> > VDD;
//typedef  vector<int>             VI;
//typedef  vector<vector<int> >    VII;
class VD{
public:
    int VDsize =0 ;
    double* data;
    void resize(int new_size){
        // Initalize array to proper size. Replace old data, Note: this will erase old data. Update size varible
        if (VDsize > 0) delete[] data;
        data = new double[new_size];
        VDsize = new_size;
    }
    int size(){
        //returns size
        return(VDsize);
    }

    void del(){
        // deallocates data
        if (VDsize > 0) delete[] data;
    }

    double& operator[](int index) {
        // check if the index is in range then return the value in index
        return data[index];
    }

    const double& operator[](int index) const {
        // check if the index is in range then return the value in index
        return data[index];
    }
};

class VDD{
  public:
    int VDDsize = 0;
    VD* data;
    void resize(int new_size){
        // Initalize array to proper size. Replace old data, Note: this will erase old data. Update size varible
        if (VDDsize > 0) delete[] data;
        data = new VD[new_size];
        VDDsize = new_size;
    }
    int size(){
        //returns size
        return(VDDsize);
    }
    void del(){
        // deallocates data
        if (VDDsize > 0) delete[] data;
    }

    VD& operator[](int index) {
        // check if the index is in range then return the value in index
        return data[index];
    }

    const VD& operator[](int index) const {
        // check if the index is in range then return the value in index
        return data[index];
    }
};

class VI{


public:
    int VIsize = 0;
    int* data;
    void resize(int new_size){
        // Initalize array to proper size. Replace old data, Note: this will erase old data. Update size varible
        if (VIsize > 0) delete[] data;
        data = new int[new_size];
        VIsize = new_size;
    }
    int size(){
        //returns size
        return(VIsize);
    }
    void del(){
        // deallocates data
        if (VIsize > 0) delete[] data;
    }
    void push_back(int newVal){
        // allocate new data, transfer data to new array, deallocated old data, add new value, incriment size varible
        int* newData = new int[VIsize+1];
        for(int i = 0; i < VIsize; i++){
            newData[i] = data[i];
        }
        if (VIsize > 0) delete[] data;
        newData[VIsize] = newVal;
        data = newData;
        VIsize = VIsize+1;
    }
    int& operator[](int index) {
        // check if the index is in range then return the value in index
        return data[index];
    }

    const int& operator[](int index) const {
        // check if the index is in range then return the value in index
        return data[index];
    }

    
};

class VII{
  public:
    int VIIsize = 0;
    VI* data;
    void resize(int new_size){
        // Initalize array to proper size. Replace old data, Note: this will erase old data. Update size varible
        if (VIIsize > 0) delete[] data;
        data = new VI[new_size];
        VIIsize = new_size;
    }
    int size(){
        //returns size
        return(VIIsize);
    }
    void del(){
        // deallocates data
        if (VIIsize > 0) delete[] data;
    }
    VI& operator[](int index) {
        // check if the index is in range then return the value in index
        return data[index];
    }

    const VI& operator[](int index) const {
        // check if the index is in range then return the value in index
        return data[index];
    }
};

void Exit()
{
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
  exit(0);
}


void FatalError(string msg)
{

  cout << " " << endl;
  cout << " " << endl;
  cout << "Fatal Error on this PE: " << msg << endl;
  cout << " " << endl;
  Exit();


}


// ==
// ||
// ||
// ||  timingInfo:  This class can be used to compute the execution time of the code or
// ||               any of its routines.
// ||
// ==

class timingInfo
{
 public:

  // Name of the intenty for which timing is desired

  string name;

  // Two methods of recording time:
  
  double       startSeconds ,  endSeconds ;  // (1)
  std::clock_t startCPUtime ,  endCPUtime ;  // (2)


  timingInfo()
    {
      name = "timingInfo name not set";
    }
    
  timingInfo(string _name)
    {
      name = _name;
    }
    
  void Start(int myPE)
  {

    // Record start time using two methods
    
    startSeconds = MPI_Wtime();              // (1)
    startCPUtime = std::clock();             // (2)
    
    if ( myPE == 0)
      {
	cout << "[timingInfo] [" << name << "] Start time (Wall): " << startSeconds << " Start time (CPU) : " << startCPUtime << endl;
      }

  }

  void Finish(int myPE)
  {

    // Record finish time using two methods
    
    endSeconds = MPI_Wtime();               // (1)
    endCPUtime = std::clock();              // (2)

    // Compute elapsed time
    
    double elapsedSeconds = endSeconds - startSeconds;  // (1)
    double elapsedCPUtime = endCPUtime - startCPUtime;  // (2)

    // Report results
    
    if ( myPE == 0)
      {

	// (1) results
	
	cout << "[timingInfo] [" << name << "] Finish time (Wall): " << endSeconds <<
	                                     " Finish time (CPU) : " << endCPUtime << endl;

	// (2) results
	
	cout << "[timingInfo] [" << name << "] Elapsed time (Wall, seconds): "  << elapsedSeconds <<
	                                     " Elapsed time (CPU, seconds) : "  << elapsedCPUtime/ (double) CLOCKS_PER_SEC << endl;
      }
    
    return ;
    
  }

};


// ====================================================================================
// ||                                                                                ||
// ||                      T i m i n g   U t i l i i t e s                           ||
// ||                                                                                ||
// ====================================================================================

void StartTimer(struct timespec &t0  )
{
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t0);
}

void EndTimer( string KernelName , struct timespec &t0 , struct timespec &t1 )
{
  // The timespec struct provides time information in this format:
  //
  // tv_sec:tv_nsec  
  //
  // which should be thought of as an anology to the more commonly understood
  // time format
  //
  //  HH:MM:SS
  //
  // So in order to compute elapsed time, one must subtract each place (e.g., HH, MM, SS),
  // and add the differences while including units conversion

  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t1);

  int64_t sec_place     = t1.tv_sec  - t0.tv_sec ;
  int64_t ns_place      = t1.tv_nsec - t0.tv_nsec;
  int64_t sec_2_ns      = 1000000000;
  int64_t exeTime_in_ns = sec_place*sec_2_ns + ns_place;

  cout << "[ " << KernelName << " ] EXECUTION TIME  = " << exeTime_in_ns << " (ns)" << endl;
}
