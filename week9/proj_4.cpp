#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#define STRING_NUM 20

using namespace std;

string my_to_string(int val)
{
    char buffer[10] = {0};
    int digit;
    int i = 0;
    while (val > 9) {
        digit = val % 10;
        buffer[i++] = digit + 48;
        val /= 10;
    }
    buffer[i++] = val + 48;
    for (int j = 0; j < i/2; ++j) {
        char tmp = buffer[j];
        buffer[j] = buffer[i-j-1];
        buffer[i-j-1] = tmp;
    }
    string str(buffer);
    return str;
}

class StringOperation
{
    int mN;
    string *mStrings[STRING_NUM];
public:
    StringOperation(int n){mN = n;}
    void getStrings(){
        for (int i = 0; i < mN; ++i) {
            mStrings[i] = new string;
            cin >> *mStrings[i];
        }
    }
    size_t find(const string& str, int n){
        size_t pos = mStrings[n]->find(str);
        if (pos == string::npos) {
            return mStrings[n]->size();
        }
        return pos;
    }
    size_t rfind(const string& str, int n){
        size_t pos = mStrings[n]->rfind(str);
        if (pos == string::npos) {
            return mStrings[n]->size();
        }
        return pos;
    }
        //copy N X L：取出第N个字符串第X个字符开始的长度为L的字符串。
    string copy(int n, int x, int l){
        return mStrings[n]->substr(x, l);
    }
        //insert S N X 在第N个字符串的第X个字符位置中插入S字符串
    void insert(const string& str, int n, int x){
        mStrings[n]->insert(x, str);
    }
        //reset S N：将第N个字符串变为S
    void reset(const string& str, int n){
        *mStrings[n] = str;
    }
        //print N：打印输出第N个字符串。
        //printall：打印输出所有字符串。
    void print(int n){cout << *mStrings[n] << endl;}
    void printall(){
        for (int i = 0; i < mN; ++i) {
            cout << *mStrings[i] << endl;
        }
    }
};


string add(const string &str1, const string &str2){
    bool str1Numeric = true;
    bool str2Numeric = true;
    for (int i = 0; i < (int)str1.size(); ++i) {
        if ((str1[i] >= 'a' && str1[i] <= 'z') || (str1[i] >= 'A' && str1[i] <= 'Z')) {
            str1Numeric = false;
            break;
        }
    }
    
    for (int i = 0; i < (int)str2.size(); ++i) {
        if ((str2[i] >= 'a' && str2[i] <= 'z') || (str2[i] >= 'A' && str2[i] <= 'Z')) {
            str2Numeric = false;
            break;
        }
    }
    
    int s1 = 0;
    int s2 = 0;
    if (str1Numeric && str2Numeric) {
        s1 = atoi(str1.c_str());
        s2 = atoi(str2.c_str());
        if (s1 < 0 || s1 > 99999) {
            str1Numeric = false;
        }
        if (s2 < 0 || s2 > 99999) {
            str2Numeric = false;
        }
    }
    
    if (str1Numeric && str2Numeric) {
        int res = s1 + s2;
        return my_to_string(res);
    } else {
        return str1 + str2;
    }
}


void parseCommand(string &str, StringOperation &so){
    int posIndex[6];
    posIndex[0] = (int)str.rfind("copy ");
    posIndex[1] = (int)str.rfind("add ");
    posIndex[2] = (int)str.rfind("find ");
    posIndex[3] = (int)str.rfind("rfind ");
    posIndex[4] = (int)str.rfind("insert ");
    posIndex[5] = (int)str.rfind("reset ");
    
    if (posIndex[2] > 0 && str[posIndex[2]-1] == 'r') {
        posIndex[2] = -1;
    }
    int maxIndex = 0;
    for (int i = 0; i < 6; ++i) {
        if (posIndex[i] != string::npos)
            if (posIndex[i] >= posIndex[maxIndex])
                maxIndex = i;
    }
    string nStr, xStr, lStr, res, s;
    size_t nPos, nEndPos;
    size_t sPos, sEndPos;
    size_t xPos, xEndPos;
    size_t sbstrLen;
    int n, x;
    switch (maxIndex) {
        case 0:
        {
            //copy N X L：取出第N个字符串第X个字符开始的长度为L的字符串。
        nPos = str.find_first_of(' ', posIndex[0]) + 1;
        nEndPos = str.find_first_of(' ', nPos);
        string nStr = str.substr(nPos, nEndPos - nPos);
        int n = atoi(nStr.c_str());
        
        xPos = nEndPos + 1;
        xEndPos = str.find_first_of(' ', xPos);
        xStr = str.substr(xPos, xEndPos - xPos);
        int x = atoi(xStr.c_str());
        
        size_t lPos = xEndPos + 1;
        size_t lEndPos = str.find_first_of(' ', lPos);
        if (lEndPos == string::npos) {
            lStr = str.substr(lPos);
            sbstrLen = str.size() - posIndex[0];
        } else {
            lStr = str.substr(lPos, lEndPos - lPos);
            sbstrLen = lEndPos - posIndex[0];
        }
        int l = atoi(lStr.c_str());
        res = so.copy(n-1, x, l);
        str.replace(posIndex[0], sbstrLen, res);
        }
            break;
        case 1:
        {
            //add S1 S2
        size_t str1Pos = str.find_first_of(' ', posIndex[1]) + 1;
        size_t str1EndPos = str.find_first_of(' ', str1Pos);
        string str1 = str.substr(str1Pos, str1EndPos - str1Pos);
        size_t str2Pos = str1EndPos + 1;
        size_t str2EndPos = str.find_first_of(' ', str2Pos);
        string str2;
        if (str2EndPos == string::npos) {
            str2 = str.substr(str2Pos);
            sbstrLen = str.size() - posIndex[1];
        } else {
            str2 = str.substr(str2Pos, str2EndPos - str2Pos);
            sbstrLen = str2EndPos - posIndex[1];
        }
        res = add(str1, str2);
        str.replace(posIndex[1], sbstrLen, res);
        }
            break;
        case 2:
        {
            //find S N：在第N个字符串中从左开始找寻S字符串，返回其第一次出现的位置，若没有找到，返回字符串的长度。
        sPos = str.find_first_of(' ', posIndex[2]) + 1;
        sEndPos = str.find_first_of(' ', sPos);
        s = str.substr(sPos, sEndPos - sPos);
        nPos = sEndPos + 1;
        nEndPos = str.find_first_of(' ', nPos);
        if (nEndPos == string::npos) {
            nStr = str.substr(nPos);
            sbstrLen = str.size() - posIndex[2];
        } else {
            nStr = str.substr(nPos, nEndPos - nPos);
            sbstrLen = nEndPos - posIndex[2];
        }
        int n = atoi(nStr.c_str());
        int pos = (int)so.find(s, n-1);
        string resStr = my_to_string(pos);
        str.replace(posIndex[2], sbstrLen, resStr);
        }
            break;
        case 3:
        {
            //rfind S N
        sPos = str.find_first_of(' ', posIndex[3]) + 1;
        sEndPos = str.find_first_of(' ', sPos);
        s = str.substr(sPos, sEndPos - sPos);
        nPos = sEndPos + 1;
        nEndPos = str.find_first_of(' ', nPos);
        if (nEndPos == string::npos) {
            nStr = str.substr(nPos);
            sbstrLen = str.size() - posIndex[3];
        } else {
            nStr = str.substr(nPos, nEndPos - nPos);
            sbstrLen = nEndPos - posIndex[3];
        }
        n = atoi(nStr.c_str());
        int ret = (int)so.rfind(s, n-1);
        string resStr = my_to_string(ret);
        str.replace(posIndex[3], sbstrLen, resStr);
        }
            break;
        case 4:
        {
        /*insert S N X：在第N个字符串的第X个字符位置中插入S字符串。
         */
        sPos = str.find_first_of(' ', posIndex[4]) + 1;
        sEndPos = str.find_first_of(' ', sPos);
        s = str.substr(sPos, sEndPos - sPos);
        nPos = sEndPos + 1;
        nEndPos = str.find_first_of(' ', nPos);
        xPos = nEndPos + 1;
        xEndPos = str.find_first_of(' ', xPos);
        if (xEndPos == string::npos) {
            xStr = str.substr(xPos);
            sbstrLen = str.size() - posIndex[4];
        } else {
            xStr = str.substr(xPos, xEndPos - xPos);
            sbstrLen = xEndPos - posIndex[4];
        }
        x = atoi(xStr.c_str());
        nStr = str.substr(nPos, nEndPos);
        n = atoi(nStr.c_str());
        so.insert(s, n-1, x);
        str.erase(posIndex[4], sbstrLen);
        }
            break;
        case 5:
        {
        sPos = str.find_first_of(' ', posIndex[5]) + 1;
        sEndPos = str.find_first_of(' ', sPos);
        s = str.substr(sPos, sEndPos - sPos);
        nPos = sEndPos + 1;
        nEndPos = str.find_first_of(' ', nPos);
        if (nEndPos == string::npos) {
            nStr = str.substr(nPos);
            sbstrLen = str.size() - posIndex[5];
        } else {
            nStr = str.substr(nPos, nEndPos - nPos);
            sbstrLen = nEndPos - posIndex[5];
        }
        n = atoi(nStr.c_str());
        so.reset(s, n-1);
        str.erase(posIndex[5], sbstrLen);
        }
            break;
    }
    
    if (!posIndex[maxIndex]) {
        return;
    }
    parseCommand(str, so);
}




int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    StringOperation so(n);
    so.getStrings();
    
    while (true) {
        char buffer[1024];
        cin.getline(buffer, sizeof(buffer));
        size_t size = strlen(buffer);
        if (!size)
            continue;
        if (buffer[size-1] == '\n')
            buffer[size-1] = 0;
        if (!strncmp(buffer, "over", 4)) {
            break;
        } else if (!strncmp(buffer, "print ", 6)) {
            char *end;
            int d = strtod(buffer + 6, &end);
            so.print(d-1);
        } else if (!strncmp(buffer, "printall", 8)) {
            so.printall();
        } else {
            string str(buffer);
            parseCommand(str, so);
        }
    }
    return 0;
}





