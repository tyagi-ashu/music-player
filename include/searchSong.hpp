#pragma once

#include <string>
using namespace std;

class TrieNode {
    public:
    TrieNode* child[95];
    bool wordEnd;
    //charector , artist
    pair<char,string> songs;
    TrieNode(){};
    TrieNode(char w,string s)
    {
        this->songs.first=w;
        this->songs.second=s;
        wordEnd = false;
        for (int i = 0; i < 95; i++) {
            child[i] = NULL;
        }
    }
};
class trie:private TrieNode{
    public:
    TrieNode* root;
    trie():TrieNode(){
        root=new TrieNode('\0',"");
    }
    void insertKey(TrieNode* root, string word,string artist) {
        if(word.length()==0){
            root->wordEnd=true;
            return ;
        }
        int index=word[0]-' ';
        TrieNode* temp;
        if(root->child[index]!=NULL){
            temp=root->child[index];
        }
        else{
            temp=new TrieNode(word[0],artist);
            root->child[index]=temp;
        }
        insertKey(temp,word.substr(1),artist);
    }
    pair<bool,string> searchKey(TrieNode* root,string word,string artist=""){
        if(word.length()==0){
            if(root->wordEnd){
                artist=root->songs.second;
            }
            return make_pair(root->wordEnd,artist);
        }
        int index=word[0]-' ';
        TrieNode* temp;
        if(root->child[index]!=NULL){
            temp=root->child[index];
        }
        else{
            return make_pair(false,"");
        }
        return searchKey(temp,word.substr(1),artist);

    }
    void insertSong(string word,string artist){
        insertKey(root, word,artist);
    }
    pair<bool,string> searchSong(string word){
        return searchKey(root, word);
    }
};
