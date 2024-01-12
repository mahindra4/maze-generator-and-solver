#include <bits/stdc++.h>
#include <chrono>
using namespace std;
pair<int,int> find(pair<int,int> x,vector<vector<pair<int,int>>> &v){
    //union find using path compression
    pair<int,int> p = x;
    while(v[p.first][p.second]!=p){
        p = v[p.first][p.second];
    }
    while(x!=p){
        pair<int,int> parent = v[x.first][x.second];
        v[x.first][x.second] = p;
        x = parent;
    }
    return x;
}
void Union(pair<int,int> a,pair<int,int> b,vector<vector<pair<int,int>>> &v){
    pair<int,int> p = find(a,v);
    v[p.first][p.second]=find(b,v);
}
namespace std {
    template <>
    struct hash<std::pair<std::pair<int, int>, std::pair<int, int>>> {
        size_t operator()(const std::pair<std::pair<int, int>, std::pair<int, int>>& p) const {
            size_t hash1 = std::hash<int>()(p.first.first);
            size_t hash2 = std::hash<int>()(p.first.second);
            size_t hash3 = std::hash<int>()(p.second.first);
            size_t hash4 = std::hash<int>()(p.second.second);
            return hash1 ^ (hash2 << 1) ^ (hash3 << 2) ^ (hash4 << 3);
        }
    };
}
int dfs_count=0,bfs_count=0,a_count=0;
int dfs_duration=0,bfs_duration=0,a_duration=0,maze_creation_duration=0;
unordered_set<pair<pair<int,int>,pair<int,int>>> dfs_path(unordered_set<pair<pair<int,int>,pair<int,int>>> maze,int n){
    vector<vector<bool>> visited(n,vector<bool>(n,false));
    vector<vector<pair<int,int>>> parent(n,vector<pair<int,int>>(n,{-1,-1}));
    vector<pair<int,int>> st;
    st.push_back({0,0});
    visited[0][0]=true;
    while(!st.empty()){
        pair<int,int> p = st.back();
        st.pop_back();
        int i = p.first,j = p.second;
        // cout<<i<<" "<<j<<endl;
        visited[i][j]=true;
        dfs_count++;
        if(p==make_pair(n-1,n-1)) break;
        if(i<n-1 && maze.find({{i+1,j},{i+1,j+1}})==maze.end() && !visited[i+1][j]){
            st.push_back({i+1,j});
            parent[i+1][j]={i,j};
        }
        if(i>0 && maze.find({{i,j},{i,j+1}})==maze.end() && !visited[i-1][j]){
            st.push_back({i-1,j});
            parent[i-1][j]={i,j};
        }
        if(j<n-1 && maze.find({{i,j+1},{i+1,j+1}})==maze.end() && !visited[i][j+1]){
            st.push_back({i,j+1});
            parent[i][j+1]={i,j};
        }
        if(j>0 && maze.find({{i,j},{i+1,j}})==maze.end() && !visited[i][j-1]){
            st.push_back({i,j-1});
            parent[i][j-1]={i,j};
        }
    }
    pair<int,int> end = {n-1,n-1};
    unordered_set<pair<pair<int,int>,pair<int,int>>> path;
    while(parent[end.first][end.second]!=make_pair(-1,-1)){
        pair<int,int> a = parent[end.first][end.second];
        if(end.first==a.first+1||end.second==a.second+1){
            path.insert({a,end});
        }
        else{
            path.insert({end,a});
        }
        end = a;
    }
    return path;
}
// struct change{
//     int n;
//     change(int n): n(n) {}
//     bool operator()(pair<int,int> a,pair<int,int> b){
//         int costa = sqrt((n-1-a.first)*(n-1-a.first)+(n-1-a.second)*(n-1-a.second));
//         int costb = sqrt((n-1-b.first)*(n-1-b.first)+(n-1-b.second)*(n-1-b.second));
//         if(costa<costb){
//             return b<a;
//         }
//         else{
//             return a<b;
//         }
//     }
// };
struct change{
    int n;
    change(int n): n(n) {}
    bool operator()(pair<int,int> a,pair<int,int> b){
        int costa = 2*(n-1)-(a.first+a.second);
        int costb = 2*(n-1)-(b.first+b.second);
        if(costa<costb){
            return b<a;
        }
        else{
            return a<b;
        }
    }
};
unordered_set<pair<pair<int,int>,pair<int,int>>> a_path(unordered_set<pair<pair<int,int>,pair<int,int>>> maze,int n){
    vector<vector<bool>> visited(n,vector<bool>(n,false));
    vector<vector<pair<int,int>>> parent(n,vector<pair<int,int>>(n,{-1,-1}));
    change customComparator(n);
    priority_queue<pair<int,int>,vector<pair<int,int>>, change> st(customComparator);
    st.push({0,0});
    visited[0][0]=true;
    while(!st.empty()){
        pair<int,int> p = st.top();
        st.pop();
        int i = p.first,j = p.second;
        // cout<<i<<" "<<j<<endl;
        visited[i][j]=true;
        if(p==make_pair(n-1,n-1)) break;
        a_count++;
        if(i<n-1 && maze.find({{i+1,j},{i+1,j+1}})==maze.end() && !visited[i+1][j]){
            st.push({i+1,j});
            parent[i+1][j]={i,j};
        }
        if(i>0 && maze.find({{i,j},{i,j+1}})==maze.end() && !visited[i-1][j]){
            st.push({i-1,j});
            parent[i-1][j]={i,j};
        }
        if(j<n-1 && maze.find({{i,j+1},{i+1,j+1}})==maze.end() && !visited[i][j+1]){
            st.push({i,j+1});
            parent[i][j+1]={i,j};
        }
        if(j>0 && maze.find({{i,j},{i+1,j}})==maze.end() && !visited[i][j-1]){
            st.push({i,j-1});
            parent[i][j-1]={i,j};
        }
    }
    pair<int,int> end = {n-1,n-1};
    unordered_set<pair<pair<int,int>,pair<int,int>>> path;
    while(parent[end.first][end.second]!=make_pair(-1,-1)){
        pair<int,int> a = parent[end.first][end.second];
        if(end.first==a.first+1||end.second==a.second+1){
            path.insert({a,end});
        }
        else{
            path.insert({end,a});
        }
        end = a;
    }
    return path;
}
unordered_set<pair<pair<int,int>,pair<int,int>>> bfs_path(unordered_set<pair<pair<int,int>,pair<int,int>>> maze,int n){
    vector<vector<bool>> visited(n,vector<bool>(n,false));
    vector<vector<pair<int,int>>> parent(n,vector<pair<int,int>>(n,{-1,-1}));
    queue<pair<int,int>> q;
    q.push({0,0});
    visited[0][0]=true;
    while(!q.empty()){
        pair<int,int> p = q.front();
        q.pop();
        int i = p.first,j = p.second;
        // cout<<i<<" "<<j<<endl;
        visited[i][j] = true;
        bfs_count++;
        if(p==make_pair(n-1,n-1)) break;
        if(i<n-1 && maze.find({{i+1,j},{i+1,j+1}})==maze.end() && !visited[i+1][j]){
            q.push({i+1,j});
            parent[i+1][j]={i,j};
        }
        if(i>0 && maze.find({{i,j},{i,j+1}})==maze.end() && !visited[i-1][j]){
            q.push({i-1,j});
            parent[i-1][j]={i,j};
        }
        if(j<n-1 && maze.find({{i,j+1},{i+1,j+1}})==maze.end() && !visited[i][j+1]){
            q.push({i,j+1});
            parent[i][j+1]={i,j};
        }
        if(j>0 && maze.find({{i,j},{i+1,j}})==maze.end() && !visited[i][j-1]){
            q.push({i,j-1});
            parent[i][j-1]={i,j};
        }
    }
    pair<int,int> end = {n-1,n-1};
    unordered_set<pair<pair<int,int>,pair<int,int>>> path;
    while(parent[end.first][end.second]!=make_pair(-1,-1)){
        pair<int,int> a = parent[end.first][end.second];
        if(a.first==end.first+1 || a.second==end.second+1){
            path.insert({end,a});
        }
        else{
            path.insert({a,end});
        }
        end = a;
    }
    return path;
}
void display_maze(unordered_set<pair<pair<int,int>,pair<int,int>>> maze,int n){
    for(int i=0;i<=n;i++){
        for(int j=0;j<n;j++){
            cout<<"* ";
            if(maze.find({{i,j},{i,j+1}})!=maze.end()){
                cout<<"* ";
            }
            else{
                cout<<"  ";
            }
        }
        cout<<"*"<<endl;
        for(int j=0;j<=n;j++){
            if(maze.find({{i,j},{i+1,j}})!=maze.end()){
                cout<<"*   ";
            }
            else{
                cout<<"    ";
            }
        }
        cout<<endl;
    }
}
void display(unordered_set<pair<pair<int,int>,pair<int,int>>> maze,unordered_set<pair<pair<int,int>,pair<int,int>>> s,int n){
    for(int i=0;i<=n;i++){
        for(int j=0;j<n;j++){
            cout<<"* ";
            if(maze.find({{i,j},{i,j+1}})!=maze.end()){
                cout<<"* ";
            }
            else if(s.find({{i-1,j},{i,j}})!=s.end()){
                cout<<"@ ";
            }
            else{
                cout<<"  ";
            }
        }
        cout<<"*"<<endl;
        for(int j=0;j<=n;j++){
            if(maze.find({{i,j},{i+1,j}})!=maze.end()){
                cout<<"* ";
            }
            else if(s.find({{i,j-1},{i,j}})!=s.end()){
                cout<<"@ ";
            }
            else{
                cout<<"  ";
            }
            if(i==n-1 && j==n-1){
                cout<<"@ ";
            }
            else if(s.find({{i,j},{i,j+1}})!=s.end()){
                cout<<"@ "; 
            }
            else if(s.find({{i,j},{i+1,j}})!=s.end()||s.find({{i-1,j},{i,j}})!=s.end()){
                cout<<"@ ";
            }
            else{
                cout<<"  ";
            }
        }
        cout<<endl;
    }
}
int main(){
    int n;
    cout<<"Enter the dimension of the maze(nxn): ";
    cin>>n;
    vector<vector<int>> v(n,vector<int>(n));
    vector<pair<pair<int,int>,pair<int,int>>> edges;
    set<pair<int,int>> visited;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i<n-1 && visited.find({i,j})==visited.end()){
                edges.push_back({{i,j},{i+1,j}});
            }
            if(j<n-1 && visited.find({i,j})==visited.end()){
                edges.push_back({{i,j},{i,j+1}});
            }
            visited.insert({i,j});
        }
    }
    auto start = chrono::high_resolution_clock::now();
    random_device rd;
    mt19937 g(rd());
    shuffle(edges.begin(),edges.end(),g);

    vector<vector<pair<int,int>>> parent(n,vector<pair<int,int>>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
           parent[i][j] = {i,j};
        }
    }
    unordered_set<pair<pair<int,int>,pair<int,int>>> path;
    for(int i=0;i<edges.size();i++){
        pair<int,int> a=edges[i].first,b=edges[i].second;
        if(find(a,parent)!=find(b,parent)){
            Union(a,b,parent);
            path.insert({a,b});
        }
    }
    unordered_set<pair<pair<int,int>,pair<int,int>>> maze;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(i<n && (path.find({{i,j-1},{i,j}})==path.end()|| j==0 || j==n)){
                maze.insert({{i,j},{i+1,j}});
            }
            if(j<n && (path.find({{i-1,j},{i,j}})==path.end()|| i==0 || i==n)){
                maze.insert({{i,j},{i,j+1}});
            }
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    maze_creation_duration = duration.count();
    
    cout<<"\n\nrandomly generated maze: \n\n";
    display_maze(maze,n);

    cout<<"\n\n\ndfs path for the maze:\n\n";
    start = chrono::high_resolution_clock::now();
    unordered_set<pair<pair<int,int>,pair<int,int>>> dfs_ans = dfs_path(maze,n);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    dfs_duration = duration.count();
    display(maze,dfs_ans,n);

    cout<<"\n\n\nbfs path for the maze:\n\n";
    start = chrono::high_resolution_clock::now();
    unordered_set<pair<pair<int,int>,pair<int,int>>> bfs_ans = bfs_path(maze,n);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    bfs_duration = duration.count();
    display(maze,bfs_ans,n);

    cout<<"\n\n\na* path for the maze:\n\n";
    start = chrono::high_resolution_clock::now();
    unordered_set<pair<pair<int,int>,pair<int,int>>> a_ans = a_path(maze,n);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop-start);
    a_duration = duration.count();
    display(maze,bfs_ans,n);

    cout<<endl<<endl;
    cout<<"The steps taken for completion of dfs_path: "<<dfs_count<<endl;
    cout<<"The steps taken for completion of bfs_path: "<<bfs_count<<endl;
    cout<<"The steps taken for completion of a*_path: "<<a_count<<endl<<endl;

    cout<<"The order of the number of steps taken: ";
    if(dfs_count<bfs_count && dfs_count<a_count){
        cout<<"dfs < ";
        if(bfs_count<a_count){
            cout<<"bfs < a*";
        }
        else{
            cout<<"a* < bfs";
        }
    }
    if(bfs_count<dfs_count && bfs_count<a_count){
        cout<<"bfs < ";
        if(dfs_count<a_count){
            cout<<"dfs < a*";
        }
        else{
            cout<<"a* < dfs";
        }
    }
    if(a_count<bfs_count && a_count<dfs_count){
        cout<<"a* < ";
        if(bfs_count<dfs_count){
            cout<<"bfs < dfs";
        }
        else{
            cout<<"dfs < bfs";
        }
    }
    cout<<endl;

    cout<<endl<<endl;
    cout<<"The time taken for creation of the maze: "<<maze_creation_duration<<endl;
    cout<<"The time taken for completion of dfs_path: "<<dfs_duration<<endl;
    cout<<"The time taken for completion of bfs_path: "<<bfs_duration<<endl;
    cout<<"The time taken for completion of a*_path: "<<a_duration<<endl<<endl;

    cout<<"The order of the number of time taken: ";
    if(dfs_duration<bfs_duration && dfs_duration<a_duration){
        cout<<"dfs < ";
        if(bfs_duration<a_duration){
            cout<<"bfs < a*";
        }
        else{
            cout<<"a* < bfs";
        }
    }
    if(bfs_duration<dfs_duration && bfs_duration<a_duration){
        cout<<"bfs < ";
        if(dfs_duration<a_duration){
            cout<<"dfs < a*";
        }
        else{
            cout<<"a* < dfs";
        }
    }
    if(a_duration<bfs_duration && a_duration<dfs_duration){
        cout<<"a* < ";
        if(bfs_duration<dfs_duration){
            cout<<"bfs < dfs";
        }
        else{
            cout<<"dfs < bfs";
        }
    }
    cout<<endl;
    return 0;
}