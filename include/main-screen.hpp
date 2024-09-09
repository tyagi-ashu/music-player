#pragma once

class mainScreen{
    public:
    virtual ~mainScreen(){};    // to delete instance of derived class class from pointer of base class
    virtual void render(){};
    private:

};