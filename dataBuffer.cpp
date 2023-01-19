#include "dataBuffer.h"
using namespace std;

//default constructor
dataBuffer::dataBuffer() 
{
    //default constructor values
    numElement = 0;
    numSample = 0;
    scanline = 0;

    dataMatrix = NULL;
    next = NULL;
}

//paramatized constructor
dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline) 
{
    //assign inputed values to constructor values
    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;

    //form 2D array and assign to dataMatrix
    dataMatrix = createDataMatrix();

    //populate dataMatrix with extracted data
    int num = loadRFData(dataMatrix, imagFile, realFile);
} 

 //delete allocated memory for dataMatrix
dataBuffer::~dataBuffer()
{
    deleteDataMatrix();
}

//form dynamic 2D array
complex **dataBuffer::createDataMatrix()
{
    complex **RFData;  
    
    //allocate new memory to form 2D array
    RFData = new complex*[numElement];

    //forming array under each pointer by allocating new memory
    for (int i = 0; i < numElement; i++){ 
        RFData[i] = new complex[numSample];
    }

    //return created array
    return RFData;

}

//retrieving data from inputted files and loading it into RFData 
int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 
    //temporary array 
    const int numLength = 100;
    char temp[numLength];

    //loading retrieved data into each component of the element in the 2D array
    for (int i = 0; i < numElement; i++) 
    {
        for (int x = 0; x < numSample; x++)
        {
            //getting data from imaginary file into temporary array
            imagFile->getline(temp,numLength);
            //changing char data into float and loading into imaginary component of element
            RFData[i][x].imag = atof(temp);

            //getting data from real file into temporary array
            realFile->getline(temp,numLength);
            //changing char data into float and loading into real component of element
            RFData[i][x].real = atof(temp);
        }
    }

    //if unable to retrieve imaginary file
    if (imagFile->fail()) 
		return -1;

    //if unable to retrieve real file
    else if (realFile->fail()) 
		return -1;

    return 0;
}

//get specific retrieved real data from dataMatrix
float dataBuffer::getRealRFData(int element,int sample)
{
    return dataMatrix[element][sample].real;
     
}

//get specific retrieved imaginary data from dataMatrix
float dataBuffer::getImagRFData(int element,int sample)
{
    return dataMatrix[element][sample].imag;
}

//delete allocated memory for dataMatrix
void dataBuffer::deleteDataMatrix()
{
    //delete pointer within array 
    for(int i = 0; i < numElement; i++)
    {
        delete dataMatrix[i];
    }

    //delete pointer of 2D array
    delete dataMatrix;

}




