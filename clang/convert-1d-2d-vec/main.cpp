#include "utils/VectorConversion.hpp"

int main()
{
    int row_size = 3;
    auto result = convert_1D_to_2D_vector(5, row_size);
    printf("x: %d, y: %d\n", result.x, result.y);
    auto result2 = convert_2D_to_1D_vector(result.x, result.y, row_size);
    printf("index: %d", result2);
    return 0;
}
