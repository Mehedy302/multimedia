#include<bits/stdc++.h>
using namespace std;


struct node{

    int left, right, id;
    int cost;
    char ch;

    node(){}
    node(int _id, int _left, int _right, int _cost, char _ch){
        id = _id;
        left = _left;
        right = _right;
        cost = _cost;
        ch = _ch;
    }

    bool operator < (const node&x)const{
        return  cost>x.cost;
    }
} nlist[1000000];

int id = 0;

vector<int>code[150],vc;


void dfs(int id){

    if(nlist[id].left==-1){
        code[(int)nlist[id].ch].assign(vc.begin(), vc.end());
        return;
    }

    vc.push_back(0);
    dfs(nlist[id].left);
    vc.pop_back();

    vc.push_back(1);
    dfs(nlist[id].right);
    vc.pop_back();
}


string huffman_coding(string str){

    int freq[150];
    int root;
    int distinct_char=0;
    string code_map = "";
    string out = "";
    priority_queue<node>pq;
    map<char, string>mp;

    ofstream enc_out;
    enc_out.open("huffman_enc.txt");

    id = 0;

    memset(freq, 0, sizeof freq);

    // count frequency and push on priority queue
    for(int i = 0; i < str.size(); i++){
        freq[(int)str[i]]++;
    }

    for(int i = 0; i < 130; i++){
        if(freq[i]){
            distinct_char++;
            nlist[id] = node(id, -1, -1, freq[i], (char)i);
            pq.push(nlist[id]);
            id++;
        }
    }

    // creating the tree;
    node lt, rt;
    while(pq.size() > 1){
        lt = pq.top();
        pq.pop();
        rt = pq.top();
        pq.pop();
        nlist[id] = node(id, lt.id, rt.id, lt.cost + rt.cost, '0');
        pq.push(nlist[id]);

        id++;
    }

    root = id++;
    nlist[root] = pq.top();
    pq.pop();

    //cout<<nlist[nlist[root].left].ch<<endl;

    // generating code form the tree

    dfs(root);

    enc_out<<distinct_char<<endl;

    for(int i = 0; i < 130; i++){
        if(code[i].size()){
            cout<<(char)i<<" : ";
            enc_out<<i<<" ";
            code_map = "";
            for(int j = 0; j < code[i].size(); j++){
                cout<<code[i][j];
                code_map += (char)(code[i][j]+'0');
            }
            mp[(char)i] = code_map;
            enc_out<<code_map<<endl;
            cout<<endl;
        }
    }

    /// Encoding with the huffman code:

    for(int i = 0; i < str.size(); i++){
        out += mp[str[i]];
    }

    cout<<"Text : "<<str<<endl;
    cout<<"Encoded : ";
    cout<<out<<endl;
    enc_out<<out<<endl;
    return out;
}

string huffman_decoding(){

    int i, j, k, n;
    int ch;

    string str,tmp,decd = "";
    map<string, int>mp;

    ifstream enc_in;
    enc_in.open("huffman_enc.txt");

    enc_in>>n;
    for(i = 0; i < n; i++){
        enc_in>>ch>>str;
        mp[str] = ch;
    }
    enc_in>>str;
    //cout<<str<<endl;
    tmp = "";
    for(i = 0; i < str.size(); i++){
        tmp += str[i];
        if(mp[tmp]){

            decd += (char)mp[tmp];
            tmp = "";
        }
    }
    cout<<"Decoded : ";
    cout<<decd<<endl;

    return decd;
}

int main(){

    int i,j,n,m,a,b;
    string str, enc, decd;
    ifstream input;
    input.open("huffman_input.txt");


    input>>str;

    enc = huffman_coding(str);
    decd = huffman_decoding();



    return 0;
}
