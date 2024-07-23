#include "Classes.h"

int main() {
    SocialNetwork s;
    s.LoadProgram();

    cout << "WELCOME TO WANNA BE BOOK\n";
    cout << "AT ANY INSTANCE YOU WANT TO EXIST ENTER -1\n";

    cout << "\nCOMMAND LIST IS AS PROVIDED\n";
    cout << "\t1)\tView Feed\n";
    cout << "\t2)\tView Timeline\n";
    cout << "\t3)\tView Post\n";
    cout << "\t4)\tView Post likes\n";
    cout << "\t5)\tAdd Comment\n";
    cout << "\t6)\tAdd Like\n";
    cout << "\t7)\tView FriendList\n";
    cout << "\t8)\tView Liked Pages\n";
    cout << "\t9)\tView Memories\n";
    cout << "\t10)\tShare Memory\n";
    cout << "\t11)\tView Page\n";
    cout << "\t12)\tChange User\n";

    cout << "---------------------------------------------------------\n";

    int choice = 0;

    s.setCurrentUser();

    while (choice != -1)
    {
        cout << "Enter command: ";
        cin >> choice;
         cout << "\n\n";
        switch (choice)
        {
        case 1:
            s.viewFeed();
            cout << "---------------------------------------------------------\n";
            break;
        case 2:
            s.viewTimeline();
            cout << "---------------------------------------------------------\n";
            break;
        case 3:
            s.viewPost();
            cout << "---------------------------------------------------------\n";
            break;
        case 4:
            s.viewLikedList();
            cout << "---------------------------------------------------------\n";
            break;
        case 5:
            s.commentPost();
            cout << "---------------------------------------------------------\n";
            break;
        case 6:
            s.likePost();
            cout << "---------------------------------------------------------\n";
            break;
        case 7:
            s.displayFriends();
            cout << "---------------------------------------------------------\n";
            break;
        case 8:
            s.displayPages();
            cout << "---------------------------------------------------------\n";
            break;
        case 9:
            s.seeSharedMemory();
            cout << "---------------------------------------------------------\n";
            break;
        case 10:
            s.shareMemory();
            cout << "---------------------------------------------------------\n";
            break;
        case 11:
            s.viewPage();
            cout << "---------------------------------------------------------\n";
            break;
        case 12:
            s.setCurrentUser();
            break;
        case -1:
            break;
        default:
            cout << "Error!\n";
            cout << "---------------------------------------------------------\n";
            break;
        }

        cout << "\nCOMMAND LIST IS AS PROVIDED\n";
        cout << "\t1)\tView Feed\n";
        cout << "\t2)\tView Timeline\n";
        cout << "\t3)\tView Post\n";
        cout << "\t4)\tView Post likes\n";
        cout << "\t5)\tAdd Comment\n";
        cout << "\t6)\tAdd Like\n";
        cout << "\t7)\tView FriendList\n";
        cout << "\t8)\tView Liked Pages\n";
        cout << "\t9)\tView Memories\n";
        cout << "\t10)\tShare Memory\n";
        cout << "\t11)\tView Page\n";
        cout << "\t12)\tChange User\n";

        cout << "---------------------------------------------------------\n";
    }


    return 0;
}
