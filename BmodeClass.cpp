#include "BmodeClass.h"
using namespace std;

//default constructor
BmodeClass::BmodeClass()
{
    //assigning values of default constructor
    imparams = NULL;
    RFData = NULL;
    next = NULL;

    line = 0;
}

//parametrized constructor
BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline)
{
    //assign inputed values to constructor values
    imparams = params; //pointer to access image parameters
    RFData = data; //pointer to access retrieved data
    line = numline; //pointer to access scanline number

    //assign created 1D array to scanline
    scanline = createScanline(imparams->getNumPixel()); //accessing numPixel(private variable) from other class file
    beamform();
}

//delete allocated memory for scanline
BmodeClass::~BmodeClass()
{
    deleteScanline();
}

//create 1D array for scanline
float *BmodeClass::createScanline(int numPixel)
{
    float *mem;

    //allocate new memory to create 1D array
    mem = new float[numPixel];

    //return created array
    return mem;
}


void BmodeClass::beamform()
{
    //assign all values to 0
    float tForward = 0; 
    float tBack = 0;
    float tTotal = 0;

    //assign s variable to integer
    int s;
    
    //calculations for each scanline; loop for all number of pixels wanted
    for(int i = 0; i < (imparams -> getNumPixel()); i++) 
    {
        //declare the sums as 0 everytime we change pixels("location")
        float sumR = 0; 
        float sumI = 0;

        //calculate time forward
        tForward = (imparams->getYPosition(line,i)/(imparams->SOS));

        //loop of each element within each pixel incriment
        for(int x = 0; x < (imparams -> getNumElement()); x++) 
        {
            //calculate time back
            tBack = (sqrt((pow((imparams->getYPosition(line,i)),2))+ (pow(imparams->getXPosition(line,i) - imparams->getElementPosition(x),2)))/imparams->SOS); 
            
            //calculate total time
            tTotal = tForward + tBack; 
            
            //calculate sample
            s = floor(tTotal*(imparams->FS)); 

            //the sample is within the sample range
            if (s < imparams->getNumSample()) {
                sumR += RFData -> getRealRFData(x,s); //the sum of all the real parts
                sumI += RFData -> getImagRFData(x,s); //the sum of all imaginary parts
            }
        }

        //allocate results to scanline array
        scanline[i] = sqrt(pow(sumR,2) + pow(sumI,2));
    }

}

void BmodeClass::getScanline(float *data)
{
    for (int i = 0; i < (imparams -> getNumPixel()); i++ )
    {
        data[i] = scanline[i];
    }
}

void BmodeClass::deleteScanline()
{
    delete scanline;
}