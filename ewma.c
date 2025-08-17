#include "ewma.h"

// Example usage and test function
int main(int argc, char** argv) 
{
    printf("EWMA Algorithm Demo\n");
    printf("==================\n\n");
    
    // Test data
    double data[] = {0.000721, 0.000721, 13.0, 0.000721, 11.0, 0.000721, 0.000721, 0.000721, 17.0, 0.000721, 0.000721, 0.000721, 0.000721, 13.3, 15.4, 0.000721, 0.000721, 0.000721, 17.5, 2.4, 0.000721, 0.000721};
    size_t dataSize = sizeof(data) / sizeof(data[0]);
    double alpha = 0.3;
    
    printf("Input data: ");
    for (size_t i = 0; i < dataSize; i++)
        printf("%.7f ", data[i]);

    printf("\n");
    printf("Alpha (smoothing factor): %.2f\n\n", alpha);
    
    // Method 1: Using EWMA structure step by step
    printf("Method 1 - Step by step updates:\n");
    EWMA_TypeDef ewma1;
    if (EwmaInit(&ewma1, alpha) == 0) 
    {
        for (size_t i = 0; i < dataSize; i++) 
        {
            double ewmaVal = EwmaUpdate(&ewma1, data[i]);
            printf("%5.7f,\t%7.3f\n", data[i], ewmaVal);
        }
    }
    
    printf("\n");
    
    // Method 2: Using array calculation function
    printf("Method 2 - Array calculation:\n");
    double* results = (double*)malloc(dataSize * sizeof(double));
    if (results != NULL && EwmaCalculateArray(data, dataSize, alpha, results) == 0) 
    {
        for (size_t i = 0; i < dataSize; i++) 
            printf("Index %zu:\tValue = %5.1f,\tEWMA = %7.3f\n", i, data[i], results[i]);

        free(results);
    }
    
    printf("\n");
    
    // Demonstrate different alpha values
    printf("Comparing different alpha values:\n");
    double alphas[] = {0.1, 0.3, 0.7};
    size_t numAlphas = sizeof(alphas) / sizeof(alphas[0]);
    
    for (size_t a = 0; a < numAlphas; a++) 
    {
        printf("\nAlpha = %.1f:\n", alphas[a]);
        EWMA_TypeDef ewmaTest;
        EwmaInit(&ewmaTest, alphas[a]);
        
        for (size_t i = 0; i < dataSize; i++) 
        {
            double val = EwmaUpdate(&ewmaTest, data[i]);
            printf("%5.1f,%7.3f\n", data[i], val);
        }
    }
    
    return 0;
}