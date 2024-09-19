#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <time.h>
#include <cstdlib>    //rand
#include <cmath>     //round
//code is messy because i didnt clean up after main() function to struct conversion

using namespace std;

//https://keyj.emphy.de/balanced-shuffle/

typedef struct shuffle{
    //.first= artist  .second= song_name
    vector<pair<string,string>> songs;
    //mapping of each artist to their song list
    unordered_map<string,vector<string>> map;
    //mapping of each song name to artist name     made for searching in 0(1) time instead of O(n) in vector
    unordered_map<string,string> map2;
    int artist_count;
    int total_songs;
    shuffle(vector<pair<string,string>> vec){
        songs=vec;
        for(size_t i=0;i<songs.size();i++){
            map[songs[i].first].push_back(songs[i].second);
        }
        artist_count=map.size();
        for(size_t i=0;i<songs.size();i++){
            map2[songs[i].second]=songs[i].first;
        }
        total_songs=songs.size();
    };

    //for shuffling songs of same artists -- (fisher yates shuffle algo used)
    void randomize1 (vector<string> &vec){ 
        srand (time(NULL)); 
        for (int i = vec.size()-1; i > 0; i--) 
        { 
            int j = rand() % (i + 1); 
            string temp=vec[i];
            vec[i]=vec[j];
            vec[j]=temp;
        } 
    }
    void randomize2 (vector<pair<string,string>> &vec){ 
        srand (time(NULL)); 
        for (int i = vec.size()-1; i > 0; i--) 
        { 
            int j = rand() % (i + 1); 
            pair<string,string> temp=vec[i];
            vec[i]=vec[j];
            vec[j]=temp;
        } 
    }

    vector<pair<string,string>> output(){
        if(!songs.size()){
            return {};
        }
        int max_n=0;   //max number of songs with an artist
        for(auto i:map){
            int n=i.second.size();
            if(max_n<n) max_n=n;
        }
        //vector of all songs
        vector<vector<string>> group(artist_count);
        //just to get a vector to not waste space
        int group_index=0;
                
        for(auto i:map){
            group[group_index++]=i.second;
        }

        //randomizing 
        group_index=0;
        for(auto i:group){
            randomize1(i);
            int flag=1;
            if(i.size()<max_n-i.size()) flag=0;
            if(min(i.size(),max_n-i.size())==0)    //for no blanks
                group[group_index++]=i;
            int n=max_n;
            size_t i_index=0;
            vector<string> temp_i;
            for(int k=min(i.size(),max_n-i.size());k>0;k--){
                float r=n/k;

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
            }
            //add random offset now
            if(temp_i.size()){
                int random_index=0+(rand() % max_n);
                string temp_s=temp_i[0];
                temp_i[0]=temp_i[random_index];
                temp_i[random_index]=temp_s;
                group[group_index++]=temp_i;
            }
            temp_i.clear();
        }

        vector<pair<string,string>> shuff_songs(total_songs);
        int index=0;   //for shuff_songs;
        for(int i=0;i<max_n;i++){
            vector<pair<string,string>> temp;
            for(int j=0;j<group_index;j++){
                if(group[j][i]!="0")
                    temp.push_back(make_pair(map2[group[j][i]],group[j][i]));   //artist, song
            }
            randomize2(temp);
            
            //swapping first and last element if 2 consecutive songs of same artist came
            if(index!=0 && map2[temp[0].second]==map2[shuff_songs[index-1].second]){
                pair<string,string> p_temp=temp[0];
                temp[0]=temp[temp.size()-1];
                temp[temp.size()-1]=p_temp;
            }
            for(size_t k=0;k<temp.size();k++){
                shuff_songs[index++]=temp[k];
            }
            temp.clear();
        }
        return shuff_songs;
    }
}shuffle;
