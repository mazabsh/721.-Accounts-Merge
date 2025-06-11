#include<iostream> 
#include<unordered_map> 
#include<unordered_set> 
#include<vector> 
#include<algorithm> 

using namespace std; 

class Solution{
public: 
      unordered_map<string, vector<string>> graph; 
      unordered_map<string, string> emailToName; 
      unordered_set<string> visited; 
      void dfs(string email, vector<string>& components){
        visited.insert(email); 
        components.push_back(email); 
        for(string& neighbor : graph[email]){
          if (!visited.count(neighbor)) dfs(neighbor , components);
          
        }
        
      }
      vector<vector<string>> accountsMerge(vector<vector<string>>& accounts){
        vector<vector<string>> out; 

        for(auto account: accounts){
          string name = account[0]; 
          int n = account.size(); 
          for(int i=1; i<n ; ++i){
            string email = account[i]; 
            emailToName[email] = name; 
            if(i>1){
              graph[account[i]].push_back(account[i-1]); 
              graph[account[i-1]].push_back(account[i]); 
            }
            
          }
        }
        for(auto [email, _] : emailToName){
           
          if(!visited.count(email)){
            vector<string> components;
            dfs(email, components); 
            sort(components.begin(), components.end()); 
            components.insert(components.begin(), emailToName[email]); 
            out.push_back(components);
          } 
        }
        return out; 
        
      }
};
int main() {
    // Write C++ code here
    vector<vector<string>> accounts = {{"John","johnsmith@mail.com","john_newyork@mail.com"},{"John","johnsmith@mail.com","john00@mail.com"},{"Mary","mary@mail.com"}  ,{"John","johnnybravo@mail.com"}};
    Solution sol; 
    vector<vector<string>> res = sol.accountsMerge(accounts); 
    for(auto vec: res){
        cout << "[ " ; 
        for(string s: vec){
            cout << s << " , " ; 
        }
        cout << " ] " << endl; 
    }
    
    return 0;
}
