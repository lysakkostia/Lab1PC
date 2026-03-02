#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;


double max_without_parallelism(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);

    vector<vector<int>> matrix(n, vector<int>(n));
    for ( int i = 0; i < n; ++i )
    {
        for ( int j = 0; j < n; ++j )
        {
            matrix[i][j] = dis(gen);
        }
    }
    auto start = chrono::high_resolution_clock::now();

    for ( int j = 0; j < n; ++j )
    {
        int maxIdx = 0;
        for ( int i = 1; i < n; ++i )
        {
            if ( matrix[i][j] > matrix[maxIdx][j] )
            {
                maxIdx = i;
            }
        }
        swap( matrix[j][j], matrix[maxIdx][j] );
    }

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>( end - start ).count();
}

int main() {

    vector<int> sizes = { 10, 100, 500, 1000, 2000, 5000, 10000, 20000 };

    cout << setfill( '-' ) << setw( 50 ) << "-" << endl;
    cout << setfill( ' ' ) << setw( 15 ) << "Розмір (NxN)"
         << setw( 30 ) << "Час (мкс)"
         << setw(20) << "Час (мс)" << endl;
    cout << setfill( '-' ) << setw( 50 ) << "-" << endl;
    cout << setfill( ' ' );

    for (int n : sizes)
    {
        double duration = max_without_parallelism(n);

        cout << setw( 15 ) << to_string(n) + "x" + to_string(n)
             << setw( 20 ) << duration
             << setw( 15 ) << fixed << setprecision( 2 ) << duration / 1000.0 << endl;
    }

    cout << setfill( '-' ) << setw( 50 ) << "-" << endl;

    return 0;
}