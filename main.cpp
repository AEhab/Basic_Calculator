#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <cstdio>


using namespace std;

int countsign(string str);

double converttonum(string str);
double solve_signs(stack <char> signs,stack <double> Nums);
double calculate_pure_str(string Input);

string convertdoubletostr(double ans);
string cut_paste_str(string L,int be,int en,double ans);
string solve_neg_sign(string IN);
string solve_all(string INPUT);
stack <double> stack_reverse ( stack <double> x);
stack <char> stack_reverse ( stack <char> x);

int main()
{
    string INPUT;
    while(1)
    {
        cin >> INPUT;  // input example = "(5*(6+-7)/(8-90)*-11)" with out ""
        cout<<solve_all(INPUT)<<"\n";
    }

    return 0;
}





double solve(stack <char> signs,stack <double> Nums)
{
    stack <char> notnows;
    stack <double> notnown;
    double x,y;
    signs = stack_reverse(signs);
    Nums = stack_reverse(Nums);
    while((int)signs.size()>0)
    {
        if(signs.top()=='*'||signs.top()=='/')
        {
            x=Nums.top();
            Nums.pop();
            y=Nums.top();
            Nums.pop();
            if(signs.top()=='*')
                Nums.push(x*y);
            else
                Nums.push(x/y);
            signs.pop();
        }
        else
        {
            notnown.push(Nums.top());
            Nums.pop();
            notnows.push(signs.top());
            signs.pop();
        }
    }
     notnown.push(Nums.top());
     Nums.pop();
     notnown = stack_reverse(notnown);
     notnows = stack_reverse(notnows);

    while ((int)notnows.size()>0)
    {
        x=notnown.top();
        notnown.pop();
        y=notnown.top();
        notnown.pop();

        if(notnows.top()=='+')
            notnown.push(x+y);
        else
            notnown.push(x-y);

        notnows.pop();
    }
    return notnown.top();
}

double calculate_pure_str(string Input)
{
    stack <double> numbers;
    stack <char> signs;
    string num;
    double floo;
    bool flag=0;
    int i,j,test;

    Input=solve_neg_sign(Input);

    for (i=1;i<(int)Input.length()-1;i++)
    {
        num="";
        flag=0;
        while(Input[i]!='+'&&Input[i]!='-'&&Input[i]!='*'&&Input[i]!='/'&&i<(int)Input.length()-1)
        {
            if(Input[i]=='.')
            {
                flag=1;
                floo=converttonum(num);
                num="";
                i++;
            }
            num+=Input[i];
            i++;
        }
        if(flag==0)
        numbers.push(converttonum(num));
        else
        {
            test=1;
            j=0;
            while(j<(int)num.length())
                test*=10,j++;

            if(floo>0)
            numbers.push(floo+(converttonum(num)/test));
            else
                numbers.push(floo-(converttonum(num)/test));
        }
        if(Input[i]!=')'&&Input[i]!='(')
        signs.push(Input[i]);
    }
//    stack <double> f = numbers;
//    cout<<endl<<"{";
//   while (f.size()>0)
//    {
//        cout<<f.top()<<" ";
//        f.pop();
//    }
//    cout<<endl<<"}";
    return solve(signs,numbers);
}

string solve_all(string INPUT)
{
    int i,be,signs;
    double ans;
    string shortstr;
    signs=countsign(INPUT)+1;
    while (signs)
    {
        shortstr="";
        be=0;
        for (i=0;i<(int)INPUT.length()&&INPUT[i]!=')';i++)
        {
            if(INPUT[i]=='(')
                shortstr="",be=i;
            else
                shortstr+=INPUT[i];
        }
        shortstr='('+shortstr+')';
        ans = calculate_pure_str(shortstr);
        //cout<<ans<<endl;
        INPUT = cut_paste_str(INPUT,be,i+1,ans);
        signs--;
    }
    return INPUT;
}

string cut_paste_str(string L,int be,int en,double ans)
{
    string ne;

    for(int i=0;i<be;i++)
        ne+=L[i];
        ne+=convertdoubletostr(ans);
    for(int i=en;i<(int)L.length();i++)
        ne+=L[i];
    return ne;
}

string solve_neg_sign(string IN)
{
    int i;
    string OUT;
    for(i=0;i<(int)IN.length()-1;i++)
    {
        if(IN[i+1]=='-'&&(IN[i]=='*'||IN[i]=='/'||IN[i]=='-'||IN[i]=='+'))
        {
            OUT+=IN[i];
            OUT+='N';
            i++;
        }
        else
            OUT+=IN[i];
    }
    OUT+=IN[i];
    return OUT;
}

string convertdoubletostr(double ans)
{
    long long int i,inty,dec;
    bool flag = 0;
    string out="";
    if(ans<0)
    {
         ans=ans*-1;
         flag=1;
    }
    inty=ans;
    ans=ans-(double)inty;
    for(i=0;i<7;i++)
        ans*=10;

    dec = ans;
    while(i)
    {
        out=(char)('0'+(dec%10))+out;
        dec/=10;
        i--;
    }
    out='.'+out;
    i=inty;
    while(inty)
    {
        out=(char)('0'+(inty%10))+out;
        inty/=10;
    }

    if (i==0)
        out='0'+out;
    if(flag)
        out='-'+out;
    return out;
}

int countsign(string str)
{
    int o=0;
    for(int i=0;i<(int)str.length();i++)
    {
        if(str[i]=='(')
            o++;
    }
    return o;
}

double converttonum(string str)
{
    int no=0,i=0,ne=1;
    if(str[0]=='N')
        i=1,ne=-1;
    for(;i<(int)str.length();i++)
    {
        no*=10;
        no+=(str[i]-'0');
    }
    return no*ne;
}

stack <double> stack_reverse ( stack <double> x)
{
    queue <double> Q;
    while((int)x.size()>0)
    {
        Q.push(x.top());
        x.pop();
    }
    while((int)Q.size()>0)
    {
        x.push(Q.front());
        Q.pop();
    }
    return x;
}

stack <char> stack_reverse ( stack <char> x)
{
    queue <char> Q;
    while((int)x.size()>0)
    {
        Q.push(x.top());
        x.pop();
    }
    while((int)Q.size()>0)
    {
        x.push(Q.front());
        Q.pop();
    }
    return x;
}
