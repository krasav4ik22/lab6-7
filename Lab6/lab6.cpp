#include<iostream>
#include<string>
#include <string.h>
#include <fstream>
class Abstract{
    public:
        virtual geterate(std::string S, std::string Data) = 0;
};

class Miem:public Abstract{
    protected:
        std::string str_; 
    public:
        void dataGenerate(const std::string Data);
        void sGenerate();
        std::string getStr(){return str_;}
        Miem(){
            str_="111111111111111";
        }
        geterate(std::string S, std::string Data){
            if (S=="men")
                str_[0] = '8';
            else
                str_[0] = '4';
            dataGenerate(Data);
            sGenerate(); 
        }
};

void Miem::dataGenerate(const std::string Data){
            for(int i=1;i<9;i++){
                str_[i] = Data[i - 1];
            }
            for(int i = 9;i<14;++i)
                str_[i] = (char)((int)Data[i - 9] * 9 %10 +48);
}


void Miem::sGenerate(){
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
}


//Не миэм
class noMiem:public Abstract{
    protected:
        std::string str_; 
    public:
        void dataGenerate(const std::string Data);
        void sGenerate();
        std::string getStr(){return str_;}
        noMiem(){
            str_="11111111111111";
        }
        geterate(std::string S, std::string Data){
            if (S=="men")
                str_[0] = '2';
            else
                str_[0] = '1';
            sGenerate();
            dataGenerate(Data);
        }
};

void noMiem::dataGenerate(const std::string Data){
            for(int i=1;i<9;i++){
                str_[i] = Data[i - 1];
            }
            for(int i = 9;i<13;++i)
                str_[i] = (char)((int)Data[i - 9] * 9 %10 +48);
}

void noMiem::sGenerate(){
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

int main(int argc, char* argv[]){
    //file1
    if(!strcmp(argv[1], "--toFile" )){
        std::string S;
        std::string Data;
        std::string fileName;
        std::cout<<"Filename? Pol? Data?"<<std::endl;
        std::cin>>fileName>>S>>Data;

        noMiem noMiem;
        Miem Miem;
        noMiem.geterate(S,Data);
        Miem.geterate(S,Data);

        std::ofstream out;
        out.open(fileName);
        if (out.is_open())
            out<<Miem.getStr()<<std::endl<<noMiem.getStr();
        else
            std::cout<<"Error file";
        out.close();
    }
    //file2
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
        noMiem noMiem;
        Miem Miem;
        noMiem.geterate(S,Data);
        Miem.geterate(S,Data);
        std::cout<<noMiem.getStr()<<std::endl<<Miem.getStr()<<std::endl;
    }
    return 0;
}