#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

void readFile(int totalArray[] ,string fileName, int numberofIntegers){
    ifstream file;
    file.open(fileName);
    for(int i = 0; i < numberofIntegers; i++){
        file >> totalArray[i];
    }
    file.close();
}

void createOutputFile(int totalArray[], int numberofIntegers){
    ofstream outfile("output.txt");
    
    for(int i = 0; i < numberofIntegers; i++)
        outfile << totalArray[i] << endl;
    
    outfile.close();
}

void mergeSort(int totalArray[], int lowerIndex, int upperIndex);
void merge(int totalArray[], int lowerIndex, int midIndex, int upperIndex);
void bubbleSort(int totalArray[], int numberofIntegers);
void swap(int *first, int *second);

int main(int argc, const char * argv[]) {
    string typeofSort = argv[1];
    int numberofIntegers = atoi(argv[2]);
    string fileName = argv[3];
    int totalArray[numberofIntegers];
    
    readFile(totalArray, fileName, numberofIntegers);
    
    clock_t time = clock();
    
    if(typeofSort == "m")
        mergeSort(totalArray, 0, numberofIntegers-1);
    
    else if(typeofSort == "b")
        bubbleSort(totalArray, numberofIntegers);
    
    else
        cout << "Invalid algorithm type!";
    
    if(typeofSort == "m" || typeofSort == "b"){
        time = clock() - time;
        cout << ((float)time)/CLOCKS_PER_SEC;
        createOutputFile(totalArray, numberofIntegers);
    }
    return 0;
}

void bubbleSort(int totalArray[], int numberofIntegers){
    int i = numberofIntegers;
    bool sorted = false;
    int temp;
    
    while(i > 1 && sorted == false){
        sorted = true;
        for(int j = 1; j < i; j++){
            if(totalArray[j] < totalArray[j-1]){
                //swap(&totalArray[j], &totalArray[j-1]);
                temp = totalArray[j];
                totalArray[j] = totalArray[j-1];
                totalArray[j-1] = temp;
                sorted = false;
            }
        }
        i--;
    }
}

void swap(int *first, int *second){
    int temp = *first;
    *first = *second;
    *second = temp;
}

void mergeSort(int totalArray[], int lowerIndex, int upperIndex){
    int midIndex = (lowerIndex+upperIndex)/2;
    if (lowerIndex < upperIndex){
        mergeSort(totalArray, lowerIndex, midIndex);
        mergeSort(totalArray, midIndex+1, upperIndex);
        merge(totalArray, lowerIndex, midIndex, upperIndex);
    }
}

void merge(int totalArray[], int lowerIndex, int midIndex, int upperIndex){
    int sizeLower = midIndex - lowerIndex + 1;
    int sizeUpper = upperIndex - midIndex;
    int lowerArray[sizeLower], upperArray[sizeUpper];   // temp arrays
    
    for(int i = 0; i < sizeLower; i++)  // filling temp arrays
        lowerArray[i] = totalArray[lowerIndex+i];
    
    for(int i = 0; i < sizeUpper; i++)
        upperArray[i] = totalArray[midIndex+1+i];
    
    int i = 0, j= 0, k = lowerIndex;
    
    while(i < sizeLower && j < sizeUpper){
        if(lowerArray[i] <= upperArray[j]){
            totalArray[k] = lowerArray[i];
            i++;
        }
        else{
            totalArray[k] = upperArray[j];
            j++;
        }
        k++;
    }
    while(i < sizeLower){   // if lower array still has elements
        totalArray[k] = lowerArray[i];
        i++;
        k++;
    }
    while(j < sizeUpper){   // if upper array still has elements
        totalArray[k] = upperArray[j];
        j++;
        k++;
    }
}
