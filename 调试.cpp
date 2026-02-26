#include <iostream>
using namespace std；
class IMotor{
    public:
    virtual void setoutput(int a)=0;
    virtual int getspeed()=0;
    virtual int update()=0;
    virtual ~IMotor(){}
}；
class djimotor:public IMotor{
    private:
    int speed;
    public:
    djiotor():speed(0){}
    void setoutput(int a){
        speed=a;
    }
    int getspeed(){
        return speed;
    }
    int update(){
        return speed*2;
    }
}；
