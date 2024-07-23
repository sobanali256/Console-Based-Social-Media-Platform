#pragma once
#include <iostream>
#include <vector>
#include <string>
#include<cstdlib>
#include <fstream>
using namespace std;

class User;
class Page;
class Post;
class Date;
class Object;
class Activity;
class Memory;


class Activity
{
private:
    int type;
    string value;

public:

    Activity();

    void setDetail(int t, string v);
    void print();
};

class Object
{
public:
    virtual void addTimeline(Post*) = 0;
    virtual void displayDetails() = 0;
    virtual string getID() = 0;
};

class Date
{
private:
    int day;
    int month;
    int year;

public:

    Date();

    void setDate(int d, int m, int y);

    string getDate();

    string DateCompare(Date* d);
};

class Comment
{
private:
    string ID;
    string text;
    Object* author;
public:

    Comment();

    void setDetails(string id, string t, Object* a);

    void displayComment();
};

class Post
{
private:
    string ID;
    string text;

    vector<Object*> likedBy;

    Date datePosted;
    vector<Comment*> comments;
    Activity* postActivity;

public:

    Post();

    string getID();

    void LoadPost(ifstream& fin);

    void addLikes(Object* add);

    void addComment(Comment* add);

    void addActivity(Activity* add);

    void showLikes();

    void showComments();

    void displayActivity();

    virtual void display();

    bool alreadyLike(string ID);

    string getText();

    Date* getDate();

    ~Post();

};

class Memory : public Post
{
private:
    Post* originalPost;

public:

    void shareMemory(Post* add);

    void display();
};

class Page : public Object
{
private:
    string ID;
    string title;

    vector<Post*> Posts;
    int postCount;

public:

    Page();

    void LoadPage(ifstream& fin);

    string getID();

    string getTitle();

    void addTimeline(Post* add);

    void displayDetails();

    void viewPosts();

    Post* searchPosts(string ID);

    ~Page();
};

class User : public Object
{
private:
    string ID;

    string fname;
    string lname;

    vector<User*> friends;
    int friendCount;

    vector<Page*> likedPages;
    int pageCount;

    vector<Post*> timeline;

    vector<Memory*> mem;

public:
    // Default Constructor
    User();

    // Setting details of User
    void LoadUser(ifstream& fin);

    //-------------------------------------------------------------------------------------------------------------------------

    //======================================Functions related to friends=======================================================

    //Setting count of number of friends
    void setFriendCount(int n);

    //Adding friends obj
    void addFriend(User* friendPtr);

    //-------------------------------------------------------------------------------------------------------------------------

    void setPageCount(int n);

    void addPage(Page* ptr);

    //-------------------------------------------------------------------------------------------------------------------------

    void addTimeline(Post* add);

    void addComment(string postID);

    void addLike(string postID);

    void addMemory(Memory* add);

    void displayDetails();

    void shareMemory(string ID);

    Post* searchTimeline(string ID);

    //-------------------------------------------------------------------------------------------------------------------------

    string getName();

    //Returning user ID
    string getID();

    void viewSpecificPost(string);

    void displayFriends();

    void viewPosts();

    void viewFeed();

    void viewTimeline();

    void seeSharedMemory();

    void displayLikedPages();
    //Destructor
    ~User();
};

class SocialNetwork
{
private:

    string curUser;
    User* controller;

    vector<User*> users; // Changed to vector of User pointers
    int userCount;

    vector<Page*> Pages;
    int pageCount;

    vector<Post*> Posts;
    int postCount;

public:

    // Default Constructor
    SocialNetwork();
    //----------------------------LOADING USERS---------------------------------------------------------------------
    void LoadUsers();
    //==============================================================================================================
    //----------------------------LOADING PAGES---------------------------------------------------------------------

    void LoadPages();

    //==============================================================================================================
    //----------------------------ADDING FRIENDS/LIKED PAGES--------------------------------------------------------

    //**************************************************************************************************************
    User* searchUser(string id);

    Page* searchPage(string id);
    //**************************************************************************************************************

    void addFriendsAndPages();

    //--------------------------------------------------------------------------------------------------------------
    void displayUser();

    void displayPage();

    void displayFriends();

    //--------------------------------------------------------------------------------------------------------------
    //==============================================================================================================
    //----------------------------ADDING POSTS----------------------------------------------------------------------
    void addPosts();

    Post* searchPost(string ID);
    //--------------------------------------------------------------------------------------------------------------
    //==============================================================================================================

    void LoadProgram();

    //--------------------------------------------------------------------------------------------------------------
    //==============================================================================================================
    void viewFeed();

    void likePost();

    void commentPost();

    void viewPost();

    void shareMemory();

    void viewLikedList();

    void viewTimeline();

    void viewPage();

    void seeSharedMemory();

    void setCurrentUser();

    void displayPages();

    //--------------------------------------------------------------------------------------------------------------
    //==============================================================================================================

    ~SocialNetwork();

};
