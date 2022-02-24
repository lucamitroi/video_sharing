#include <iostream>
#include <conio.h>
#include "videos.h";
#include <fstream>
#include <vector>
#include <ctime>
#define BUFFER_SIZE 1000
using namespace std;


void read_channel(channel channel_array[], int n)
{
    ifstream fin("files/Canale.in");
    char x[200];
    int nr;
    for(int i=0; i<n; i++)
    {
        fin.getline(x,200);
        channel_array[i].setName(x);
    }
    fin.close();
}

void read_videos(channel channel_array[], int n)
{
    FILE* all_videos =  fopen("files/all_videos.csv", "r");
    char buffer[BUFFER_SIZE];
    int index = -1;
    char text[200];
    char channel_name[300];
    while(fgets(buffer, BUFFER_SIZE, all_videos) != NULL)
    {
        char *p1 = strtok(buffer, ";");
        for(int i = 0; i < n; i++)
        {
            if(strcmp(channel_array[i].getName(), p1) == 0)
            {
                index = i;
                channel_array[i].setClipsNumber();
            }
        }
        char *p2 = strtok(NULL, ";");
        if(index != -1)
            channel_array[index].clips[channel_array[index].getClipsNumber() - 1].setName(p2);
        char *p3 = strtok(NULL, ";");
        if(index != -1)
            channel_array[index].clips[channel_array[index].getClipsNumber() - 1].setUpload(p3);
        char *p4 = strtok(NULL, ";");
        if(index != -1)
            channel_array[index].clips[channel_array[index].getClipsNumber() - 1].setDescription(p4);
        char *p5 = strtok(NULL, ";");
        if(index != -1)
            channel_array[index].clips[channel_array[index].getClipsNumber() - 1].setDuration(p5);
    }
}
void vezi_video(channel ch[], int clip_nr)
{
    for(int i = 0; i < clip_nr; i++)
    {
        cout << ch[i].getName() << endl << endl;
        cout<<ch[i];
    }
}

int cursor_meniu(int n, char *Meniu[])
{
    char ch;
    int current = 0;
    while (ch != 13)
    {
        system("cls");
        cout << "Meniul se parcurge cu sagetile de pe numpad (apasa num lock daca nu merge)" << endl;
        for (int i = 0; i < n; i++)
        {
            if (i == current)
            {
                printf("%s", "  ---->  ");
            }
            else
            {
                printf("         ");
            }
            printf("%d %s", i + 1, "  ");
            printf("%s\n", Meniu[i]);

        }

        ch = getch();
        if (ch == 0)
        {
            ch = getch();
            if (ch == 80)
            {
                current++;
                if (current == n)
                {
                    current = 0;
                }
            }
            else if (ch == 72)
            {
                current--;
                if (current == -1)
                {
                    current = n - 1;
                }
            }
        }
    }
    return current;
}
int cursor(int n, char *Meniu[],channel canal[], int clip_nr)
{

    char ch;
    int current = 0;
    while (ch != 13)
    {
        system("cls");
        vezi_video(canal,clip_nr);
        cout<<endl<<endl;
        for (int i = 0; i < n; i++)
        {
            if (i == current)
            {
                printf("%s", "  ---->  ");
            }
            else
            {
                printf("         ");
            }
            printf("%d %s", i + 1, "  ");
            printf("%s ", Meniu[i]);
            printf("\n");
        }

        ch = getch();
        char *Meniu[] = {"Cautare","Iesire"};
        if (ch == 0)
        {
            ch = getch();
            vezi_video(canal,clip_nr);
            if (ch == 80)
            {
                current++;
                if (current == n)
                {
                    current = 0;
                }
            }
            else if (ch == 72)
            {
                current--;
                if (current == -1)
                {
                    current = n - 1;
                }
            }
        }
    }
    system("cls");
    return current;
}
void save_data(channel channel_array[], int n)
{
    ofstream g("files/saved_data.out");
    char backup[10000];
    strcpy(backup, "\0");
    strcat(backup, "ChName;Name;Date;Description;Duration");
    strcat(backup, "\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < channel_array[i].getClipsNumber(); j++)
        {
            strcat(backup, channel_array[i].getName());
            strcat(backup, ";");
            strcat(backup, channel_array[i].clips[j].getName());
            strcat(backup, ";");
            strcat(backup, channel_array[i].clips[j].getUpload());
            strcat(backup, ";");
            strcat(backup, channel_array[i].clips[j].getDescription());
            strcat(backup, ";");
            strcat(backup, channel_array[i].clips[j].getDuration());
        }
    }

    g << backup;
    g.close();
}
char* upper(char nume[])
{

    for(int i=0; i<strlen(nume); i++)
        nume[i]=toupper(nume[i]);
    return nume;
}
void cautare(int clip_number,channel ch[])
{
    cout<<"Introduceti un cuvant cheie:"<<endl;
    char key[20];
    cin.get(key,20);
    for(int i=0; i<clip_number; i++)
    {
        for(int j=0; j<ch[i].getClipsNumber(); j++)
            if(strstr((upper(ch[i].clips[j].getName())),(upper(key)))!=0)
                cout<<ch[i].clips[j];
    }
}
void vezi_channel(int number,channel ch[])
{
    system("cls");
    char *nume[number];
    for(int i=0; i<number; i++)
        nume[i]=new char[100];
    for(int i=0; i<number; i++)
    {
        strcpy(nume[i],ch[i].getName());
    }
    int current=cursor_meniu(number,nume);
    system("cls");
    cout<<ch[current];

}
void stegere_video(int number,channel ch[])
{
    ofstream g("files/all_videos.csv");
    char backup[10000];
    system("cls");
    char *nume[1000];
    for(int i=0; i<1000; i++)
        nume[i]=new char[100];
    int k=0;
    for(int i=0; i<number; i++)
    {
        cout<<ch[i].getName()<<":"<<endl;
        for(int j=0; j<ch[i].clipsNumber; j++)
        {
            strcpy(nume[k++],ch[i].clips[j].getName());
        }
    }
    cout<<"Ce videoclip doriti sa stegeti:"<<endl;
    int current=cursor_meniu(k,nume);
    strcpy(backup, "\0");
    strcat(backup, "ChName;Name;Date;Description;Duration");
    strcat(backup, "\n");
    for(int i = 0; i < number; i++)
    {
        for(int j = 0; j < ch[i].getClipsNumber(); j++)
        {
            if(strcmp(ch[i].clips[j].getName(),nume[current])!=0)
            {
                strcat(backup, ch[i].getName());
                strcat(backup, ";");
                strcat(backup, ch[i].clips[j].getName());
                strcat(backup, ";");
                strcat(backup, ch[i].clips[j].getUpload());
                strcat(backup, ";");
                strcat(backup, ch[i].clips[j].getDescription());
                strcat(backup, ";");
                if(i==number-1 && j==ch[i].getClipsNumber()-1)
                    strcat(backup, ch[i].clips[j].getDuration());
                else
                {
                    strcat(backup, ch[i].clips[j].getDuration());
                    strcat(backup,"\n");
                }
            }
        }

    }
    g<<backup;
    g.close();
}
void adaugare_video()
{
    system("cls");
    char text[100]= {'\0'};
    char temp[100]= {'\0'};
    cout<<"Canal:"<<endl;
    cin.get(temp,100);
    strcat(text,temp);
    strcat(text,";");
    cin.get();
    cout<<"Nume videoclip:"<<endl;
    cin.get(temp,100);
    strcat(text,temp);
    strcat(text,";");
    cin.get();
    cout<<"Data incarcarii:"<<endl;
    cin.get(temp,100);
    strcat(text,temp);
    strcat(text,";");
    cin.get();

    cout<<"Descriere:"<<endl;
    cin.get(temp,100);
    strcat(text,temp);
    strcat(text,";");
    cin.get();

    cout<<"Durata videoclipului:"<<endl;
    cin.get(temp,100);
    strcat(text,temp);
    ofstream ofs;
    ofs.open ("files/all_videos.csv", ofstream::out | ofstream::app);
    ofs<<endl<<text;
    ofs.close();

}
void adaugare_canal(int number)
{
    system("cls");
    ofstream g("files/nr_canale.in");
    number++;
    g<<number;
    cout<<"Introduceti numele canalului:"<<endl;
    char nume[100];
    cin.get(nume,100);
    g.close();
    ofstream ofs;
    ofs.open ("files/Canale.in", ofstream::out | ofstream::app);
    ofs<<endl<<nume;
    ofs.close();
}
void stergere_canale(int number,channel ch[])
{

    cout<<"Ce canal doriti sa stergeti:"<<endl;
    char *nume[number];
    char canale[1000]= {'\0'};
    for(int i=0; i<number; i++)
        nume[i]=new char[100];
    for(int i=0; i<number; i++)
    {
        strcpy(nume[i],ch[i].getName());
    }
    int current=cursor_meniu(number,nume);
    for(int i=0; i<number; i++)
    {
        if(strcmp(ch[i].getName(),nume[current])!=0)
        {
            strcat(canale,nume[i]);
            strcat(canale,"\n");
        }
    }
    strncpy(canale, canale, strlen(canale) - 1);
    number--;
    ofstream g("files/nr_canale.in");
    g<<number;
    g.close();
    ofstream f("files/Canale.in");
    f<<canale;
    f.close();
    ofstream c("files/all_videos.csv");
    strcpy(canale,"\0");
    strcat(canale, "ChName;Name;Date;Description;Duration");
    strcat(canale, "\n");
    for(int i=0; i<number+1; i++)
    {
        if(strcmp(ch[i].getName(),ch[current].getName())!=0)
        {
            for(int j=0; j<ch[i].clipsNumber; j++)
            {

                    strcat(canale, ch[i].getName());
                    strcat(canale, ";");
                    strcat(canale, ch[i].clips[j].getName());
                    strcat(canale, ";");
                    strcat(canale, ch[i].clips[j].getUpload());
                    strcat(canale, ";");
                    strcat(canale, ch[i].clips[j].getDescription());
                    strcat(canale, ";");
                    strcat(canale, ch[i].clips[j].getDuration());
                    strcat(canale,"\n");
            }
        }
    }
    strncpy(canale, canale, strlen(canale) - 1);
    c << canale;
}
void functie(int clip_nr,channel ch[])
{
    while(1)
    {
        char *Meniu[] = {"Vizualizare videoclipuri", "Vizualizare canale","Adaugare videoclip","Stergere videoclip","Adaugare canal","Stergere canal","Inchide"};
        int current=cursor_meniu(7,Meniu);
        switch(current)
        {
        case 0:
        {
            vezi_video(ch, clip_nr);
            char *meniu2[]= {"Cautare","Iesire"};
            // system("pause");

            int current2=cursor(2,meniu2,ch,clip_nr);
            if(current2==0)
            {
                cautare(clip_nr,ch);
                system("pause");
                current2=-1;
            }
            else if(current2==1)
            {
                functie(clip_nr,ch);
                current2=-1;
            }

            break;
        }
        case 1:
        {
            vezi_channel(clip_nr,ch);
            system("pause");
            break;
        }
        case 2:
        {
            adaugare_video();
            return;
        }
        case 3:
        {
            stegere_video(clip_nr,ch);
            return;
        }
        case 4:
        {
            adaugare_canal(clip_nr);
            return ;
        }
        case 5:
        {
            stergere_canale(clip_nr,ch);
            return;
        }
        case 6:
        {
            exit(0);
        }
        }
    }
}
int main()
{
    ifstream f1("files/nr_canale.in");
    int clip_nr;
    f1 >> clip_nr;
    f1.close();
    channel *ch = new channel[clip_nr];
    read_channel(ch, clip_nr);
    read_videos(ch, clip_nr);
    functie(clip_nr,ch);
    return 0;
}
