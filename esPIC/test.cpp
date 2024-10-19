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

using std :: string;
using std :: vector;
using std :: stringstream;
using std :: cout;
using std :: endl;
using namespace std::chrono;


class VD{


public:
    int VDsize;
    double* data;
    void resize(int new_size){
        double* newData = new double[new_size];
        data = newData;
        VDsize = new_size;
    }
    int size(){
        int oupt = VDsize;
        return(oupt);
    }
    //VD(const double*& initialData) : data(initialData) {}

    double& operator[](int index) {
        if (index >= 0 && index < VDsize) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    const double& operator[](int index) const {
        if (index >= 0 && index < VDsize) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    
};

class VDD{
  public:
    int VDDsize;
    //VDDsize[2] ;
    VD* data;
    void resize(int new_size){
        VD* newData = new VD[new_size];
        data = newData;
        VDDsize = new_size;
    }
    int size(){
        int oupt = VDDsize;
        return(oupt);
    }
    //VD(const double*& initialData) : data(initialData) {}

    VD& operator[](int index) {
        if (index >= 0 && index < VDDsize) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    const VD& operator[](int index) const {
        if (index >= 0 && index < VDDsize) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }
};

class VI{


public:
    int VIsize = 0;
    int* data;
    void resize(int new_size){
        //std::cout<< "resizeing VI" << endl;
        int* newData = new int[new_size];
        data = newData;
        VIsize = new_size;
    }
    int size(){
        //std::cout << "getting size" << endl;
        int oupt = VIsize;
        return(oupt);
    }
    //VI(const int*& initialData) : data(initialData) {}
    void push_back(int newVal){
        //std::cout << "starting push back" << endl;
        int* newData = new int[VIsize+1];
        for(int i = 0; i < VIsize; i++){
            newData[i] = data[i];
        }
        newData[VIsize] = newVal;
        data = newData;
        VIsize = VIsize+1;
        //std::cout << "ending push back" << endl;
    }
    int& operator[](int index) {
        if (index >= 0 && index < VIsize) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    const int& operator[](int index) const {
        if (index >= 0 && index < VIsize) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    
};

class VII{
  public:
    int VIIsize;
    //VIIsize[2] ;
    VI* data;
    void resize(int new_size){
        VI* newData = new VI[new_size];
        data = newData;
        VIIsize = new_size;
    }
    int size(){
        int oupt = VIIsize;
        return(oupt);
    }
    //VI(const int*& initialData) : data(initialData) {}

    VI& operator[](int index) {
        if (index >= 0 && index < VIIsize) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    const VI& operator[](int index) const {
        if (index >= 0 && index < VIIsize) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }
};

int main(){

    int n = 100;
    typedef  vector<double>          sVD;
    typedef  vector<vector<double> > sVDD;
    typedef  vector<int>             sVI;
    typedef  vector<vector<int> >    sVII;

    VD vd;
    vd[n];
    sVD svd[n];
    cout << " ====================  ==================== " <<endl;
    auto start = high_resolution_clock::now();
    for (int i=0; i< n;i++){
        vd[i] = 1.;
    }
    auto stop = high_resolution_clock::now();

    
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    return 0;

}