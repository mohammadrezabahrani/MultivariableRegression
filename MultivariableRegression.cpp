#include <iostream>
#include <iterator> // Include the <iterator> library for begin() and end()
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class MultivariableRegression
{

public:
    void Read_Csv_Data(std::string path, bool header = false, int index_Y_data = 0)
    {
        std::string &filename = path;
        csvToMatrix(filename, header, index_Y_data);
        calculate_Sum_and_mean_eachX();
        calculate_Sum_and_mean_Y();
        calculate_SSX();
        calculate_SSY();
        calculate_SPXY();
        calculate_SPXX();
        // printMatrix(SPXX);
        // printMatrix(mean_each_x);
        // printMatrix(sum_each_Xx);
        calculateCoefficient();
        // printMatrix(XM);
    }

private:
    std::vector<std::vector<double>> X;
    std::vector<std::vector<double>> XM;
    std::vector<std::vector<double>> Xx;
    std::vector<double> SPXX;
    std::vector<double> sum_each_x;
    std::vector<double> mean_each_x;

    std::vector<double> SSX;
    std::vector<double> SPXY;
    std::vector<double> SXx;
    std::vector<double> Y;
    std::vector<double> b;

    double sum_y = 0;
    double mean_y = 0;
    double SSY = 0;

    //************************
    int column_count = 0;
    int row_count = 0;

    void calculate_SSX()
    {
        for (int i = 0; i < column_count; i++)
        {
            double temp = 0;
            for (int j = 0; j < row_count; j++)
            {
                temp += (X[j][i] - mean_each_x[i]) * (X[j][i] - mean_each_x[i]);
            }
            SSX.push_back(temp);
        }
    }

    void calculate_SSY()
    {
        double temp = 0;
        for (int i = 0; i < row_count; i++)
        {
            temp += (Y[i] - mean_y) * (Y[i] - mean_y);
        }
        SSY = temp;
    }

    void calculate_Sum_and_mean_eachX()
    {
        for (int i = 0; i < column_count; i++)
        {
            double sum = 0;
            for (int j = 0; j < row_count; j++)
            {
                sum += X[j][i];
            }
            sum_each_x.push_back(sum);
            mean_each_x.push_back(sum / row_count);
        }
    }

    void calculate_Sum_and_mean_Y()
    {
        double sum = 0;
        for (int i = 0; i < row_count; i++)
        {
            sum += Y[i];
        }
        sum_y = sum;
        mean_y = sum / row_count;
    }

    void calculate_SPXY()
    {
        for (int i = 0; i < column_count; i++)
        {
            double sum = 0;
            for (int j = 0; j < row_count; j++)
            {
                sum += (X[j][i] - mean_each_x[i]) * (Y[j] - mean_y);
            }
            SPXY.push_back(sum);
        }
    }

    void calculate_SPXX()
    {
        for (int i = 0; i < column_count; i++)
        {
            std::vector<double> temper;
            for (int j = 0; j < row_count; j++)
            {
                temper.push_back(X[j][i] - mean_each_x[i]);
            }
            XM.push_back(temper);
        }

        std::vector<double> sumech;
        for (int k = 0; k < row_count; k++)
        {
            for (int i = 0; i < column_count; i++)
            {

                double result = 0;
                for (int j = i + 1; j < column_count; j++)
                {
                    if (sumech.size() < column_count)
                    {
                        sumech.push_back(0);
                    }
                    result = XM[i][k] * XM[j][k];
                    // std::cout << XM[i][k] << " * " << XM[j][k] << " = " << result  << std::endl;
                    sumech[i + j - 1] += result;
                }
            }
        }
        SPXX = sumech;
    }

    void calculateCoefficient()
    {

        // cout<<SPXX[0]<<endl;

        printMatrix(SPXX);
        cout << endl;
        int size = SPXY.size();
        int spxxsize = SPXX.size();
=        for (int i = 0, j = 0; i < size; i++, j++)
        {
            double f = 0;
            if (spxxsize == 2 and j > 0)
            {
                j--;
            }

            // b1 = (SPX1Y * SSX2 - SPX1X2 * SPX2Y) / (SSX1 * SSX2 - SPX1X2 * SPX1X2)
            // b2 = (SPX2Y * SSX1 - SPX1X2 * SPX1Y) / (SSX1 * SSX2 - SPX1X2 * SPX1X2)
            // b3 = (SPX3Y * SSX1 - SPX1X3 * SPX1Y) / (SSX1 * SSX3 - SPX1X3 * SPX1X3)

            if (i == 0)
            {
                f = (SPXY[i] * SSX[i + 1] - SPXX[j] * SPXY[i + 1]) / ((SSX[0] * SSX[i + 1]) - (SPXX[j] * SPXX[j]));
            }
            else
            {
                f = (SPXY[i] * SSX[0] - SPXX[j] * SPXY[0]) / ((SSX[0] * SSX[i]) - (SPXX[j] * SPXX[j]));
            }
            b.push_back(f);
        }
        printMatrix(b);
        // double f = (SPXY[0]* SSX[1]  - SPXX[0] * SPXY[1]) / ((SSX[0]*SSX[1])- (SPXX[0] * SPXX[0]));
    }

    void printMatrix(const std::vector<std::vector<double>> &matrix)
    {
        for (const auto &row : matrix)
        {
            for (double value : row)
            {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
    }
    void printMatrix(std::vector<double> &matrix)
    {
        for (const auto &row : matrix)
        {
            std::cout << row << " ";
        }
    }

    void csvToMatrix(const std::string &filename, bool header = false, int index_Y = 0)
    {
        std::vector<std::vector<double>> matrix;
        std::ifstream file(filename);
        std::string line;
        bool fersirow = true;
        while (std::getline(file, line))
        {
            std::vector<double> row;
            std::stringstream ss(line);
            std::string cell;
            int lastIndexDefalut = countCharInString(line, ',');
            if (index_Y == 0)
            {
                index_Y = lastIndexDefalut;
            }
            column_count = lastIndexDefalut++;
            if (header && fersirow)
            {
                fersirow = false;
                continue;
            }
            while (std::getline(ss, cell, ','))
            {
                row.push_back(std::stoi(cell)); // Convert string to integer
            }
            Y.push_back(row[index_Y]);

            row[index_Y] = 1;
            matrix.push_back(row);
            row_count++;
        }
        file.close();
        X = matrix;
    }

    int countCharInString(const std::string &str, char ch)
    {
        int count = 0;
        for (char c : str)
        {
            if (c == ch)
            {
                count++;
            }
        }
        return count;
    }
};

int main()
{
    cout << "****************** START *****************" << endl
         << endl;

    MultivariableRegression m;
    m.Read_Csv_Data("sampledata.csv", true);

    cout << endl
         << "******************* END ******************" << endl;
    return 0;
}