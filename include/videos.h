#ifndef VIDEOS_H
#define VIDEOS_H
#include <string.h>
#include <iostream>

class videos
{
public:
    videos();
    videos(char name[], char upload[], char description[], char duration[], char channelName[]);
    virtual ~videos();
    friend std::ostream & operator << (std::ostream &, const videos &);
    char* getName();
    char* getUpload();
    char* getDescription();
    char* getDuration();
    void setName(char x[]);
    void setUpload(char x[]);
    void setDescription(char x[]);
    void setDuration(char x[]);
private:
    char *name, *upload, *description, *duration, *channelName;
};

class channel
{
public:
    channel(int x,char nume[]);
    channel();
    virtual ~channel();
    void show_channel();
    void setName(char x[]);
    void setClipsNumber();
    char* getName();
    int getClipsNumber();
    friend void read_videos(channel channel_array[], int n);
    friend void save_data(channel channel_array[], int n);
    void read(int x);
    friend std::ostream & operator << (std::ostream &,  channel&);
    friend void cautare(int,channel ch[]);
    friend void vezi_channel(int,channel ch[]);
    friend void stegere_video(int,channel ch[]);
    friend void stergere_canale(int,channel ch[]);
private:
    videos *clips;
    int clipsNumber;
    char *name;
};

#endif
