#include<iostream>
#include<string>
#include <string.h>
#include <fstream>


class Abstract{
    protected:
    std::string str_;
    public:
        virtual void dataGenerate(const std::string Data)=0;
        virtual void cGenerate()=0;
        virtual void stringGenerate()=0;
        virtual void sGenerate(const std::string S)=0;

        void generate(const std::string S, const std::string Data){
            stringGenerate();
            sGenerate(S);
            dataGenerate(Data);
            cGenerate();
        }
        std::string getStr(){ return str_;};
        
};


class Miem: public Abstract{
    public:
    void stringGenerate(){
        str_="111111111111111";
    }
    void cGenerate(){
        int summ = 0;
        int number = 0;
        for(int i=0;i<15;++i)
            summ = summ + ((int)str_[i]) * (i+1);
        while((summ + number * 14) % 11 ){
            number = number + 1;
            if(number > 9) //на случай бесконечного вызова 
            {
                summ = summ - str_[13]*14;
                str_[13] = (char)(abs((int)str_[13]-1) % 10) + 48;
                number = 0;
            }
        }
        str_[14] = (char)(number % 10 +48);
    };
    void dataGenerate(const std::string Data){
            for(int i=1;i<9;i++){
                str_[i] = Data[i - 1];
            }
            for(int i = 9;i<14;++i)
                str_[i] = (char)((int)Data[i - 9] * 9 %10 +48);
    };
    void sGenerate(const std::string S){
        if (S=="men")
            str_[0] = '8';
        else    
            str_[0] = '4';
    }
};

class noMiem: public Abstract{
    public:
    void stringGenerate(){
        str_="11111111111111";
    }
    void cGenerate(){
        int summ = 0;
        int number = 0;
        for(int i=0;i<13;++i)
            summ = summ + ((int)str_[i]) * (i+1);
        while((summ + number * 14) % 10 ){
            number = number + 1;
            if(number > 9) //на случай бесконечного вызова 
            {
                summ = summ - str_[12]*13;
                str_[12] = (char)(abs((int)str_[12]-1) % 10) + 48;
                number = 0;
            }
        }
        str_[13] = (char)(number % 10 +48);
    };
    void dataGenerate(const std::string Data){
            for(int i=1;i<9;i++){
                str_[i] = Data[i - 1];
            }
            for(int i = 9;i<13;++i)
                str_[i] = (char)((int)Data[i - 9] * 9 %10 +48);
    };
    void sGenerate(const std::string S){
        if (S=="men")
            str_[0] = '2';
        else    
            str_[0] = '1';
    }
};


int main(int argc, char* argv[]){
    //file4
    if(!strcmp(argv[1], "--toFile" )){
        std::string S;
        std::string Data;
        std::string fileName;
        std::cout<<"Filename? Pol? Data?"<<std::endl;
        std::cin>>fileName>>S>>Data;
        Abstract* obj2;
        if(!strcmp(argv[2], "miem" ))
            obj2 = new Miem();
        else
            obj2 = new noMiem();

        obj2->generate(S,Data);
        

        std::ofstream out;
        out.open(fileName);
        if (out.is_open())
            out<<obj2->getStr()<<std::endl;
        else
            std::cout<<"Error file";
        out.close();
    }
    //file3
    else if(!strcmp(argv[1], "--fromFile" )){
        std::string S="";
        std::string Data="";
        std::string fileName;
        std::string   str="";
        std::cout<<"FileName?"<<std::endl;
        std::cin>> fileName;
        
        std::ifstream in(fileName);
        if (in.is_open()){
            bool flag = true;
            char c;
            while(in>>c){
                str = str + c;
                if (c<58){
                    flag=false;
                }
                if (flag){
                    S = S + c;
                }
                else{
                    Data = Data + c;
                }
            }
        } 
        Abstract* obj2;
        if(!strcmp(argv[2], "miem" ))
            obj2 = new Miem();
        else
            obj2 = new noMiem();
        obj2->generate(S,Data);
        std::cout<<obj2->getStr()<<std::endl;
    }
    return 0;
}