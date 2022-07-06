
#include<iostream>
#include<string.h>
#include<fstream>
#include<ctype.h>
#include<windows.h>
#include<stdio.h>
#include<conio.h>
using std::cout; using std::ofstream;
using std::endl; using std::string;

using namespace std;

struct htnode
{
    char word[30];
    htnode *next,*down;
}*table[500]={NULL};


char vowels[5]={'a','e','i','o','u'};

char* searcher(char word[]){
	int j=0,f=0,i=0,k=0,g=0;
	char wrd[50];
	int n= strlen(word);
	 ///STEP 1:Drop duplicate adjacent letters except for  word C
	for(i=0;i<n;i++){
		wrd[j]=word[i];
		j++;
		if(word[i+1]==word[i] && word[i] !='c'){
			i++;
		}
	}
	
	wrd[j]='\0';  // it is mostly used to indicate the termination of a character string.
    // copy the contents of wrd to word now wrd becomes empty
    strcpy(word,wrd);
    n=strlen(word);



	/////STEP 2:If the word begins with 'KN', 'GN', 'PN', 'AE', 'WR', drop the first letter.
	switch(word[0]){
		case 'k': if(word[1]=='n'){
			 f=1;
			break;
		}
		case 'g': if(word[1]=='n'){
			f=1;
			break;
		}
		case 'p': if(word[1]=='n'){
			f=1;
			break;
		}
		case 'a' : if(word[1]=='e'){
			f=1;
			break;
		}
		case 'w' : if(word[1]=='r'){
			f=1;
			break;
		}
	}
	if(f==1){
		for(i=0; i<strlen(word)-1;i++){
			wrd[i]=word[i+1];
		}
		wrd[i]='\0';
        strcpy(word,wrd);
        n--;
	}
	
	///STEP 3:Drop 'B' if after 'M' at the end of the word.
	if(word[n-1]=='b')
	{
		if(word[n-2]=='m'){
			f=1;
		}
		
	}
	if(f==1){
		for(i=0;i<n;i++){
			wrd[i]=word[i];
		}
		wrd[i]='\0';
		strcpy(word,wrd);
	}
	n=strlen(word);
// remove ing it's at end

	if(word[n-1]=='g'){
		if (word[n-2]=='n'){
			if(word[n-3]=='i'){
				f=1;
			}
	}
}
	if(f==1){
		for(i=0;i<n;i++){
			if(i<n-3){
					wrd[i]=word[i];
			}
		   else{
		   	  wrd[i]='e';
		   	  i=n-1;
		   }
		}
		wrd[i]='\0';
		strcpy(word,wrd);
	}

	n=strlen(word);
	// If the word ends in -s, remove the -s
	if(word[n-1]=='s'){
		f=1;
	}
		if(f==1){
		for(i=0;i<n-1;i++){
					wrd[i]=word[i];
		}
		   
		
		wrd[i]='\0';
		strcpy(word,wrd);
	}
	n=strlen(word);

    // If the word ends in -ies, remove the -ies, and add -y
    
    if(word[n-1]=='s'){
		if (word[n-2]=='e'){
			if(word[n-3]=='i'){
				f=1;
			}
	}
}
	if(f==1){
		for(i=0;i<n;i++){
			if(i<n-3){
					wrd[i]=word[i];
			}
		   else{
		   	  wrd[i]='y';
		   	  i=n-1;
		   }
		}
		wrd[i]='\0';
		strcpy(word,wrd);
	}


	n=strlen(word);
	///STEP 4:'C' transforms to 'X' if followed by 'IA' or 'H' (unless in latter case, it is part of '-SCH-', 
	//in which case it transforms to 'K'). 'C' transforms to 'S' if followed by 
	//'I', 'E', or 'Y'. Otherwise, 'C' transforms to 'K'.
	  j=0;
    for(i=0;i<n;i++)
    {
        if(word[i]!='c')
        {
            wrd[j]=word[i];
        }
        else
        {
            switch(word[i+1])
            {
                case 'h':if(word[i-1]=='s')
                        {
                            wrd[j]='k';
                        }
                        else
                        {
                            wrd[j]='x';
                        }
                        break;

                case 'i':if(word[i+2]=='a')
                        {
                            wrd[j]='x';
      	                  }
                        else
                        {
                            wrd[j]='s';
                        }
                        break;

                case 'e':wrd[j]='s';

                case 'y':wrd[j]='s';
                        break;

                default: wrd[j]='k';

            }

        }
        j++;
    }
    wrd[j]='\0';
    strcpy(word,wrd);
    
     ///STEP 5:'D' transforms to 'J' if followed by 'GE', 'GY', or 'GI'. Otherwise, 'D' transforms to 'T'.
     n=strlen(word);
     j=0;
     for(i=0;i<n;i++){
     	if(word[i]!='d'){
     		wrd[j]=word[i];
		 }
		 else
		 {
		 	if(i<n-2)
		 	{
		 		if(word[i+1]=='g'){
		 			if((word[i+2]=='e') || (word[i+2]=='i') || (word[i+2]=='y')){
		 				f=1;
					 }
					 
				 }
			 }
			 if(f){
			 	wrd[i]='j';
			 	i=i+2;
			 }
			 else
			 {
			   wrd[j]='t'	;
			 }
		 }
		 j++;
	 }
	 wrd[j]='\0';
     strcpy(word,wrd);
     
      ///STEP 6:Drop 'G' if followed by 'H' and 'H' is not at the end or before a vowel.
	  // Drop 'G' if followed by 'N' or 'NED' and is at the end.
	  n=strlen(word);
    j=0;
    for(i=0;i<n;i++)
    {
        if(word[i]!='g')
        {
            wrd[j]=word[i];
            j++;
        }
        else
        {
          if(word[i+1]=='h'&&i!=n-2)
          {
              for(k=0;k<5;k++)
              {
                  if(word[i+2]==vowels[k])
                  {
                      g=1;
                  }
              }
              if(!g)
              {
                  f=1;
              }
          }
          else
          {
              if(word[i+1]=='n'&&i==n-2)
              {
                  f=1;
              }
          }
          if(!f)
          {
              wrd[j]=word[i];
              j++;
          }
        }
    }
    wrd[j]='\0';
    strcpy(word,wrd);
///STEP 7:'G' transforms to 'J' if before 'I', 'E', or 'Y', and it is not in 'GG'. Otherwise, 'G' transforms to 'K'.
    n=strlen(word);
    j=0;
    for(i=0;i<n;i++)
    {
        if(word[i]!='g')
        {
            wrd[i]=word[i];
        }
        else
        {
            switch(word[i+1])
            {
                case 'i':

                case 'e':

                case 'y': wrd[i]='j';
                          break;

                default:wrd[i]='k';
            }
        }
    }
    wrd[i]='\0';
    strcpy(word,wrd);
	
	 ///STEP 8:Drop 'H' if after vowel and not before a vowel.
    n=strlen(word);
    j=0;
    for(i=0;i<n;i++)
    {
        if(word[i]!='h')
        {
            wrd[j]=word[i];
            j++;
        }
        else
        {
            for(k=0;k<5;k++)
            {
                if(word[i-1]==vowels[k])
                {
                    f=1;
                }
            }
            for(k=0;k<5;k++)
            {
                if(word[i+1]==vowels[k])
                {
                    g=1;
                }
            }
            if(!(f==1&&g==0))
            {
                wrd[j]=word[i];
                j++;
            }

        }
    }
    wrd[j]='\0';
    strcpy(word,wrd);
	
	///STEP 10:'PH' transforms to 'F'.
    n=strlen(word);
    j=0;
    for(i=0;i<n;i++)
    {
        if(word[i]!='p')
        {
            wrd[j]=word[i];
            j++;
        }
        else
        {
            if(word[i+1]=='h')
            {
                wrd[j]='f';
                i++;
                j++;
            }
            else
            {
                wrd[j]=word[i];
                j++;
            }
        }
    }
    wrd[j]='\0';
    strcpy(word,wrd);
///STEP 11:'Q' transforms to 'K'.
    n=strlen(word);
    j=0;
    for(i=0;i<n;i++)
    {
        if(word[i]=='q')
        {
            wrd[i]='k';
        }
        else
        {
            wrd[i]=word[i];
        }
    }
    wrd[i]='\0';
    strcpy(word,wrd);
	
	///STEP 12:'S' transforms to 'X' if followed by 'H', 'IO', or 'IA'.
    n=strlen(word);
    j=0;
    for(i=0;i<n;i++)
    {
        if(word[i]!='s')
        {
            wrd[i]=word[i];
        }
        else
        {
            if(word[i+1]=='h')
            {
                f=1;
            }
            else
            {
                if(word[i+1]=='i')
                {
                    if((word[i+2]=='o')||(word[i+2]=='a'))
                    {
                        f=1;
                    }
                }
            }
            if(f==1)
            {
                wrd[i]='x';
            }
            else
            {
                wrd[i]=word[i];
            }
        }
    }
    wrd[i]='\0';
    strcpy(word,wrd);
	
   //STEP 13:'V' transforms to 'F'.
    n=strlen(word);
    j=0;
    for(i=0;i<n;i++)
    {
        if(word[i]=='v')
        {
            wrd[i]='f';
        }
        else
        {
            wrd[i]=word[i];
        }
    }
    wrd[i]='\0';
    strcpy(word,wrd);
    
     ///STEP 14:'WH' transforms to 'W' if at the beginning. Drop 'W' if not followed by a vowel.
    n=strlen(word);
    j=0;
    i=0;
    if(word[0]=='w'&&word[1]=='h')
    {
        i=2;
        wrd[j]='w';
        j++;
    }
    for(i=i;i<n;i++)
    {
        if(word[i]=='w')
        {
            for(k=0;k<5;k++)
            {
                if(word[i+1]==vowels[k])
                {
                    f=1;
                }
            }
        }
        else
        {
            f=1;
        }
        if(f)
        {
            wrd[j]=word[i];
            j++;
        }
        f=0;
    }
    wrd[j]='\0';
    strcpy(word,wrd);

 ///STEP 15:'X' transforms to 'S' if at the beginning. Otherwise, 'X' transforms to 'KS'.
    n=strlen(word);
    j=0;
    i=0;
    if(word[0]=='x')
    {
        i=1;
        wrd[j]='s';
        j++;
    }
    for(i=i;i<n;i++)
    {
        if(word[i]=='x')
        {
            wrd[j]='k';
            j++;
            wrd[j]='s';

        }
        else
        {
            wrd[j]=word[i];
        }
        j++;
    }
    wrd[j]='\0';
    strcpy(word,wrd);
    
     j=0;
    n=strlen(word);
    for(i=0;i<n;i++)
    {
        if(word[i]=='y')
        {
            f=0;
            for(k=0;k<5;k++)
            {
                if(word[i+1]==vowels[k])
                {
                    f=1;
                }
            }
            if(f)
            {
                wrd[j]='y';
                j++;
            }
        }
        else
        {
            wrd[j]=word[i];
            j++;
        }
    }
    wrd[j]='\0';
    strcpy(word,wrd);
    
    
     ///STEP 16:Drop 'Y' if not followed by a vowel.

    j=0;
    n=strlen(word);
    for(i=0;i<n;i++)
    {
        if(word[i]=='y')
        {
            f=0;
            for(k=0;k<5;k++)
            {
                if(word[i+1]==vowels[k])
                {
                    f=1;
                }
            }
            if(f)
            {
                wrd[j]='y';
                j++;
            }
        }
        else
        {
            wrd[j]=word[i];
            j++;
        }
    }
    wrd[j]='\0';
    strcpy(word,wrd);
    
    ///STEP 17:'Z' transforms to 'S'.
    n=strlen(word);
    i=0;
    j=0;
    for(i=0;i<n;i++)
    {
        if(word[i]=='z')
        {
            wrd[i]='s';
        }
        else
        {
            wrd[i]=word[i];
        }
    }
    wrd[i]='\0';
    strcpy(word,wrd);

	  
	 //STEP 19:Drop all vowels unless it is the beginning.
    n=strlen(word);
    j=0;
    i=0;
    wrd[0]=word[0];
    j=1;
    for(i=1;i<n;i++)
    {
        f=0;
        for(k=0;k<5;k++)
        {
            if(word[i]==vowels[k])
            {
                f=1;
            }
        }
        if(!f)
        {
            wrd[j]=word[i];
            j++;
        }
    }
    wrd[j]='\0';
    strcpy(word,wrd);
    word[5]='\0';

    return word;
} 


///HASH FUNCTION
int h(char word[])
{
    int i,v=0,a;
    for(i=0;i<strlen(word);i++)
    {
        a=int(word[i]);
        v=v+a;
    }
    v=v%500;

    return v;
}	





///INSERT IN THE TABLE
int tinsert(char word[])
{
    char word1[50];
    strcpy(word1,word);
    char* wrd=searcher(word);
    char wrd1[50];
    strcpy(wrd1,wrd);
    int a=h(wrd1);
    htnode *ptr=table[a];
    htnode *temp=new htnode;
    strcpy(temp->word,word1);
    temp->next=NULL;
    while(ptr!=NULL)
    {
        if(strcmp(ptr->word,wrd1)==0)
        {
            ptr=ptr->down;
            temp->down=ptr->down;
            ptr->down=temp;
            return 1;
        }
        ptr=ptr->next;
    }
    htnode *temp1=new htnode;
    strcpy(temp1->word,wrd1);
    temp->down=NULL;
    temp1->next=table[a];
    temp1->down=temp;
 
    table[a]=temp1;
}
 
 
 
///SEARCH IN THE TABLE
int tsearch(char word[])
{
    char word1[30];
    strcpy(word1,word);
    char *wrd=searcher(word);
    char wrd1[50];
    strcpy(wrd1,wrd);
    int a=h(wrd1);
    htnode *ptr=table[a];
    while(ptr!=NULL)
    {
        if(strcmp(wrd1,ptr->word)==0)
        {
            ptr=ptr->down;
            while(ptr!=NULL)
            {
                if(strcmp(word1,ptr->word)==0)
                {
                    cout<<endl<<endl<<"\t\t\t\tWord Found";
                    return 1;
                }
                else
                {
                    ptr=ptr->down;
                }
            }
            return -1;
        }
        ptr=ptr->next;
    }
    return -1;
}



int min(int x, int y, int z)
{
   return min(min(x, y), z);
}

int editDist(char str1[],char str2[], int m ,int n)
{

    if (m == 0) return n;


    if (n == 0) return m;


    if (str1[m-1] == str2[n-1])
        return editDist(str1, str2, m-1, n-1);


    return 1 + min ( editDist(str1,  str2, m, n-1),
                     editDist(str1,  str2, m-1, n),
                     editDist(str1,  str2, m-1, n-1)
                   );
}
void disp(char word[])
{
    char word1[30];
    strcpy(word1,word);
    char *wrd=searcher(word);
    char wrd1[50];
    strcpy(wrd1,wrd);
    int a=h(wrd1);
    htnode *ptr=table[a];

    while(ptr!=NULL)
    {
        if(strcmp(wrd1,ptr->word)==0)
        {
            ptr=ptr->down;
            while(ptr->down!=NULL)
            {
                int m=editDist(ptr->word,word1,strlen(ptr->word),strlen(word1));
                if(m<3&&m!=0)
                {
                        cout<<"\t\t\t\t\t"<<ptr->word<<endl;
                }
                   ptr=ptr->down;

            }
        }
        ptr=ptr->next;
    }

} 
main()
{
    char ch;
    system("color B");
    char word[30],word1[30],word2[30];
    int n,i;
    string name;
    fstream fin;
    fin.open("wl.txt",ios::in);

    while(fin!=NULL)
    {
        fin>>word;
        strcpy(word1,word);
        tinsert(word);
    }
    fin.close();

    do
    {
        cout<<"\n";
        cout<<"SPELL CHECKER";
        cout<<"\n";
        cout<<"Hareem Arshad(2020-CE-34)";
        cout<<"\n";
        cout<<"Hira Sohail(2020-CE-41)";
        cout<<"\n";
        cout<<endl<<endl<<endl<<endl;
        cout<<"ENTER THE WORD YOU WANT TO SEARCH: ";
        cin>>word;
        strcpy(word2,word);
        int s=tsearch(word);
        cout<<endl<<endl;
        if(s==-1)
        {
            cout<<"Sorry,No such word exist!"<<endl;
            ofstream myfile;
            disp(word2);
        }
    
        cout<<"You might have meant these words!"<<endl;
        cout<<endl<<endl<<endl<<"choose a word which you want ";
        string id;
	    fstream myfile;
	    myfile.open("add.txt",ios::out|ios::app);
	    cout<<endl;
	    cout<<"Enter the word which you want : ";
	    cin>>id;
	    myfile<<id<<"|"<<"\n";
	    myfile.close();
        cout<<endl<<endl<<endl<<"Do you want to continue(y/n)?";
        ch=getch();
        cout<<endl<<endl<<endl;
    }while(ch=='y');


   
    cout<<"Azadi Mubarak"<<endl;
    cout<<"Aish krooo "<<endl;

}
