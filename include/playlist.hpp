#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "musicFile.hpp"
#include "shuffle.hpp"
//head==>index=0
//make_shuffle will feed to shuffle.hpp

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
    song* head;

    public:
    int count=0;
    float fontSize=24;
    vector<pair<string,string>> vec;

    playlist(): song(){
        cout<<"playlist  done"<<endl;
        this->head=NULL;
        //remove this mf part
        vec=musicFile::read_music_files();
        for(auto i:vec){
            add_song(i);
        }
    }
    // index=-1 insert at end
    //index=0 insert at head
    void add_song(pair<string ,string> p,int index=-1){
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
        count++;
    }
    //dont insert on start and end with this function
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

        count++;
    }
    // remove by index
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
        return 1;
    }
    int print(){
        if(head==NULL){
            cout<<"empty"<<endl;
            return 0;
        }
        song* temp = head;
        do{
            cout<<temp->p.second<<"  "<<temp->p.first<<endl;
            temp=temp->prev;
        }while (temp!= head);
        return 1;
    }
    // unfinished function...DO NOT CALL
    int get_song_name(int index){
        if(index>=count || head==NULL){
            cout<<"nooo"<<endl;
            return 0;
        }

        song* temp = head;
        do{
            if(index==0) break;
            temp=temp->prev;
            --index;
        }while(temp!=head && index>=0);
        cout<<temp->p.second<<endl;
        return 1;
    }
    void make_shuffle(){
        shuffle shuf(vec);
        vec.clear();
        vec=shuf.output();
        for(int i=count;i>0;i--){
            if(!remove_song(0)) break;
        }
        for(auto i:vec){
            add_song(i);
        }
    }
};
