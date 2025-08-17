#ifndef _EWMA__H_
#define _EWMA__H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * EWMA_TypeDef (Exponentially Weighted Moving Average) structure.
 * 
 * Maintains state for calculating running EWMA values.
 */
typedef struct 
{
    double alpha;        // Smoothing factor (0 < alpha <= 1).
    double ewma;         // Current EWMA value.
    bool   initialized;  // Whether EWMA_TypeDef has been initialized.
} EWMA_TypeDef;

/**
 * Initialize EWMA_TypeDef structure.
 * @param ewma Pointer to EWMA_TypeDef structure.
 * @param alpha Smoothing factor (0 < alpha <= 1). Higher alpha = more weight to recent values. Lower alpha = more smoothing.
 * @return 0 on success, -1 on error.
 */
int EwmaInit(EWMA_TypeDef* ewma, double alpha) 
{
    if (ewma == NULL || alpha <= 0.0 || alpha > 1.0)
        return -1;
    
    ewma->alpha = alpha;
    ewma->ewma = 0.0;
    ewma->initialized = false;
    
    return 0;
}

/**
 * Update EWMA with new value.
 * 
 * Formula: EWMA(t) = alpha * X(t) + (1 - alpha) * EWMA(t-1).
 * 
 * For first value: EWMA(0) = X(0).
 * 
 * @param ewma Pointer to EWMA_TypeDef structure.
 * @param value New data point.
 * @return Updated EWMA value, or 0.0 on error.
 */
double EwmaUpdate(EWMA_TypeDef* ewma, double value) 
{
    if (ewma == NULL)
        return 0.0;
    
    if (!ewma->initialized) 
    {
        // Initialize with first value
        ewma->ewma = value;
        ewma->initialized = true;
    } 
    else 
        // Apply EWMA formula
        ewma->ewma = ewma->alpha * value + (1.0 - ewma->alpha) * ewma->ewma;
    
    return ewma->ewma;
}

/**
 * Get current EWMA value.
 * @param ewma Pointer to EWMA_TypeDef structure.
 * @return Current EWMA value, or 0.0 if not initialized.
 */
double EwmaGetValue(const EWMA_TypeDef* ewma) 
{
    if (ewma == NULL || !ewma->initialized)
        return 0.0;

    return ewma->ewma;
}

/**
 * Reset EWMA_TypeDef to uninitialized state.
 * @param ewma Pointer to EWMA_TypeDef structure
 */
void EwmaReset(EWMA_TypeDef* ewma) 
{
    if (ewma != NULL) 
    {
        ewma->ewma = 0.0;
        ewma->initialized = false;
    }
}

/**
 * Simple function to calculate EWMA for an array of values.
 * @param values Array of input values.
 * @param size Size of the array.
 * @param alpha Smoothing factor.
 * @param result Output array for EWMA values (must be pre-allocated).
 * @return 0 on success, -1 on error.
 */
int EwmaCalculateArray(const double* values, size_t size, double alpha, double* result) {
    if (values == NULL || result == NULL || size == 0 || alpha <= 0.0 || alpha > 1.0)
        return -1;
    
    EWMA_TypeDef ewma;

    if (EwmaInit(&ewma, alpha) != 0)
        return -1;
    
    for (size_t i = 0; i < size; i++)
        result[i] = EwmaUpdate(&ewma, values[i]);
    
    return 0;
}

#endif