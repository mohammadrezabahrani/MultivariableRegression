#include <iostream>
#include <vector>

// Function to calculate multivariable regression coefficients
std::vector<double> multivariableRegression(const std::vector<std::vector<double>>& X, const std::vector<double>& Y) {
    int numVariables = X[0].size();  // Number of independent variables
    int numSamples = X.size();  // Number of data samples

    // Calculate sums and cross-products
    std::vector<double> sumX(numVariables, 0.0);
    std::vector<double> sumXY(numVariables, 0.0);
    double sumY = 0.0;
    double sumX2 = 0.0;

    for (int i = 0; i < numSamples; i++) {
        for (int j = 0; j < numVariables; j++) {
            sumX[j] += X[i][j];
            sumXY[j] += X[i][j] * Y[i];
        }
        sumY += Y[i];
        sumX2 += X[i][0] * X[i][0];  // Assuming the first variable is X1
    }

    // Calculate regression coefficients
    std::vector<double> coefficients(numVariables, 0.0);
    double denominator = numSamples * sumX2 - sumX[0] * sumX[0];  // Assuming the first variable is X1

    for (int i = 0; i < numVariables; i++) {
        double numerator = numSamples * sumXY[i] - sumX[i] * sumY;
        coefficients[i] = numerator / denominator;
    }

    return coefficients;
}

int main() {
    std::vector<std::vector<double>> X = {
        {152, 230, 325},
        {135, 234, 326},
        {165, 231, 320},
        {175, 260, 345},
        {136, 125, 325}
    };

    std::vector<double> Y = {15, 17, 15, 18, 20};

    // Calculate regression coefficients
    std::vector<double> coefficients = multivariableRegression(X, Y);

    // Print the regression coefficients
    std::cout << "Regression Coefficients:" << std::endl;
    for (int i = 0; i < coefficients.size(); i++) {
        std::cout << "b" << i+1 << " = " << coefficients[i] << std::endl;
    }

    return 0;
}
