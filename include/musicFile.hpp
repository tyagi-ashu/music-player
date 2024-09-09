#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
// call this at the start of main program then make playlist and shuffle out of that
// add a reload button to load new songs after you have added new songs in folder
using namespace std;
//using struct to reduce memory footprint 
//and there is no need for polymorphism or inheritance in this code
typedef struct musicFile{
    fstream myfile;
    string path = "../resources/music";

    void add_music_file(){
        myfile.open("../resources/records.csv",ios::out | ios::trunc);
        if(myfile.good()){
            for (const auto & i : filesystem::directory_iterator(path)){
                for(const auto & j:filesystem::directory_iterator(i.path())){
                    filesystem::path p(j.path());
                    if(p.extension()==".mp3"){
                        string song_name=p.stem().string();
                        string catagory=p.parent_path().stem().string();
                        myfile<<catagory<<","<<song_name<<endl;
                    }
                }
            }
            myfile.close();
        }
    }

    vector<pair<string,string>> read_music_files(){
        vector<pair<string,string>> vec;
        vec.clear();
        myfile.open("../resources/records.csv",ios::in);
        string line;
        if(myfile.good()){
            while(getline(myfile,line)){
                string cell;
                stringstream ss(line);
                vector<string> temp;
                while(getline(ss,cell,',')){
                    temp.push_back(cell);
                }
                vec.push_back(make_pair(temp[0],temp[1]));
            }
            myfile.close();
        }
        return vec;
    }
}musicFile;
/*
int main()
{
    musicFile mf;
    mf.add_music_file();
    vector<pair<string,string>> vec;
    vec=mf.read_music_files();
    for(auto i:vec){
        cout<<i.first<<"  "<<i.second<<endl;
    }
    return 0;
}
*/