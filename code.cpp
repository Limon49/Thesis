#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define data_len 32
#define parity_len 6
#define H_marix_Len 22

typedef long long ll;
mt19937 R(chrono::system_clock().now().time_since_epoch().count());

int main()
{
    // define data 32 bit data
    //string data = "11111111111111111111111111111011";
    // define H matrix
    //vector<string> p = {"100000", "010000", "001000", "000100", "000010", "000001"};
    //vector<string> H = {"1111000110111000011110", "0001111101001110011011", "1001001011000001111010", "0010101010010101010010", "0000000000101010100101", "0101010101010101010101"};
    ll data[data_len];

    for(int i = 1; i <= data_len; i++){
        data[i-1] = (R())%2;
    }

    ll parity[parity_len][parity_len] =
        {
            {1, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 1}};
    ll H[parity_len][H_marix_Len] =
        {
            {1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0},
            {0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1},
            {1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0},
            {0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}};
    ll ip_parity = 0;
    // inter leave parity calculation p_ip

//x-or all 3's position value
    cout << "data : " << endl;
    for(int i = 0; i < data_len; i++){
        cout << data[i];
    }
    cout << endl;
    for (ll i = 1; i <= data_len; i++)
    {
        if (i % 3 == 0)
        {
            ip_parity ^= data[i-1];
        }
    }

    cout << "ip parity : " << ip_parity << endl;

    // SEC-DAEC  parity calculation

    ll data_comp[H_marix_Len];
    int pos = 0;
    for (int i = 1; i <= data_len; i++)
    {
        if (i % 3 == 0)
        {
            continue;
        }
        data_comp[pos++] = data[i-1];
    }

    /// store sec-daec
    ll Parity[parity_len];

    for (ll i = 0; i < parity_len; i++)
    {
        Parity[i] = 0;
        for (ll j = 0; j < H_marix_Len ; j++)
        {
            if (H[i][j] == 1)
            {
                Parity[i] ^= data_comp[j];
            }
        }
    }

    cout << "Sec_Dec Parity: ";
    for(int i=0; i<parity_len; i++){
        cout << Parity[i] ;
    }
    cout << endl;

    // flip data data ,actually error data
    // define data 32 bit data with error
    //string data_prime = "11111111111111111111111111111001";
    // flip last last bit
    ll data_prime[data_len];

    for(int i = 1; i <= data_len; i++){
        data_prime[i-1] = data[i-1];
    }

    //error injector
    int number_of_error;
    cout << "Enter number of errors: ";
    cin >> number_of_error;
    if(number_of_error == 1){
        cout << "Enter position of error: ";
        int pos;
        cin >> pos;
        pos = 32-pos;
        data_prime[pos] = (data_prime[pos] == 1? 0: 1);;
    }
    else if(number_of_error == 2){
        cout << "Enter positions of errors: ";
        int pos1, pos2;
        cin >> pos1 >> pos2;
        pos1 = 32-pos1;
        pos2 = 32-pos2;
        data_prime[pos1] = (data_prime[pos1] == 1? 0: 1);
        data_prime[pos2] = (data_prime[pos2] == 1? 0: 1);
    }


    cout << "data prime : " << endl;
    for(int i = 0; i < data_len; i++){
        cout << data_prime[i];
    }
    cout << endl;

    ll ip_syndrome = 0;
    for (ll i = 1; i <= data_len; i++)
    {
        if (i % 3 == 0)
        {
            ip_syndrome ^= data_prime[i-1];
        }
    }
    ip_syndrome = ip_syndrome ^ ip_parity;

    cout << "ip_syndrome: " << ip_syndrome << endl;

    // Calculate SEC-DAEC syndrome
    // remove multiple of 3 and store data_Compress array
    //string data_compress = "";
    ll data_compress[H_marix_Len];
    pos = 0;
    for (int i = 1; i <= data_len; i++)
    {
        if (i % 3 == 0)
        {
            continue;
        }
        data_compress[pos++] = data_prime[i-1];
    }
    string sec_dec_syndrom = "";
    //ll sec_dec_syndrom[parity_len];

    ll Parity_prime[parity_len];
    for (ll i = 0; i < parity_len; i++)
    {
        Parity_prime[i] = 0;
        for (ll j = 0; j < H_marix_Len ; j++)
        {
            if (H[i][j] == 1)
            {
                Parity_prime[i] ^= data_compress[j];
            }
        }
    }

    cout << "Sec_Dec Parity Prime: ";
    for(int i=0; i<parity_len; i++){
        cout << Parity_prime[i] ;
    }
    cout << endl;

    for (int i = 0; i < parity_len; i++)
    {

        ll sec_dec_parity = Parity_prime[i] ^ Parity[i];
        // cout<<"parity _Prime :"<<parity_prime<<endl;
        // cout<<"parity :"<<parity[i]<<endl;
        sec_dec_syndrom = sec_dec_syndrom + char(sec_dec_parity+'0');
    }

    cout << "SEC-DAEC syndrome: "  << sec_dec_syndrom << endl;

    // store the pattern of error
    map<string, vector<int> > SEC_DEC_Syndrom_Error_Bit;
    vector<string> Error_bit = {"000000", "010011", "111100", "100011", "111000", "111101", "001010", "001101", "010010", "010101", "110010", "100101", "000010", "011001", "101100", "110001", "011100", "010001", "010100", "111001", "100100", "100001", "101000", "101111", "011011", "110111", "011111", "100111", "000111", "110101", "101101", "000101", "011101", "001001"};
    vector<vector<int> > Error_position = {vector<int>(), {1}, {2}, {3}, {5}, {7}, {8}, {10}, {11}, {13}, {14}, {16}, {17}, {19}, {20}, {22}, {23}, {25}, {26}, {28}, {29}, {31}, {32}, {1,2}, {4, 5}, {7, 8}, {10, 11}, {13, 14}, {16, 17}, {19, 20}, {22, 23}, {25, 26}, {28, 29}, {31, 32}};

    for (int i = 0; i < Error_bit.size(); i++)
    {
        SEC_DEC_Syndrom_Error_Bit[Error_bit[i]] = Error_position[i];
    }
    //now find the error bit position
    ll data_correction[data_len];
    for(int i = 0; i < data_len; i++) data_correction[i] = data_prime[i];

    vector<int> error_pos = SEC_DEC_Syndrom_Error_Bit[sec_dec_syndrom];

    if(error_pos.size() == 0){
        cout << "No Error" << endl;
    }
    else if(error_pos.size() == 1){
        cout << "SE on position : " << error_pos[0] << endl;
        data_correction[32-error_pos[0]] = (data_correction[32-error_pos[0]] == 1? 0: 1);
        cout << "data after correcting error: " << endl;
        for(int i=0; i<data_len; i++){
            cout << data_correction[i];
        }
        cout << endl;

    }
    else if(error_pos.size() == 2){
        cout << "DAE on position : " << error_pos[0] << " and " << error_pos[1] << endl;
        data_correction[32-error_pos[0]] = (data_correction[32-error_pos[0]] == 1? 0: 1);
        data_correction[32-error_pos[1]] = (data_correction[32-error_pos[1]] == 1? 0: 1);
        cout << "data after correcting error: " << endl;
        for(int i=0; i<data_len; i++){
            cout << data_correction[i];
        }
        cout << endl;
    }

    return 0;
}






