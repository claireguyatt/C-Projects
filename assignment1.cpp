#include <iostream>

using namespace std;

const int rows = 5;
const int cols = 5;

// function that takes an input password and determines if it is valid
void checkPassword()
{

    // bool to keep track of if password is valid
    bool valid = true;

    // ask for password and assign input string to a variable
    cout << "Input password" << endl;
    string pwrd;
    cin >> pwrd;

    // test length of password and display corresponding error message
    if (pwrd.length() < 8)
    {
        cout << "Input password must be at least 8 characters.\n";
        valid = false;
    }

    // bools to test that the password has a number & a special character & no triple repeats
    bool num = false;
    bool special = false;
    bool repeat = false;

    // test for char repeats & display corresponding error message
    for (int i = 0; i < pwrd.length(); i++)
    {

        char c = pwrd.at(i);

        if (c >= '0' && c <= '9')
        {
            num = true;
        }
        if (c == '*' || c == '#' || c == '$')
        {
            special = true;
        }

        // int to keep track of character count
        int count = 0;

        // only display repeat error message once
        if (repeat == false)
        {

            for (int j = 0; j < pwrd.length(); j++)
            {
                char d = pwrd.at(j);
                if (c == d)
                {
                    count++;
                    if (count > 2)
                    {
                        cout << "Input password must not repeat characters more than twice.\n";
                        repeat = true;
                        valid = false;
                        break;
                    }
                }
            }
        }
    }
    // test that password has a number and display corresponding error message
    if (num == false)
    {
        cout << "Input password must contain a number.\n";
        valid = false;
    }
    // test that the password has a special character and display corresponding error message
    if (special == false)
    {
        cout << "Input password must contain a special character.\n";
        valid = false;
    }

    // check if password is valid and display corresponding message
    if (valid == true)
    {
        cout << "Password has been accepted.\n";
    }
}

// function that takes an input word and converts it to its corresponding phonetic alphabet
void convertPhonetic()
{
    // string array containing NATO phonetic alphabet
    string alph[26] = {"Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India", "Juliett", "Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo", "Sierra", "Tango", "Uniform", "Victor", "Whiskey", "X-ray", "Yankee", "Zulu"};

    // ask for word and assign input string to a variable
    cout << "Please enter a word:\n";
    string word;
    cin >> word;

    // go through the word letter by letter
    for (int i = 0; i < word.length(); i++)
    {
        // print corresponding NATO word for each letter (case insensitive)
        // by getting the word from the array using the char's ASKI val
        char c = word.at(i);
        if (c >= 97 && c <= 122)
        {
            int map = c - 97;
            cout << alph[map] << " ";
        }
        if (c >= 65 && c <= 90)
        {
            int map = c - 65;
            cout << alph[map] << " ";
        }
    }
    cout << "\n";
}

// function to fill a matrix with randomly generated numbers
void fillMatrix(int matrix[rows][cols])
{
    // go through each column of each row
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // set range of random numbers from 0-25
            matrix[i][j] = rand() % (25 + 1);
        }
    }
}

// function that prints each row of an input matrix
void printMatrix(int matrix[rows][cols])
{
    // go through each col then each row
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // format the output properly
            if (j != 4)
            {
                cout << matrix[i][j] << " | ";
            }
            else
            {
                cout << matrix[i][j];
            }
        }
        cout << "\n---------------------------------\n";
    }
    cout << "\n";
}

void multiplyMatrices(int matrix_left[rows][cols], int matrix_right[rows][cols], int matrix_result[rows][cols])
{
    // ints to keep track of current cell row/col of new matrix & col/row to be multiplied
    // keep static so they're not always put back to zero at every entrance to the function
    static int i = 0, j = 0, k = 0;

    // stop when done
    if (i >= rows)
    {
        return;
    }
    
    // don't go past the row/col limit
    if (j < cols)
    {
        if (k < rows)
        {
            // fill result maatrix by multiplying input matrices cells
            matrix_result[i][j] += (matrix_left[i][k] * matrix_right[k][j]);
            // move onto next cell to be multiplied
            k++;

            multiplyMatrices(matrix_left, matrix_right, matrix_result);
        }
        // move onto right cell
        k = 0;
        j++;
        multiplyMatrices(matrix_left, matrix_right, matrix_result);
    }
    // move onto right cell
    j = 0;
    i++;
    multiplyMatrices(matrix_left, matrix_right, matrix_result);
}


void transposeMatrix(int matrix[5][5])
{
for (int i = 0; i < 5; i++) {
for (int j = 0; j < 5; j++) {


swap(matrix[i][j], matrix[j][i]);

}
}
printMatrix(matrix);
}

int main()
{
    //checkPassword();
    //convertPhonetic();
    int matrix[rows][cols];
    //int matrix2[rows][cols];
    //int matrix_result[rows][cols];
    fillMatrix(matrix);
    //fillMatrix(matrix2);
    printMatrix(matrix);
    //printMatrix(matrix2);
    //multiplyMatrices(matrix, matrix2, matrix_result);
    //printMatrix(matrix_result);
    transposeMatrix(matrix);
    //printMatrix(matrix);
    return 0;
}