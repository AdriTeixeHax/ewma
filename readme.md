# EWMA C Algorithm

This repository provides an implementation of the Exponentially Weighted Moving Average (EWMA) algorithm, useful for averaging non-periodic datasets. The general equation of this algorithm is the following:

$$\textit{EWMA}(t) = \alpha \cdot X(t) + (1 - \alpha) \cdot \textit{EWMA}(t-1)$$

Where $\alpha$ is a smoothing factor. The program works by providing a dataset and an $\alpha$ value.

## Installation

Clone the repository and copy the `ewma.h` header file into your C project:

```bash
git clone https://github.com/AdriTeixeHax/ewma.git
```

## Usage

1. Include the header file.
```C
#include "ewma.h"
```

2. Provide a dataset in the form of a `float` or `double` array. Calculate its size.
```C
double data[] = { <double array> };
size_t dataSize = sizeof(data) / sizeof(data[0]);
```

3. Provide an alpha value.
```C
double alpha = <value>;
```

4. Define an EWMA structure.
```C
EWMA_TypeDef ewma;
```

5. Use either of the two functions implemented:

- Using `EwmaUpdate()`. Initialize the structure via the `EwmaInit()` function. Then, calculate the EWMA value for each point in the dataset provided.
```C
if (EwmaInit(&ewma, alpha) == 0) 
{
    for (size_t i = 0; i < dataSize; i++) 
    {
        double ewmaVal = EwmaUpdate(&ewma, data[i]);

        // Do something with the data calculated, for example:
        printf("%5.5f,\t%5.5f\n", data[i], ewmaVal);
    }
}
```

- Using `EwmaCalculateArray()`. First define a memory region to store the results, then call the function.
```C
double* results = (double*)malloc(dataSize * sizeof(double));
if (results != NULL && EwmaCalculateArray(data, dataSize, alpha, results) == 0) 
{
    // Do something

    free(results);
}
```

## Example

Provided in the `ewma.c` source file in this repository.

## License

This project uses the GPL 2.0 license. See [LICENSE](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html) for details.
