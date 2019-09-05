#include<bits/stdc++.h>
using namespace std;

struct storage
{
    string filename;
    int recentblock;
    map<int,string> blockdata;
    map<int,vector<int>> timeblock;
};

vector<storage> allfiles;
vector<string> filenames;

void savedata(string fname,string content,int tstamp)
{
    // First see if the file exist in the list of files
    int fileExists = 0;
    for(auto i=filenames.begin();i!=filenames.end();i++)
    {
        if(*i == fname)
        {
            fileExists = 1;
            break;
        }
    }
    // now if the file exists write in the already present file
    if(fileExists)
    {
        storage filed;
        int allSize = allfiles.size();
        int t_id=0;
        for(int traverse = 0;traverse <allSize;traverse++)
        {
            filed = allfiles[traverse];
            t_id = traverse;
            if(filed.filename==fname)
                break;
        }

        int conlen = content.length();
        int nofblock = conlen/8;
        if(conlen%8 != 0)
        {
            nofblock++;
        }

        for(int j=0;j<nofblock;j++)
        {
            string currblock="";
            int endsize = (j+1)*8;
            if(endsize > conlen)
                endsize = conlen;

            for(int k=8*j;k<endsize;k++)
            {
                currblock = currblock+content[k];
            }
            // as the file is already present we need to use recentblock number
            // check if the contents exists else
            int rused = filed.recentblock;
            map<int,string>::iterator itr;
            int skip = 0;
            for(itr=filed.blockdata.begin();itr!=filed.blockdata.end();++itr)
            {
                if(itr->second == currblock)
                {
                    skip = 1;
                    //cout<<itr->second<<endl;
                    //cout<<itr->first<<endl;
                    filed.timeblock.insert(pair<int,vector<int>>(tstamp,vector<int>()));
                    filed.timeblock[tstamp].push_back(itr->first);

                }
            }

            if(skip == 0)
            {

                filed.blockdata.insert(pair<int,string>(rused+1,currblock));
                filed.timeblock.insert(pair<int,vector<int>>(tstamp,vector<int>()));
                filed.timeblock[tstamp].push_back(rused+1);
                filed.recentblock = rused+1;
                //cout<<"IN Skip "<<endl;
                //cout<<tstamp<<endl;
                //cout<<currblock<<endl;
                //cout<<filed.recentblock<<endl;
            }

        }
        map<int,string>::iterator itr2;
        for(itr2=filed.blockdata.begin();itr2!=filed.blockdata.end();++itr2)
        {
                cout<<itr2->second<<endl;
                cout<<itr2->first<<endl;
        }

        allfiles[t_id] = filed;
    }
    else //if the file does not exist create a new file
    {
        filenames.push_back(fname);
        storage filed;
        filed.filename = fname;
        int conlen = content.length();
        int nofblock = conlen/8;
        if(conlen%8 != 0)
        {
            nofblock++;
        }
        for(int j=0;j<nofblock;j++)
        {
            string currblock="";
            int endsize = (j+1)*8;
            if(endsize > conlen)
                endsize = conlen;

            for(int k=8*j;k<endsize;k++)
            {
                currblock = currblock+content[k];
            }

            cout<<currblock<<endl;
            filed.blockdata.insert(pair<int,string>(j,currblock));
            filed.timeblock.insert(pair<int,vector<int>>(tstamp,vector<int>()));
            filed.timeblock[tstamp].push_back(j);
            filed.recentblock = j;
            cout<<filed.recentblock<<endl;

        }
        allfiles.push_back(filed);
    }

}

void printdata(string fname,int tstamp)
{
        storage filed;
        int allSize = allfiles.size();
        for(int traverse = 0;traverse <allSize;traverse++)
        {
            filed = allfiles[traverse];
            //t_id = traverse;
            if(filed.filename==fname)
                break;
        }



        vector<int> difftstamp;
        map<int,vector<int>>::iterator itr3;
        for(itr3=filed.timeblock.begin();itr3!=filed.timeblock.end();++itr3)
        {
            difftstamp.push_back(itr3->first);
        }
        if(find(difftstamp.begin(),difftstamp.end(),tstamp)==difftstamp.end())
        {


            int vecsize = difftstamp.size();
            int lowermin = difftstamp[0];
            sort(difftstamp.begin(),difftstamp.end());
            for(int m = 1;m<vecsize;m++)
            {
                lowermin = difftstamp[m];
                if(lowermin<=tstamp)
                    tstamp = lowermin;
                else if(lowermin>tstamp)
                    break;
            }

        }

        vector<int> blocknums = filed.timeblock[tstamp];

        int totalblocks = blocknums.size();
        for(int i = 0;i<totalblocks;i++)
        {
            cout<<filed.blockdata[blocknums[i]]<<endl;
            cout<<blocknums[i]<<endl;
        }

}

int main()
{
    //int x = 1;
    /*
    while(x==1)
    {
        cout<<"Enter your choice : "<<endl;
        int n;
        cout<<"1.Save Data"<<endl;
        cout<<"2.Print Data"<<endl;
        cout<<"3.Print FileSystem"<<endl;
        cin>>n;
        string fname;
        string content;
        int tstamp;

        switch(n)
        {
            case 1:cout<<"Enter filename : ";
                   cin>>fname;
                   cout<<"Enter content : ";
                   cin>>content;
                   cout<<"Enter timestamp : ";
                   cin>>tstamp;
                   savedata(fname,content,tstamp);
                   break;

            case 2:cout<<"Enter filename : ";
                   cin>>fname;
                   cout<<"Enter tstamp : ";
                   cin>>tstamp;
                   printdata(fname,tstamp);
                   break;

            case 3:
                   break;

            default:cout<<"Unable to perform requested operation"<<endl;
                    break;
        }

        cout<<"to continue input 1 else 0"<<endl;
        cin>>x;
    }
    */
    cout<<"At f1 tstamp - 5 - saving"<<endl;
    savedata("f1","ABCDEFGHIJKLMONPQRSTUVWX",5);
    cout<<endl;
    cout<<"At f1 tstamp - 10 - saving"<<endl;
    savedata("f1","ABCDEFGHIJKLMONPQRSTUVWXYZ",10);
    cout<<endl;
    cout<<"At f1 tstamp - 15 - saving"<<endl;
    savedata("f1","ABCDEFGHIJKLMONPQRSTUVWXXXXXYZ",15);
    cout<<endl;
    cout<<"At f1 tstamp - 20 - saving"<<endl;
    savedata("f1","ADCBEEFGHIJKLMO",20);
    cout<<endl;
    cout<<"At f1 tstamp - 13 - printing"<<endl;
    printdata("f1",13);
    cout<<endl;
    cout<<"At f1 tstamp - 20 - printing"<<endl;
    printdata("f1",20);
    cout<<endl;
    cout<<"At f2 tstamp 30 saving"<<endl;
    savedata("f2","ABCDEFGHIJKL",30);
    cout<<endl;
    cout<<"At f2 tstamp 40 saving"<<endl;
    savedata("f2","ABCDEFGHIJKLMN",40);
    cout<<endl;
    cout<<"At f2 tstamp 30 printing"<<endl;
    printdata("f2",30);
    cout<<endl;
    cout<<"At f2 tstamp 40 printing"<<endl;
    printdata("f2",40);
    return 0;
}
