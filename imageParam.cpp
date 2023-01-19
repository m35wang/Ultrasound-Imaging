#include "imageParam.h"
using namespace std;

//default constructor
imageParam::imageParam()
{
    //assigning values of default constructor
    numElement = 128;
    numSample = 3338;
    numScanline = 127;

    //assign 1D array to elementPosition
    elementPosition = genElementPosition();

    //assign 2D array to scanlinePosition
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition);

}

 //delete allocated memory for dataMatrix
imageParam::~imageParam()
{
    deletePositionArray();
}

// create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{
    float *elementPosition; 

    //allocate new memory to create 1D array
    elementPosition = new float[numElement]; 

    for (int n=0; n < numElement; n++)
    {
        //create location in x-axes 
        elementPosition[n] = (n-((float(numElement)-1)/2))*PITCH; 
    }

    //return dynamic 1D array
    return elementPosition;
    
}

//forming the position of each scanline
float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float* elementLocation)
{
    //user input the depth
    cout << "Please enter desired imaging depth: "; 
    cin >> desiredDepth;

    //user input number of pixels
    cout << "Please enter number of pixels per scanline: ";
    cin >> numPixel;

    //calculate the incriment of depth to number of pixels
    float incriment = desiredDepth/((float)numPixel - 1); 
    //the start depth is always 0
    float startDepth = 0; 

    float2 **scanlinePosition; 
    //allocate memory for 2D array
    scanlinePosition = new float2 *[numScanline];  

    for (int i = 0; i < numScanline; i++)
    {
        //forming array under each pointer by allocating new memory
        scanlinePosition[i] = new float2[numPixel];
    }

    for (int m = 0; m < numScanline; m++)
    {
        //assigning starting depth of each scanline to be 0
        scanlinePosition[m][0].y = startDepth;

        for (int q = 1; q < numPixel; q ++)
        {
            //assigning the position (wdith and depth) to both x and y component
            scanlinePosition[m][(q-1)].x = (m - ((float(numScanline) - 1)/2))*PITCH;  
            scanlinePosition[m][q].y = incriment + (scanlinePosition[m][q-1].y);
        }
        
    }

    //return 2D position array
    return scanlinePosition;

}

//get specific x component position(width)
float imageParam::getXPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].x;
}

//get specific y component position(depth)
float imageParam::getYPosition(int scanline, int pixel)
{
    return scanlinePosition[scanline][pixel].y;
}

//get the position of the element on x-axes
float imageParam::getElementPosition(int element)
{
    return elementPosition[element];
}

//get number of elements 
int imageParam::getNumElement()
{
    return numElement;
}

//get number of samples
int imageParam::getNumSample()
{
    return numSample;
}

//get number of scanlines
int imageParam::getNumScanline() 
{
    return numScanline;
}

//get number of pixels
int imageParam::getNumPixel() 
{
    return numPixel;
}

//delete allocated position 2D array memory
void imageParam::deletePositionArray()
{
    //delete pointer within array
    for(int i = 0; i < numScanline; i++)
    {
        delete scanlinePosition[i];
    }
    //delete pointer to 2D array
    delete scanlinePosition;

    //delete pointer to 2D array
    delete elementPosition;
}
