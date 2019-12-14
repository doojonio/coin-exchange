#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Coin {
    int value  = 0;
    int weight = 0;
};

int main() {
    ifstream input("input.file");
    //Get coins
    int num_coins;
    input >> num_coins;
    Coin* coins = new Coin[num_coins+1];
    coins[0] = Coin();

    for (int i = 1; i <= num_coins; i++) {
        int value, weight;
        input >> value >> weight;

        Coin new_coin = Coin{value = value, weight = weight};
        coins[i] = new_coin;
    }
    //Get sum
    int sum;
    input >> sum;

    //Create weights matrix
    int** w_matrix = new int*[sum+1];
    for (int i = 0; i<=sum; i++) {
        w_matrix[i] = new int[num_coins+1];
    }
    for (int s=0; s <=sum; s++) {
        w_matrix[s][0] = 0;
    }
    for (int c=0; c <=num_coins; c++) {
        w_matrix[0][c] = 0;
    }
    
    //filling matrix
    for (int s=1; s<=sum; s++){
        for(int c=1; c<=num_coins; c++){
            if(coins[c].value <= s) {
                if (w_matrix[s][c-1] != 0) {
                    w_matrix[s][c] = min(
                        w_matrix[s][c-1],
                        w_matrix[s-coins[c].value][c] + coins[c].weight
                    );
                }
                else {
                    w_matrix[s][c] = w_matrix[s-coins[c].value][c] + coins[c].weight;
                }
            }
            else {w_matrix[s][c] = w_matrix[s][c-1];}
        }
    }
    //print weights matrix
    for(int s=1; s<=sum; s++){
        cout << '[' << s << "] ";
        if (s < 10 ) {cout << ' ';}
        for(int c=1; c <=num_coins; c++) {
            if (w_matrix[s][c] < 10) {cout << ' ';}
            cout << w_matrix[s][c] << ' ';
        }
        cout << endl;
    }

    //find set of coins
    vector<Coin> set_coins;
    for (int s=sum; s >= 1;) {
        for(int c=num_coins; c>=1; c--) {
            if(w_matrix[s][c] == 0) {continue;}
            if(w_matrix[s][c] != w_matrix[s][c-1]){
                set_coins.push_back(coins[c]); 
                s -= coins[c].value;
                break;
            }
        }
    }
    //print set of coins
    int** quant_coins = new int*[num_coins];
    for ( int i = 0; i < num_coins; i++ ) {
        quant_coins[i] = new int[2];
        quant_coins[i][0] = coins[i+1].value;
        quant_coins[i][1] = 0;
    }

    int weight = 0;
    for(int i=0; i<set_coins.size(); i++) {
        for (int j = 0; j < num_coins; j++) {
            if(quant_coins[j][0] == set_coins[i].value) {quant_coins[j][1]++;}
        } 
        cout << "v=" << set_coins[i].value << ", w=" <<set_coins[i].weight << endl;
        weight += set_coins[i].weight;
    }
    
    cout << "quantity: " << set_coins.size() << endl;
    cout << "weigt: " << weight << endl;
    for (int i = 0; i < num_coins; i++) {
        cout << 'v' << quant_coins[i][0] << ": " << quant_coins[i][1] << endl;
    }

    return 0;
}

