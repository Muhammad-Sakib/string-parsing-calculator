#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int steps=1;
char tri_func_name[6][5] = {
                         "tan",
                         "sec",
                         "sin",
                         "cos",
                         "cot",
                         "log",
                         "cosec"
                     };

int mathOp();
void showCal(char str[])
{
    printf("\n\n\t\t\t------------------------------------------------------------\n");
    printf("\t\t\t|   Mathematical Expression Solving Scientific Calculator  |");
    printf("\n\t\t\t------------------------------------------------------------\n\n\n\n\n");
    printf("\t\t\t------------------------------------------------------------\n\n");
    printf("\t\t\t| Enter a Mathematical Expression: ");
    gets(str);
    printf("\n\t\t\t------------------------------------------------------------\n");
}

int charToInt(char ch)
{
    for(int i=0;i<10;i++)
    {
        if(ch == 48+i)
        {
            return i;
        }
    }
}

int stringToInt(char str[])
{
    int sum=0;
    for(int i=0;i<strlen(str);i++)
    {
        sum = sum*10 + charToInt(str[i]);
    }
    return sum;
}

void intToString(int value, char arr[])
{
    //printf("value: %d",value);
    int i=0,check=0;
    if(value<0)
    {
        value = abs(value);
        check=1;
    }
    else if(value==0)
    {
        arr[i]='0';
        i++;
    }
    while(value != 0)
    {
        arr[i] = 48+ 0+ value%10;
        value = value/10;
        i++;
    }
    if(check==1)
    {
        arr[i] = '-';
        arr[i+1]='\0';
    }
    else{
        arr[i]='\0';
    }
}

void addString(int left, int right, char str[], char sub_str[])
{
    int i=left, j= strlen(sub_str)-1;
    int start_right= left+j+1, right_add= right+1;
    if(sub_str[j] == '-' && str[i-1] == '-' && i-1!=0)
    {
        str[i-1] = '+';
        j--;
        start_right--;
    }
    else if(sub_str[j] == '+' && str[i-1] == '-' && i-1 == 0)
    {
        i--;
        start_right--;
    }
    else if((sub_str[j] == '-' && str[i-1] == '+') || (sub_str[j] == '+' && str[i-1] == '-'))
    {
        start_right--;
        str[i-1] = '-'; // replace main string sign
        j--; //delete sub string sign
    }
    else if(sub_str[j] == '-' && str[i-1] == '*')
    {
        str[i-1] = '*';
        j--;
        start_right--;
        int k;
        for(k=left-2;k>=0;k--)
        {
            if(str[k] >= '0' && str[j] <= '9')
            {
                continue;
            }
            else{
                break;
            }
        }
        if(k==-1)
        {
            k=0;
        }
        if(str[k] == '-')
        {
            str[k] == '+';
        }
        else if(str[k]=='+')
        {
            str[k] ='-';
        }
    }
    while(j>=0)
    {
        str[i] = sub_str[j];
        i++;
        j--;
    }
    while(str[right_add]!= '\0')
    {
        str[start_right] = str[right_add];
        start_right++;
        right_add++;
    }
    str[start_right] ='\0';
}
//search and parse String
int trigonoFunc(int left, int brac, int right, char temp_str[])
{
    int check =0,line,count=0,i, temp_left=left,start=0;
    char x[20];
    if(brac == 3)
        {
            line=6;
        }
        else{
            line= 7;
            start=6;
        }
    for(i=start;i<line;i++)
    {
            for(int j=0;j<brac;j++)
            {
                if(temp_str[temp_left] == tri_func_name[i][j])
                {
                    check =1;
                }
                else{
                    check =0;
                    break;
                }
                temp_left++;
            }
            temp_left=left;
            if(check==1)
            {
                break;
            }
    }
    for(int k=left+brac+1;k<right;k++)
    {
        x[count] = temp_str[k];
        count++;
        x[count] = '\0';
    }
    int value = stringToInt(x);
    if(i==0)
    {
        return tan(value);
    }
    else if(i==1)
    {
        return 1/cos(value);
    }
    else if(i==2)
    {
        return sin(value);
    }
    else if(i==3)
    {
        return cos(value);
    }
    else if(i==4)
    {
        return 1/tan(value);
    }
    else if(i==5)
    {
        return log10(value);
    }
    else if(i==6)
    {
        return 1/sin(value);
    }

}
int parseString(char str[])
{
    int i, j, k, left=0, right=0, arr[3], check_first_loop, check_bracket=0;
    char parsed_str[100],sub_str[20],temp_str[100];
    strcpy(temp_str,str);
    while(0==0)
    {
        // trigonometry func
        for(i=0;i<strlen(temp_str);i++)
        {
            if(temp_str[i] == 't' || temp_str[i] == 's' || temp_str[i] == 'c' || temp_str[i] == 'l')
            {
                left=arr[1] =i;
                for(int k=i+1;k<strlen(temp_str);k++)
                {
                    if(temp_str[k] == '(')
                    {
                        check_bracket = k-i;
                    }
                    if(temp_str[k] != '+' && temp_str[k] != '-' && temp_str[k] != '*' && temp_str[k] != '/')
                    {
                        arr[2] = right=k;
                    }
                    else{
                        break;
                    }
                }
                break; // from left to right * and /
            }
        }
        //find sub string -> do operation -> then merge it
        if(left >= 0 && right != 0)
        {
            int value = trigonoFunc(left,check_bracket,right,temp_str); // Do math return int
            intToString(value,sub_str); // value to string -> sub_str
            addString(left,right,temp_str,sub_str);
            printf("\n\t\t\t| Step %d: %s\n",steps,temp_str);
            printf("\t\t\t------------------------------------------------------------\n");
            steps++;
            left = right =0;
            continue; // do * and / first then move to +- section
        }
        // power
        for(i=0;i<strlen(temp_str);i++)
        {
            if(temp_str[i] == '^')
            {
                arr[1] =i;
                check_first_loop = i;
                for(int j=i-1;j>=0;j--)
                {
                    if(temp_str[j] >= '0' && temp_str[j] <= '9')
                    {
                        arr[0] = left = j;
                    }
                    else{
                        break;
                    }
                }
                for(int k=i+1;k<strlen(temp_str);k++)
                {
                    if(temp_str[k] >= '0' && temp_str[k] <= '9')
                    {
                        arr[2] = right=k;
                    }
                    else{
                        break;
                    }
                }
                break; // from left to right * and /
            }
        }
        //find sub string -> do operation -> then merge it
        if(left >= 0 && right != 0)
        {
            int value = mathOp(arr[0],arr[1],arr[2],temp_str); // Do math return int
            intToString(value,sub_str); // value to string -> sub_str
            addString(left,right,temp_str,sub_str);
            printf("\t\t\t| Step %d: %s\n",steps,temp_str);
            printf("\t\t\t------------------------------------------------------------\n");
            steps++;
            left = right =0;
            continue; // do * and / first then move to +- section
        }
        for(i=0;i<strlen(temp_str);i++)
        {
            if(temp_str[i] == '*' || temp_str[i] == '/')
            {
                arr[1] =i;
                check_first_loop = i;
                for(int j=i-1;j>=0;j--)
                {
                    if(temp_str[j] >= '0' && temp_str[j] <= '9')
                    {
                        arr[0] = left = j;
                    }
                    else{
                        break;
                    }
                }
                for(int k=i+1;k<strlen(temp_str);k++)
                {
                    if(temp_str[k] >= '0' && temp_str[k] <= '9')
                    {
                        arr[2] = right=k;
                    }
                    else{
                        break;
                    }
                }
                break; // from left to right * and /
            }
        }
        //find sub string -> do operation -> then merge it
        if(left >= 0 && right != 0)
        {
            int value = mathOp(arr[0],arr[1],arr[2],temp_str); // Do math return int
            intToString(value,sub_str); // value to string -> sub_str
            addString(left,right,temp_str,sub_str);
            printf("\t\t\t| Step %d: %s\n",steps,temp_str);
            printf("\t\t\t------------------------------------------------------------\n");
            steps++;
            left = right =0;
            continue; // do * and / first then move to +- section
        }
        left = right =0;
        for(i=0;i<strlen(temp_str);i++)
        {
            if(temp_str[i] == '+' || (temp_str[i] == '-' && i!=0))
            {
                arr[1] =i;
                for(int j=i-1;j>=0;j--)
                {
                    if((temp_str[j] >= '0' && temp_str[j] <= '9'))
                    {
                        arr[0] = left = j;
                    }
                    else{
                        break;
                    }
                }
                for(int k=i+1;k<strlen(temp_str);k++)
                {
                    if(temp_str[k] >= '0' && temp_str[k] <= '9')
                    {
                        arr[2] = right=k;
                    }
                    else{
                        break;
                    }
                }
                break; // from left to right + and -
            }
        }
        if(left >= 0 && right != 0)
        {
            int value = mathOp(arr[0],arr[1],arr[2],temp_str);
            intToString(value,sub_str);
            addString(left,right,temp_str,sub_str);
            printf("\t\t\t| Step %d: %s\n",steps,temp_str);
            printf("\t\t\t------------------------------------------------------------\n");
            steps++;
        }
        if(left ==0 && right ==0)
        {
            break;
        }
        left= right =0;
    }
    // copying tempstr to str
    strcpy(str, temp_str);
    return 1;
}
int mathOp(int left, int sign, int right, char str[])
{
    char x[20], y[20];
    int i,j,count=0, math_op;
    for(i=left;i<sign;i++)
    {
        x[count] = str[i];
        count++;
        x[count] = '\0';
    }
    count =0;
    for(j=sign+1;j<=right;j++)
    {
        y[count] = str[j];
        count++;
        y[count] = '\0';
    }
    int value_1 = stringToInt(x);
    int value_2 = stringToInt(y);

    if(str[sign] == '^')
    {
        return pow(value_1, value_2);
    }
    else if(str[sign] == '*')
    {
        return value_1 * value_2;
    }
    else if(str[sign] == '/')
    {
        return value_1 / value_2;
    }
    else if(str[sign] == str[left-1] || str[sign] == '+')
    {
        if(str[sign] == '+' && str[left-1]=='-')
        {
            return value_2 - value_1;
        }
        else{
            return value_1 + value_2;
        }
    }
    else if((str[sign] == '-' && str[left-1]=='+') || str[sign] == '-')
    {
        return value_1 - value_2;
    }
}
int main()
{
    char str[100],sub_str[100],j;
    int count=0;
    showCal(str);
    int value = parseString(str);
    if(value==1)
    {   printf("\n\n\t\t\t------------------------------------------------------------\n");
        printf("\t\t\t|Your answer is: %s\n",str);
        printf("\t\t\t------------------------------------------------------------\n");
    }
    return 0;
}
