#include "videos.h"
#include <string.h>
#include <iostream>

videos::videos(char name[], char upload[], char description[], char duration[], char channelName[])
{
    this -> name = new char[50];
    this -> upload = new char[25];
    this -> description = new char[1000];
    this -> duration = new char[7];
    this -> channelName = new char[25];
    strcpy(this -> name, name);
    strcpy(this -> upload, upload);
    strcpy(this -> description, description);
    strcpy(this -> duration, duration);
    strcpy(this -> channelName, channelName);
}

videos::videos()
{
    name = new char[50];
    upload = new char[25];
    description = new char[1000];
    duration = new char[7];
    channelName = new char[25];
}

videos::~videos()
{
    delete[] name;
    delete[] upload;
    delete[] description;
    delete[] duration;
}

std::ostream & operator << (std::ostream &st, const videos &x)
{
    st << "Name: " << x.name << std::endl;
    st << "Upload: " << x.upload << std::endl;
    st << "Description: " << x.description << std::endl;
    st << "Duration: " << x.duration << std::endl;
    st << std::endl;
    return st;
}

char* videos::getName()
{
    return this -> name;
}

char* videos::getUpload()
{
    return this -> upload;
}

char* videos::getDescription()
{
    return this -> description;
}

char* videos::getDuration()
{
    return this -> duration;
}

void videos::setName(char x[])
{
    strcpy(this -> name, x);
}

void videos::setUpload(char x[])
{
    strcpy(this -> upload, x);
}

void videos::setDescription(char x[])
{
    strcpy(this -> description, x);
}

void videos::setDuration(char x[])
{
    strncpy(this -> duration, x,strlen(x)-1);
}

channel::channel(int x,char nume[])
{
    this->name=new char[strlen(nume)+1];
    strcpy(this->name,nume);
    this -> clipsNumber = x;
    clips = new videos[x];
}

channel::~channel()
{
    delete[] clips;
}

channel::channel()
{
    this -> name = new char[500];
    clipsNumber = 0;
    clips = new videos[500];
}

void channel::show_channel()
{
    for(int i = 0; i < this -> clipsNumber; i++)
        std::cout << clips[i].getName() << std::endl;
}

void channel::setName(char x[])
{
    strcpy(this->name,x);
}

void channel::setClipsNumber()
{
    this -> clipsNumber += 1;
}

char* channel::getName()
{
    return name;
}

int channel::getClipsNumber()
{
    return clipsNumber;
}


std::ostream & operator << (std::ostream &st,  channel &x){
 for(int i=0;i<x.getClipsNumber();i++)
    st<< x.clips[i];
  return st;
}
