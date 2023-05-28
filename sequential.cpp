#include<bits/stdc++.h>
using namespace std;

void random_initialization(vector<vector<float>> &matrix)
{
    cout<<"\nRandomly initializing input matrix A ....."<<endl;

    int size = matrix.size();

    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            matrix[i][j] = (rand()%10)+1;
        }
    }

    // Making the matrix diagonal dominant, so that it is invertible
	int diagonal = 0;
    float sum = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			sum += abs(matrix[i][j]);   // sum of all values in column j
		}
		
		sum -= abs(matrix[i][diagonal]);  //Removing the diagonal value from the sum

        // For diagonal dominance, diagonal > sum of all other elements
		matrix[i][diagonal] = sum + (rand()%5)+1;

		diagonal++;
        sum = 0;
	}
}

void print_matrix(vector<vector<float>> matrix)
{
    int size = matrix.size();
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            cout <<left<<setw(9)<<setprecision(3)<<matrix[i][j]<<left<<setw(9);
        }
        cout<<endl;
    }
    cout<<endl;
}

void LU_Decomposition(vector<vector<float>> &A,vector<vector<float>> &L,vector<vector<float>> &U)
{
    int size = A.size();

    // Finding lower triangular matrix L
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if (j < i)   // set upper diagonal elements to 0
			{
				L[j][i] = 0;
				continue;
			}
            L[j][i] = A[j][i];
			for (int k = 0; k < i; k++)
			{
				//deduct from the current L cell the value of these 2 values multiplied
				L[j][i] = L[j][i] - L[j][k] * U[k][i];
			}
        }
    }

    // Finding upper triangular matrix U
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if (i > j)
			{
				U[i][j] = 0;
				continue;
			}
			//if they're equal, set u's current index to 1
			if (j == i)
			{
				U[i][j] = 1;
				continue;
			}
			//otherwise, do some math to get the right value
			U[i][j] = A[i][j] / L[i][i];
			for (int k = 0; k < i; k++)
			{
				U[i][j] = U[i][j] - ((L[i][k] * U[k][j]) / L[i][i]);
			}
        }
    }
}

int main()
{
    cout<<"\n----- SEQUENTIAL IMPLEMENTATION OF LU DECOMPOSITION -----"<<endl;

    double runtime = 0.0;

    int size;
    cout<<"\nEnter the size of the matrix : ";
    cin>>size;

    vector<vector<float>> A(size,vector<float>(size));
    vector<vector<float>> L(size,vector<float>(size));
    vector<vector<float>> U(size,vector<float>(size));

    random_initialization(A);

    cout<<"\nMatrix A : \n"<<endl;
    print_matrix(A);

    clock_t startTime = clock();  // starting the clock time
    LU_Decomposition(A, L, U);
    clock_t endTime =  clock();   // ending the clock time
    
    cout<<"\nLower triangular matrix (L Matrix) : \n"<<endl;
    print_matrix(L);

    cout<<"\nUpper triangular matrix (U Matrix) : \n"<<endl;
    print_matrix(U);

    runtime = (double)(endTime-startTime)/(double)CLOCKS_PER_SEC;
    // cout <<"\nTime elapsed : "<<runtime<<" seconds\n"<<endl;
	return 0;
}