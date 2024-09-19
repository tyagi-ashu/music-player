#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "musicFile.hpp"
#include "shuffle.hpp"
//head==>index=0

// doubly circular linked list
using namespace std;
class song{
    public:
    pair<string,string> p;
    song* next;
    song* prev;
    song(){}
    song(pair<string ,string> p){
        this->p=p;
        this->next=NULL;
        this->prev=NULL;
    }
    ~song() {
        next = NULL;
        delete next;
        prev = NULL;
        delete prev;
    }
};

class playlist: private song{
    private:
    //keeping trak of playlist curr playing song
    song* head;
    public:
    song* currsong;
    int count=0;
    float fontSize=24;
    vector<pair<string,string>> vec;

    playlist(): song(){
        cout<<"playlist  done"<<endl;
        this->head=NULL;
        currsong=head;
    }
    // index=-1 insert at end
    //index=0 insert at head
    void add_song(pair<string ,string> p,int insert_in_vec=1,int index=-1){
        song* new_song= new song(p);
        if(head==NULL){
            head=new_song;
            head->next=head;
            head->prev=head;
        }
        else{
            head->next->prev=new_song;
            new_song->next=head->next;
            head->next=new_song;
            new_song->prev=head;
            if(index==0){
                head=new_song;
            }
        }
        if(insert_in_vec && index==0){
            vec.insert(vec.begin(),p);
        }
        else if(insert_in_vec && index==-1){
            vec.push_back(p);
        } 
        currsong=head;
        count++;
    }
    //dont insert on start and end with this function(not used in this project--for future use)
    void add_song_mid(pair<string,string> p,int index){
        song* new_song = new song(p);
        song* temp = head;
        index--;
        temp=temp->prev;
        while(temp!=head && index>0){
            temp=temp->prev;
            index--;
        }
        // insert new_node between temp and next.
        temp->next->prev=new_song;
        new_song->next=temp->next;
        temp->next = new_song;
        new_song->prev = temp;
        currsong=head;
        count++;
    }
    // remove by index(only for internal use--in future)
    int remove_song(int index){
        if(index>=count || head==NULL){
            // invalid index
            return 0;
        }

        song* temp=head;
        //only 1 song
        if(count==1){
            head=NULL;
            temp->prev=NULL;
            temp->next=NULL;
            delete temp;
            --count;
            return 1;
        }
        int temp_index=index;
        //delete at any position
        do{
            if(temp_index==0) break;
            temp=temp->prev;
            --temp_index;
        }while(temp!=head && temp_index>=0);

        if(index==0)    //delete at first position
            head=temp->prev;
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        temp->prev=NULL;
        temp->next=NULL;
        delete temp;
        --count;
        currsong=head;
        return 1;
    }
    //remove by song_name
    int remove_song_name(string name){
        if(head==NULL){
            return 0;
        }

        song* temp=head;
        //only 1 song
        if(count==1){
            head=NULL;
            temp->prev=NULL;
            temp->next=NULL;
            delete temp;
            --count;
            vec.clear();
            return 1;
        }
        vector<pair<string,string>>::iterator it=vec.begin();
        do{
            if(temp->p.second==name) break;
            temp=temp->prev;
            it++;
        }while (temp!= head && it<=vec.end());

        if(it==vec.begin())    //delete at first position
            head=temp->prev;
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        temp->prev=NULL;
        temp->next=NULL;
        delete temp;
        --count;
        vec.erase(it);
        currsong=head;
        return 1;
    }

    string get_path(bool playNext){
        string path;
        if(playNext){
            path="../resources/music/"+currsong->p.first+"/"+currsong->p.second+".mp3";
            currsong=currsong->prev;
        }
        //playPrev=true
        else{
            path="../resources/music/"+currsong->next->next->p.first+"/"+currsong->next->next->p.second+".mp3";
            currsong=currsong->next;
        }
        
        return path;
    }
    //takes you to start of playlist after shuffle
    void make_shuffle(){
        //current playing song
        song* prevsong=currsong->next;
        shuffle shuf(vec);
        vec.clear();
        vec=shuf.output();
        for(int i=count;i>0;i--){
            if(!remove_song(0)) break;
        }
        for(auto i:vec){
            //0 for not inserting in vector
            add_song(i,0);
        }
        //is start of playlist and current playing song is the same
         if(prevsong->p==currsong->p){
            currsong=head->prev;
        }
        else{
            currsong=head;
        }
    }
};