#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <time.h>
#include <cstdlib>    //rand
#include <cmath>     //round

using namespace std;

//https://keyj.emphy.de/balanced-shuffle/

//make this int main into a class or struct


void make_vector(vector<pair<string,string>> &songs){
    songs.push_back(make_pair("A","song1"));
    songs.push_back(make_pair("B","song2"));
    songs.push_back(make_pair("C","song3"));
    songs.push_back(make_pair("D","song4"));
    songs.push_back(make_pair("E","song5"));
    songs.push_back(make_pair("A","song6"));
    songs.push_back(make_pair("A","song7"));
    songs.push_back(make_pair("A","song8"));
    songs.push_back(make_pair("B","song9"));
    songs.push_back(make_pair("B","song10"));
    songs.push_back(make_pair("B","song11"));
    songs.push_back(make_pair("B","song12"));
    songs.push_back(make_pair("D","song13"));
    songs.push_back(make_pair("F","song14"));
    songs.push_back(make_pair("E","song15"));
    songs.push_back(make_pair("F","song16"));
    songs.push_back(make_pair("D","song17"));
    songs.push_back(make_pair("G","song18"));
    songs.push_back(make_pair("G","song19"));
    songs.push_back(make_pair("G","song20"));
}
//mapping of each artist to theri song list
void artist_mapping(unordered_map<string,vector<string>> &map,vector<pair<string,string>> songs){
    for(int i=0;i<songs.size();i++){
        map[songs[i].first].push_back(songs[i].second);
    }
}
//mapping of each song name to artist name
void artist_mapping2(unordered_map<string,string> &map,vector<pair<string,string>> songs){
    for(int i=0;i<songs.size();i++){
        map[songs[i].second]=songs[i].first;
    }
    //print_map(map);
}
//for shuffling songs of same artists -- (fisher yates shuffle algo used)
void randomize (vector<string> &vec){ 
    srand (time(NULL)); 
    for (int i = vec.size()-1; i > 0; i--) 
    { 
        int j = rand() % (i + 1); 
        string temp=vec[i];
        vec[i]=vec[j];
        vec[j]=temp;
    } 
}

int main(){
    //.first= artist  .second= song_name
    vector<pair<string,string>> songs;
    make_vector(songs);
    //.first=artist   .second=list of songs
    unordered_map<string,vector<string>> map;
    unordered_map<string,string> map2;
    artist_mapping(map,songs);
    artist_mapping2(map2,songs);

    int artist_count=map.size();
    int total_songs=songs.size();

    int max_n=0;   //max number of songs with an artist
    for(auto i:map){
        int n=i.second.size();
        if(max_n<n) max_n=n;
    }

    vector<vector<string>> group(artist_count);
    //just to get a vector to not waste space
    int group_index=0;
    for(auto i:map){
        group[group_index++]=i.second;
    }
    //randomizing 
    group_index=0;
    for(auto i:group){
        randomize(i);
        int flag=1;
        if(i.size()<max_n-i.size()) flag=0;
        int k=min(i.size(),max_n-i.size());
        if(k==0)    //for no blanks
            group[group_index++]=i;
        int n=max_n;
        int i_index=0;
        vector<string> temp_i;
        for(k;k>0;k--){
            float r=n/k;
            //bringing -10% deviation in r
            r=round(r-(10.0*r/100));
            if(r>n-k+1) r=n-k+1;

            if(flag==0){
                if(i.size()>i_index)
                    temp_i.push_back(i[i_index++]);
                for(int j=0;j<r-1;j++){
                    temp_i.push_back("0");
                }
            }
            else{
                temp_i.push_back("0");
                for(int j=0;j<r-1;j++){
                    if(i.size()>i_index)
                        temp_i.push_back(i[i_index++]);
                    else 
                        temp_i.push_back("0");
                }
            }
            n=n-r;

            //add random offset now
        }
        if(temp_i.size()){
            int random_index=0+(rand() % max_n);
            string temp_s=temp_i[0];
            temp_i[0]=temp_i[random_index];
            temp_i[random_index]=temp_s;
            group[group_index++]=temp_i;
        }
        temp_i.clear();
    }

    vector<string> shuff_songs(total_songs);
    int index=0;   //for shuff_songs;
    for(int i=0;i<max_n;i++){
        vector<string> temp;
        for(int j=0;j<group_index;j++){
            if(group[j][i]!="0")
                temp.push_back(group[j][i]);
        }
        randomize(temp);
        
        //swapping first and last element if 2 consecutive songs of same artist came
        if(index!=0 && map2[temp[0]]==map2[shuff_songs[index-1]]){
            string s_temp=temp[0];
            temp[0]=temp[temp.size()-1];
            temp[temp.size()-1]=s_temp;
        }
        for(int k=0;k<temp.size();k++){
            shuff_songs[index++]=temp[k];
        }
        temp.clear();
    }
    for(string i:shuff_songs)
        cout<<i<<" ";
    return 0;
}