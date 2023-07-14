#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Map
{
    int K;
    int L;
    vector<vector<int>> table;

    public:

    Map() : K(1), L(1), table(K, std::vector<int>(L, 0))
    {
    }

    Map(int K, int L) : K(K), L(L), table(K, std::vector<int>(L, 0)) {
        if(K <= 0 || L <= 0 || K >= 10000 || L >= 10000 || L < K)
        {
            throw invalid_argument("Invalid parameters, this is the criteria: 0 < rows <= columns < 10000");
        }
    }

    void addBadOrrange(int x, int y, int R)
    {
        if(x <= 0 || y <= 0 || x >= K + 1 || y >= L + 1)
        {
            throw invalid_argument("Invalid parameters, coordinates should be unsigned and in the table");
        }
        table[x-1][y-1] = R + 1;
    }

    int calculateGoodOrrangesByDay(int R)
    {
        R++;

        int count = 0;

        while(R > 0)
        {
            for (int i = 0; i < K; i++) 
            {
                for (int j = 0; j < L; j++) 
                {
                    if(table[i][j] == R)
                    {
                        if(i != 0)
                        {
                            if(table[i-1][j] == 0)
                            {
                                table[i-1][j] = R - 1;
                            }
                        }
                        if(j != 0)
                        {
                            if(table[i][j-1] == 0)
                            {
                                table[i][j-1] = R - 1;
                            }
                        }
                        if(i != K - 1)
                        {
                            if(table[i+1][j] == 0)
                            {
                                table[i+1][j] = R - 1;
                            }
                        }
                        if(j != L - 1)
                        {
                            if(table[i][j+1] == 0)
                            {
                                table[i][j+1] = R - 1;
                            }
                        }
                        count++;
                    }
                }
            }  
            R--;
        }

        return K*L - count;
    }
};

int main()
{
    int K;
    int L;
    int R;

    cin >> K;
    cin >> L;
    cin >> R;

    Map map = Map(K, L);

    int x;
    int y;
    int x1;
    int y1;

    int count;

    cout<< "How much oranges are rotten?:" << endl;
    cin>> count;

    if(count == 1)
    {
        cin >> x;
        cin >> y;
        map.addBadOrrange(x, y, R);
    }else if(count == 2)
    {
        cin >> x;
        cin >> y;
        cin >> x1;
        cin >> y1;

        map.addBadOrrange(x, y, R);

        map.addBadOrrange(x1, y1, R);
    }else
    {
        cout<< "Wrong input provided"<< endl;
    }
    
    cout<< map.calculateGoodOrrangesByDay(R);

    return 0;
}