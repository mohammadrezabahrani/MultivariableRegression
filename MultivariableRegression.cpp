#include <iostream>
#include <iterator> // Include the <iterator> library for begin() and end()
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class MultivariableRegression {

    public:
        void Read_Csv_Data(std::string path,bool header=false,int index_Y_data=0)
        {
            std::string& filename = path;
            csvToMatrix(filename,header,index_Y_data);
            printMatrix(X);
        }
       
    private:
        std::vector<std::vector<int>> X;
        std::vector<int> Y;
      
        void Sum_eachX()
        {
            
        }

        void printMatrix(const std::vector<std::vector<int>>& matrix) {
            for (const auto& row : matrix) {
                for (int value : row) { std::cout << value << " "; }
                std::cout << std::endl;
            }
        }

        void csvToMatrix(const std::string& filename,bool header=false,int index_Y=0) {
            std::vector<std::vector<int>> matrix;
            std::ifstream file(filename);
            std::string line;
            bool fersirow = true;
            while (std::getline(file, line)) {
                std::vector<int> row;
                std::stringstream ss(line);
                std::string cell;
                int lastIndexDefalut = countCharInString(line,',');
                if(index_Y==0){ index_Y = lastIndexDefalut; }

                if(header && fersirow) {fersirow=false; continue;}
                while (std::getline(ss, cell, ',')) {
                    row.push_back(std::stoi(cell)); // Convert string to integer
                }
                Y.push_back(row[index_Y]);
                row[index_Y] = 1;
                matrix.push_back(row);
            }
            file.close();
            X =  matrix;
        }


        int countCharInString(const std::string& str, char ch) {
            int count = 0;
            for (char c : str) { if (c == ch) { count++; } }
            return count;
        }

};

int main() {
    cout<<"****************** START *****************" <<endl<<endl;
    

   MultivariableRegression m;
   m.Read_Csv_Data("sampledata.csv",true);

    

    cout<<endl<<"******************* END ******************" <<endl;
    return 0;
}