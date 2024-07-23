#include "Classes.h"



Activity::Activity()
{
    type = -1;
    value = "";
}

void Activity::setDetail(int t, string v)
{
    type = t;
    value = v;
}

void Activity::print()
{
    switch (type)
    {
    case 1:
        cout << " is feeling" << value << endl;
        break;
    case 2:
        cout << " is thinking about" << value << endl;
        break;
    case 3:
        cout << " is making" << value << endl;
        break;
    case 4:
        cout << " is celebrating" << value << endl;
    default:
        break;
    }
}



Date::Date()
{
    day = 1;
    month = 1;
    year = 1;
}

void Date::setDate(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

string Date::getDate()
{
    string ret = to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    return ret;
}

string Date::DateCompare(Date* d)
{
    time_t now = time(nullptr); // Get the current time in seconds since the epoch
    struct tm t;
    localtime_s(&t, &now); // Convert to local time


    int y = 1900 + t.tm_year;

    int diff = y - d->year;

    string ret = to_string(diff) + " years ago";

    return ret;

}

Comment::Comment()
{
    ID = "";
    text = "";
    author = 0;
}

void Comment::setDetails(string id, string t, Object* a)
{
    ID = id;
    text = t;
    author = a;
}

void Comment::displayComment()
{
    cout << "\t\t";
    author->displayDetails();
    cout << " wrote: " << '"' << text << '"' << endl;

}



Post::Post()
{
    ID = "";
    text = "";
    postActivity = 0;
}

string Post::getID()
{
    return ID;
}

void Post::LoadPost(ifstream& fin)
{
    int d;
    int m;
    int y;

    fin >> ID;
    fin >> d;
    fin >> m;
    fin >> y;

    datePosted.setDate(d, m, y);

    string s, t;
    fin >> s;
    getline(fin, t);
    text = s + t;
}

void Post::addLikes(Object* add)
{
    likedBy.push_back(add);
}

void Post::addComment(Comment* add)
{
    comments.push_back(add);
}

void Post::addActivity(Activity* add)
{
    postActivity = add;
}

void Post::showLikes()
{
    for (auto ptr : likedBy)
    {
        cout << "\t";
        ptr->displayDetails();
        cout << endl;
    }
}

void Post::showComments()
{
    for (auto ptr : comments)
    {
        ptr->displayComment();
    }
}

void Post::displayActivity()
{
    if (postActivity)
    {
        postActivity->print();
    }
}

void Post::display()
{
    if (postActivity)
    {
        postActivity->print();
        cout << "\t" << '"' << text << '"' << " (" << datePosted.getDate() << ")" << endl;
        showComments();
    }
    else
    {
        cout << " shared " << '"' << text << '"' << " (" << datePosted.getDate() << ")" << endl;
        showComments();
    }
}

string Post::getText()
{
    return text;
}

bool Post::alreadyLike(string ID)
{
    for (auto ptr : likedBy)
    {
        if (ptr->getID() == ID)
        {
            return true;
        }
    }

    return false;
}

Date* Post::getDate()
{
    return &datePosted;
}

Post::~Post()
{
    for (auto ptr : comments)
    {
        delete ptr;
    }

    if (postActivity)
    {
        delete postActivity;
    }
}



void Memory::shareMemory(Post* add)
{
    originalPost = add;
}

void Memory::display()
{
    Date* d = new Date;
    cout << " shared a memory\n";
    string text = d->DateCompare(originalPost->getDate());
    cout << "\t(" << text << ")" << endl;

    d = originalPost->getDate();

    cout << "\t" << '"' << originalPost->getText() << '"' << " (" << d->getDate() << ") " << endl;
}



Page::Page()
{
    ID = "";
    title = "";
    postCount = 0;
}

void Page::LoadPage(ifstream& fin)
{
    fin >> ID;
    string s, n;
    fin >> s;
    getline(fin, n);
    title = s + n;
}

string Page::getID()
{
    return ID;
}

string Page::getTitle()
{
    return title;
}

void Page::addTimeline(Post* add)
{
    Posts.push_back(add);
}

void Page::displayDetails()
{
    cout << ID << " - " << title;
}

void Page::viewPosts()
{
    for (auto ptr : Posts)
    {
        cout << ptr->getID() << "----" << Page::title;
        ptr->display();
        cout << "\n\n";
    }
}

Post* Page::searchPosts(string ID)
{
    for (auto ptr : Posts)
    {
        if (ptr->getID() == ID)
        {
            return ptr;
        }
    }

    return 0;
}

Page::~Page()
{
    for (auto ptr : Posts)
    {
        delete ptr;
    }
}



User::User()
{
    ID = "";
    fname = "";
    lname = "";

    friendCount = 0;

    pageCount = 0;

}

void User::LoadUser(ifstream& fin) {
    fin >> ID;
    fin >> fname;
    fin >> lname;
}

void User::setFriendCount(int n) {
    friendCount = n;
}

void User::addFriend(User* friendPtr) {
    friends.push_back(friendPtr); // Add a friend pointer to the vector
}

void User::setPageCount(int n)
{
    pageCount = n;
}

void User::addPage(Page* ptr)
{
    likedPages.push_back(ptr);
}

void User::addTimeline(Post* add)
{
    timeline.push_back(add);
}

void User::addMemory(Memory* add)
{
    mem.push_back(add);
}

void User::shareMemory(string ID)
{
    for (auto ptr : timeline)
    {
        if (ptr->getID() == ID)
        {
            Memory* m = new Memory;
            m->shareMemory(ptr);
            User::addMemory(m);
            cout << "Memory successfully shared!\n";
            return;
        }
    }

    cout << "POST NOT FOUND!\n";
}

void User::displayDetails()
{
    cout << ID << " - " << fname + " " + lname;
}

void User::addComment(string postID)
{
    Post* ret = 0;

    for (auto ptr : friends)
    {
        ret = ptr->searchTimeline(postID);

        if (ret)
        {

            srand((unsigned)time(NULL));
            int random = 13 + (rand() % 100);

            string text;

            Comment* c = new Comment;

            cout << "Enter comment: ";
            cin.ignore();
            getline(cin, text);

            string Cid = "c" + to_string(random);

            c->setDetails(Cid, text, this);

            ret->addComment(c);
            cout << "COMMENT ADDED\n";
            return;
        }
    }

    for (auto ptr : likedPages)
    {
        ret = ptr->searchPosts(postID);

        if (ret)
        {

            srand((unsigned)time(NULL));
            int random = 13 + (rand() % 100);

            string text;

            Comment* c = new Comment;

            cout << "Enter comment: ";
            cin.ignore();
            getline(cin, text);

            string Cid = "c" + to_string(random);

            c->setDetails(Cid, text, this);

            ret->addComment(c);
            cout << "COMMENT ADDED\n";
            return;
        }

    }
    cout << "Error! Post not found!\n";

}

void User::addLike(string postID)
{
    Post* ret = 0;

    for (auto ptr : friends)
    {
        ret = ptr->searchTimeline(postID);

        if (ret)
        {
            bool check = ret->alreadyLike(this->getID());

            if (check)
            {
                cout << "Already Liked\n";
                return;
            }
        }

        if (ret)
        {

            ret->addLikes(this);
            cout << "POST LIKED\n";
            return;
        }
    }

    for (auto ptr : likedPages)
    {
        ret = ptr->searchPosts(postID);

        if (ret)
        {
            bool check = ret->alreadyLike(this->getID());

            if (check)
            {
                cout << "Already Liked\n";
                return;
            }
        }

        if (ret)
        {
            ret->addLikes(this);
            cout << "POST LIKED\n";
            return;
        }
    }
    cout << "Error! Post not found!\n";
}

Post* User::searchTimeline(string ID)
{
    for (auto ptr : timeline)
    {
        if (ptr->getID() == ID)
        {
            return ptr;
        }
    }

    return 0;

}

string User::getName()
{
    return fname + " " + lname;
}

string User::getID()
{
    return ID;
}

void User::displayFriends()
{
    for (auto ptr : friends)
    {
        cout << ptr->getID() << " - " << ptr->getName() << endl;
    }
}

void User::viewPosts()
{
    for (auto ptr : timeline)
    {
        cout << ptr->getID() << "----" << User::getName();
        ptr->display();
        cout << "\n\n";
    }
}

void User::viewSpecificPost(string ID)
{
    Post* ret = 0;

    for (auto ptr : friends)
    {
        ret = ptr->searchTimeline(ID);

        if (ret)
        {
            cout << ret->getID() << "----" << ptr->getName();
            ret->display();
            return;
        }
    }

    for (auto ptr : likedPages)
    {
        ret = ptr->searchPosts(ID);

        if (ret)
        {
            cout << ret->getID() << "----" << ptr->getTitle();
            ret->display();
            return;
        }

    }
    cout << "Error! Post not found!\n";
}

void User::viewFeed()
{
    if (friends.size() == 0)
    {
        if (likedPages.size() == 0)
            cout << "NOTHING TO SHOW!\n\n";
    }
    else
    {
        for (auto ptr : friends)
        {
            ptr->viewPosts();
        }

        for (auto ptr : likedPages)
        {
            ptr->viewPosts();
        }
    }
}

void User::viewTimeline()
{
    bool check = false;
    if (mem.size() != 0)
    {
        User::seeSharedMemory();
        cout << "\n\n";
        check = true;
    }
    if (timeline.size() != 0)
    {
        User::viewPosts();
        check = true;
    }

    if (!check)
    {
        cout << "NOTHING TO SHOW!\n\n";
    }
}

void User::seeSharedMemory()
{
    if (mem.size() == 0)
    {
        cout << "NO MEMORY SHARED\n";
    }
    for (auto ptr : mem)
    {
        cout << ptr->getID() << "----" << User::getName();
        ptr->display();
        // cout << "-----------------------------------------------------------\n";
    }
}

void User::displayLikedPages()
{
    for (auto ptr : likedPages)
    {
        ptr->displayDetails();
        cout << endl;
    }
}

User::~User()
{
    for (auto ptr : timeline)
    {
        delete ptr;
    }

    for (auto ptr : mem)
    {
        delete ptr;
    }
}




SocialNetwork::SocialNetwork()
{
    userCount = 0;
    pageCount = 0;
    curUser = "";
    controller = 0;
    postCount = 0;
}

void SocialNetwork::LoadUsers()
{
    ifstream fin("Users.txt");

    // Error handling
    if (!fin.is_open()) {
        cout << "FILE NOT FOUND!!! PROGRAM CRASHED" << endl;
        exit(1); // Returns a value of 1 indicating that an error must have occurred terminating the program
    }

    fin >> userCount; // Getting total number of users

    users.resize(userCount); // Resize the vector to hold userCount number of User pointers

    for (int i = 0; i < userCount; i++)
    {
        users[i] = new User;
        users[i]->LoadUser(fin);
    }

    fin.close(); // Close the file after reading
}

void SocialNetwork::LoadPages()
{
    ifstream fin("Pages.txt");

    // Error handling
    if (!fin.is_open()) {
        cout << "FILE NOT FOUND!!! PROGRAM CRASHED" << endl;
        exit(1); // Returns a value of 1 indicating that an error must have occurred terminating the program
    }

    fin >> pageCount;

    Pages.resize(pageCount);

    for (int i = 0; i < pageCount && !fin.eof(); i++)
    {
        Pages[i] = new Page;
        Pages[i]->LoadPage(fin);
    }
    fin.close();
}

User* SocialNetwork::searchUser(string id)
{
    for (int i = 0; i < userCount; i++)
    {
        //cout << users[i]->getID() << "  " << id << endl;
        if (users[i]->getID() == id)
        {
            return users[i];
        }
    }
    return 0;
}

Page* SocialNetwork::searchPage(string id)
{
    for (int i = 0; i < pageCount; i++)
    {
        if (Pages[i]->getID() == id)
        {
            return Pages[i];
        }
    }
    return 0;
}

void SocialNetwork::addFriendsAndPages()
{

    ifstream fin("Friends&PagesLiked.txt");

    // Error handling
    if (!fin.is_open()) {
        cout << "FILE NOT FOUND!!! PROGRAM CRASHED" << endl;
        exit(1); // Returns a value of 1 indicating that an error must have occurred terminating the program
    }

    string id = "";
    string curUser = "";

    for (int i = 0; i < userCount; i++)
    {
        fin >> curUser;

        fin >> id;

        while (id != "-1")
        {
            User* add = searchUser(id);

            if (add)
            {
                users[i]->addFriend(add);
            }

            fin >> id;
        }


        fin >> id;
        while (id != "-1")
        {
            Page* add = searchPage(id);

            if (add)
            {
                users[i]->addPage(add);
            }

            fin >> id;
        }
    }

    fin.close();
}

void SocialNetwork::displayFriends()
{
    cout << "----------------------------------------------" << controller->getName() << " Friends-----------------------------------------------\n";
    controller->displayFriends();
}

void SocialNetwork::addPosts()
{
    ifstream fin("Posts.txt");
    ifstream Com("Comments.txt");
    ifstream Act("Activity.txt");

    // Error handling
    if (!fin.is_open() && !Com.is_open() && !Act.is_open())
    {
        cout << "FILE NOT FOUND!!! PROGRAM CRASHED" << endl;
        exit(1); // Returns a value of 1 indicating that an error must have occurred terminating the program
    }

    int totalPosts;

    fin >> totalPosts;

    for (int i = 0;i < totalPosts;i++)
    {
        Post* p = new Post;

        Posts.push_back(p);

        p->LoadPost(fin);

        string sharedBy;
        fin >> sharedBy;

        Object* owner;

        if (sharedBy[0] == 'u')
        {
            owner = searchUser(sharedBy);
            owner->addTimeline(p);
        }
        else
        {
            owner = searchPage(sharedBy);
            owner->addTimeline(p);
        }


        string likedBy;
        fin >> likedBy;

        while (likedBy != "-1")
        {
            if (likedBy[0] == 'u')
            {
                p->addLikes(searchUser(likedBy));
            }
            else
            {
                p->addLikes(searchPage(likedBy));
            }
            fin >> likedBy;
        }

        //---------------------------------------Adding Comments-----------------------------------------
        string CurrentPost;
        int numComments;

        Com >> CurrentPost;
        Com >> numComments;

        for (int i = 0; i < numComments; i++)
        {
            string id;
            string text, s, t;
            string authorID;

            Com >> id;
            Com >> authorID;

            Com >> s;
            getline(Com, t);
            text = s + t;

            if (authorID[0] == 'u')
            {
                owner = searchUser(authorID);
            }
            else
            {
                owner = searchPage(authorID);
            }

            Comment* addCom = new Comment;

            addCom->setDetails(id, text, owner);
            p->addComment(addCom);

        }
        //-------------------------------------------------------------------------------------------

        int type;

        Act >> CurrentPost;

        Act >> type;

        if (type != -1)
        {
            string v;
            getline(Act, v);
            Activity* a = new Activity;

            a->setDetail(type, v);
            p->addActivity(a);
        }
    }
    fin.close();
    Com.close();
    Act.close();
}

Post* SocialNetwork::searchPost(string ID)
{
    for (auto ptr : Posts)
    {
        if (ID == ptr->getID())
        {
            return ptr;
        }
    }
    return 0;
}

void SocialNetwork::LoadProgram()
{
    LoadUsers();
    LoadPages();
    addFriendsAndPages();
    addPosts();

    //Hardcoding a memory
    ifstream fin("Memory.txt");
    Post* add = new Post;
    add->LoadPost(fin);
    Memory* m = new Memory;
    m->shareMemory(add);
    users[6]->addMemory(m);
    fin.close();

}

void SocialNetwork::viewFeed()
{
    cout << "----------------------------------------------" << controller->getName() << " Feed-----------------------------------------------\n";
    controller->viewFeed();
}

void SocialNetwork::likePost()
{
    string ID;
    cout << "Enter post ID: ";
    cin >> ID;

    controller->addLike(ID);
}

void SocialNetwork::commentPost()
{
    string ID;
    cout << "Enter ID of the post to comment on: ";
    cin >> ID;

    controller->addComment(ID);

}

void SocialNetwork::viewPost()
{
    string ID;
    cout << "Enter post ID: ";
    cin >> ID;

    controller->viewSpecificPost(ID);
}

void SocialNetwork::viewLikedList()
{
    string ID;
    cout << "Enter post ID: ";
    cin >> ID;

    Post* p = searchPost(ID);

    if (p)
    {
        cout << "Liked by:\n";
        p->showLikes();
    }
    else
    {
        cout << "ERROR! POST NOT FOUND!\n";
    }

}

void SocialNetwork::viewTimeline()
{
    cout << "----------------------------------------------" << controller->getName() << " Timeline-----------------------------------------------\n";
    controller->viewTimeline();
}

void SocialNetwork::viewPage()
{
    string ID;

    cout << "Enter page ID: ";
    cin >> ID;

    Page* p = searchPage(ID);

    if (p)
    {
        p->displayDetails();
        cout << endl;
        p->viewPosts();
    }
    else
    {
        cout << "PAGE NOT FOUND!\n";
    }
}

void SocialNetwork::seeSharedMemory()
{
    cout << "----------------------------------------------" << controller->getName() << " Memories-----------------------------------------------\n";
    controller->seeSharedMemory();
}

void SocialNetwork::shareMemory()
{
    string ID;
    cout << "Enter post ID: ";
    cin >> ID;

    controller->shareMemory(ID);
}

void SocialNetwork::setCurrentUser()
{
    
    if (controller)
    {
        cout << "\n\t\t" << controller->getName() << " Logged Out" << endl;
        cout << "-------------------------------------------------------------------------------------------------------\n";
    }

    cout << "Example ID: u000\n";
    cout << "Enter user ID: ";
    cin >> curUser;

    if (curUser == "-1")
    {
        cout << "Closing the program!!!\n";
        exit(1);
    }
    
    controller = searchUser(curUser);

    while (!controller)
    {
        cout << "ERROR!!! INVALID ENTRY!!!\n";

        cout << "Enter again: ";
        cin >> curUser;
        controller = searchUser(curUser);
    }

    cout << "\n\t\t" << controller->getName() << " Logged In" << endl;
    cout << "-------------------------------------------------------------------------------------------------------\n";

}

void SocialNetwork::displayPages()
{
    cout << "----------------------------------------------" << controller->getName() << " Liked Pages-----------------------------------------------\n";
    controller->displayLikedPages();
}

SocialNetwork::~SocialNetwork()
{
    for (auto ptr : users)
    {
        delete ptr;
    }

    for (auto ptr : Pages)
    {
        delete ptr;
    }
}
