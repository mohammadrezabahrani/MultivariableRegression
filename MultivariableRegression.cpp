#include <iostream>
#include <vector>

std::vector<double> multivariableRegression(const std::vector<std::vector<double>>& X, const std::vector<double>& Y) {
    int numVariables = X[0].size();  // Number of independent variables
    int numSamples = X.size();  // Number of data samples

    // Calculate means
    std::vector<double> means(numVariables, 0.0);
    double meanY = 0.0;

    for (int j = 0; j < numVariables; j++) {
        for (int i = 0; i < numSamples; i++) {
            means[j] += X[i][j];
        }
        means[j] /= numSamples;
    }

    for (int i = 0; i < numSamples; i++) {
        meanY += Y[i];
    }
    meanY /= numSamples;

    // Calculate cross-products
    std::vector<double> sumXY(numVariables, 0.0);

    for (int i = 0; i < numSamples; i++) {
        for (int j = 0; j < numVariables; j++) {
            sumXY[j] += X[i][j] * Y[i];
        }
    }

    // Calculate sum of squares
    std::vector<double> sumX2(numVariables, 0.0);

    for (int i = 0; i < numSamples; i++) {
        for (int j = 0; j < numVariables; j++) {
            sumX2[j] += X[i][j] * X[i][j];
        }
    }

    // Calculate regression coefficients
    std::vector<double> coefficients(numVariables, 0.0);
    std::vector<double> sumX(numVariables, 0.0);

    for (int i = 0; i < numSamples; i++) {
        for (int j = 0; j < numVariables; j++) {
            sumX[j] += X[i][j];
        }
    }

    for (int i = 0; i < numVariables; i++) {
        double denominator = numSamples * sumX2[i] - sumX[i] * sumX[i];
        double numerator = numSamples * sumXY[i] - sumX[i] * meanY;
        coefficients[i] = numerator / denominator;
    }

    // Calculate intercept term
    double intercept = meanY;

    for (int i = 0; i < numVariables; i++) {
        intercept -= coefficients[i] * means[i];
    }

    std::vector<double> result;
    result.push_back(intercept);
    result.insert(result.end(), coefficients.begin(), coefficients.end());

    return result;
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

    // Calculate regression coefficients and intercept
    std::vector<double> result = multivariableRegression(X, Y);

    double intercept = result[0];
    std::vector<double> coefficients(result.begin() + 1, result.end());

    // Print the intercept and regression coefficients
    std::cout << "Intercept (a): " << intercept << std::endl;
    std::cout << "Regression Coefficients:" << std::endl;
    for (int i = 0; i < coefficients.size(); i++) {
        std::cout << "b" << i + 1 << " = " << coefficients[i] << std::endl;
    }

    return 0;
}
