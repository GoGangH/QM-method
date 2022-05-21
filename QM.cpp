#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <bitset>
using namespace std;
bool chk = true;
vector<pair<string, vector<int> > > find_PI( vector< pair<string, vector<int> > > PI){
    vector<pair<string, vector<int> > > result;
    vector<bool> chknum;
    for(int i=0;i<PI.size();i++) chknum.push_back(false);
    while(!PI.empty()){
        string s = PI.back().first;
        vector<int> minterm = PI.back().second;
        bool chkN = chknum.back();
        PI.pop_back();
        chknum.pop_back();

        for(int i=0;i<PI.size();i++){
            int cnt=0, tmp;
            for(int j=0;j<s.size();j++){
                if(cnt>1) break;
                if(s[j]!=PI[i].first[j]){
                    tmp=j;
                    cnt++;
                }
            }
            if(cnt==1){
                chknum[i]=true;
                chkN=true;
                string t = s;
                t[tmp]='2';
                vector<int> t_minterm;
                bool find=false;
                for(int j=0;j<result.size();j++){
                    if(t==result[j].first){
                        find=true;
                        break;
                    }
                }
                if(find==true) continue;

                for(int j=0;j<PI[i].second.size();j++) t_minterm.push_back(PI[i].second[j]);
                for(int j=0;j<minterm.size();j++) t_minterm.push_back(minterm[j]);
                result.push_back(make_pair(t, t_minterm));
                chk=true;
            }
        }
        if(chkN==false) result.push_back(make_pair(s, minterm));
    }
    return result;
}
vector<string> solution(vector<int> minterm) {
    vector<string> answer;
    vector<pair<string, vector<int> > > a;
    pair<string, vector<int> > tmp;
    for(int i=2;i<minterm.size();i++){
        bitset<100> bs(minterm[i]);
        string s = bs.to_string();
        s = s.substr(100-minterm[0], minterm[0]);
        vector<int> tmp;
        tmp.push_back(minterm[i]);
        a.push_back(make_pair(s, tmp));
    }
    while(chk==true){
        chk=false;
        vector<pair<string, vector<int> > > tmp = find_PI(a);
        if(chk) a = tmp;
    }
    int answer_size=0;
    int chk_minterm[1000000]={0,};
    string vet[a.size()];
    for(int i=0;i<a.size();i++){
        vet[answer_size++] = a[i].first;
        for(int j=0;j<a[i].second.size();j++){
            for(int k=2;k<minterm.size();k++){
                if(minterm[k]==a[i].second[j]){
                    chk_minterm[k]++;
                    break;
                }
            }
        }
    }

    vector<int> find_EPI;
    for(int i=2;i<minterm.size();i++){
        if(chk_minterm[i]==1) find_EPI.push_back(minterm[i]);
    }

    sort(vet, vet+answer_size);

    for(int i=0;i<answer_size;i++){
        string t="";
        for(int j=0;j<vet[i].size();j++){
            if(vet[i].at(j)=='2') t += '-';
            else t += vet[i].at(j);
        }
        answer.push_back(t);
    }

    answer.push_back("EPI");
    if(find_EPI.size()==0) return answer;

    int EPI_size = 0;
    string EPI_s[100000];

    while(!a.empty()){
        string ss = a.back().first;
        vector<int> tmp = a.back().second;
        a.pop_back();

        for(int i=0;i<tmp.size();i++){
            bool findchk=false;
            for(int j=0;j<find_EPI.size();j++){
                if(tmp[i]==find_EPI[j]){
                    EPI_s[EPI_size++] = ss;
                    findchk=true;
                    break;
                }
            }
            if(findchk==true) break;
        }
    }

    sort(EPI_s, EPI_s+EPI_size);

    for(int i=0;i<EPI_size;i++){
        string t="";
        for(int j=0;j<EPI_s[i].size();j++){
            if(EPI_s[i].at(j)=='2') t += '-';
            else t += EPI_s[i].at(j);
        }
        answer.push_back(t);
    }

    return answer;
}

int main(){
    vector<int> minterm;
    int arr[6]={3, 4, 0, 1, 2, 3};
    for(int i=0;i<6;i++){
        minterm.push_back(arr[i]);
    }

    solution(minterm);
    //["00-", "0-0", "11-", "1-1", "-01", "-10", "EPI"] result
}