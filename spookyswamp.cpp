#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <string>
#include <fstream>
using namespace std;


class item{
    private:
        string type;
        int value;
    public:

        item(){
            type = "nothing";
            value = 0;
        }

        item(string x, int y){
            type = x;
            value = y;
        }

        void setType(string x){
            type = x;
        }

        void setValue(int y){
            value = y;
        }

        string getType(){
            return type;
        }

        int getValue(){
            return value;
        }

        void printItem(){
            cout << "A " << type << " with a value of " << value << "." << endl;
        }

};

struct Node{
    item data;
    Node* next;

    Node(item x){
        data = x;
        next = nullptr;
    }
};

class inventory{
    private:
        
    public:
        Node* top;
        inventory(){
            top = nullptr;
        }

        void addItem(item x){
            Node* newNode = new Node(x);
            newNode->next = top;
            top = newNode;
        }

        bool removeItem(){
            if(top == nullptr){
                cout << "Inventory is empty" << endl;
                return false;
            }
            Node* temp = top;
            top = top->next;
            delete temp;
            return true;
        }

        //add peek here
        item peekItem(){
            if(top == nullptr){
                cout << "Inventory is empty." << endl;
                item tempitem;
                return tempitem;
            }
            return top->data;
        }

        void printInventory(){
            if(top == nullptr){
                cout << "Your inventory is empty." << endl;
                return;
            }

            Node* temp = top;
            cout << "Inventory:" << endl;
            while(temp != nullptr){
                temp->data.printItem();
                temp = temp->next;
            }
        }

        ~inventory(){
            Node* current = top;
            while(current != nullptr){
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }
};

class player{
    private:
        int health;
        int gold;
        string name;
    public:
        inventory inv;

        player(){
            health = 100;
            gold = 20;
            name = "x";
        }

        void setGold(int g){
            gold = g;
        }

        void setHealth(int h){
            health = h;
        }

        void setName(string x){
            name = x;
        }

        int getGold(){
            return gold;
        }

        int getHealth(){
            return health;
        }

        string getName(){
            return name;
        }

        void addInv(item toadd){
            inv.addItem(toadd);
        }

        void printInv(){
            inv.printInventory();
        }

};

class monster{
    private:
        int health;
        int level;
        string name;
    public:
        monster(){
            health = 0;
            level = 0; 
            name = "nothing";
        }

        void makeGhost(){
            health = 15;
            level = 1;
            name = "Ghost";
        }

        void makeWerewolf(){
            health = 20;
            level = 2;
            name = "Werewolf";
        }

        void makeGhoul(){
            health = 30;
            level = 3;
            name = "Ghoul";
        }

        void makeVampire(){
            health = 40;
            level = 4;
            name = "Vampire";
        }

        void setName(string x){
            name = x;
        }

        void setLevel(int x){
            level = x;
        }

        void setHealth(int x){
            health = x;
        }

        string getName(){
            return name;
        }

        int getLevel(){
            return level;
        }

        int getHealth(){
            return health;
        }
};

struct QueueNode{
    monster mon;
    QueueNode* next;

    QueueNode(monster x){
        mon = x;
        next = nullptr;
    }
};

class MonsterQueue{
    private:

    public:

        QueueNode* front;
        QueueNode* rear;

        MonsterQueue(){
            front = nullptr;
            rear = nullptr;
        }

        bool isEmpty(){
            return front == nullptr;
        }

        void enqueue(monster x){
            QueueNode* newNode = new QueueNode(x);
            if(isEmpty()){
                front = rear = newNode;
            }else{
                rear->next = newNode;
                rear = newNode;
            }
        }

        monster dequeue(){
            if(isEmpty()){
                cout << "MonsterQueue is empty." << endl;
                monster tempMonster;
                return tempMonster;
            }

            QueueNode* temp = front;
            monster x = front->mon;
            front = front->next;

            if(front == nullptr){
                rear = nullptr;
            }
            delete temp;
            return x;
        }

        monster peek(){
            if(isEmpty()){
                cout << "MonsterQueue is empty." << endl;
                monster tempmonster;
                return tempmonster;
            }
            return front->mon;
        }

        void printQueue(){
            if(isEmpty()){
                cout << "MonsterQueue is empty." << endl;
                return;
            }
            QueueNode* current = front;
            while (current != nullptr){
                cout << current->mon.getName() << "->";
                current = current->next;
            }
            cout << "NULL" << endl;
        }

        void populateQueue(){

            for(int i = 0; i < 30; i++){
                int monnum = rand() % 100 + 1;
                monster temp;

                if(monnum >= 1 && monnum <= 40){
                    temp.makeGhost();
                }
                if(monnum > 40 && monnum <= 65){ 
                    temp.makeWerewolf();
                }
                if(monnum > 65 && monnum <= 85){
                    temp.makeGhoul();
                }
                if(monnum > 85 && monnum <= 100){
                    temp.makeVampire();
                }

                enqueue(temp);
            }
        }

        ~MonsterQueue(){
            while(!isEmpty()){
                dequeue();
            }
        }
};

class board{ 
    private:
        static const int cols = 10;
        static const int rows = 10;

    public:
        char array[rows][cols];
        char shownarray[rows][cols];

        void placeTile(char tiletype){
            int randrow;
            int randcol;
            do{
                randrow = rand() % rows;
                randcol = rand() % cols;
            } while (array[randrow][randcol] != '~');
            array[randrow][randcol] = tiletype;
        } 

        board(){
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    shownarray[i][j] = '~';
                    array[i][j] = '~';
                }
            }
        }

        void printBoard(){
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    cout << shownarray[i][j] << "  ";
                }
                cout << endl;
            }
        }

        void populateBoard(){

            for(int i = 0; i < 30; i++){
                placeTile('c');
            }

            for(int i = 0; i < 20; i++){
                placeTile('r');
            }

            for(int i = 0; i < 1; i++){
                placeTile('x');
            }

            array[0][0] = '%';
            shownarray[0][0] = '%';
        }

        //got moveplayer function from chatgpt
        void movePlayer(int movement, player& p1, MonsterQueue& Mqueue) {
            // Find the player's position represented by '%'
            int playerRow = -1;
            int playerCol = -1;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (array[i][j] == '%') {
                        playerRow = i;
                        playerCol = j;
                        break; // Exit inner loop once player is found
                    }
                }
                if (playerRow != -1) break; // Exit outer loop if player is found
            }

            // Check if the player was found
            if (playerRow == -1) {
                cout << "Player not on board, try again." << endl;
                return;
            }

            // Define movement directions (row offset, column offset)
            const int directions[8][2] = {
                {-1, -1}, // Move 1 (diagonal up-left)
                {-1, 0},  // Move 2 (up)
                {-1, 1},  // Move 3 (diagonal up-right)
                {0, -1},  // Move 4 (left)
                {0, 1},   // Move 5 (right)
                {1, -1},  // Move 6 (diagonal down-left)
                {1, 0},   // Move 7 (down)
                {1, 1}    // Move 8 (diagonal down-right)
            };

            // Determine the direction based on movement
            if (movement < 1 || movement > 8) {
                cout << "Invalid movement direction." << endl;
                return;
            }

            int newRow = playerRow + directions[movement - 1][0];
            int newCol = playerCol + directions[movement - 1][1];

            // Check for out-of-bounds
            if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols) {
                cout << "Can't move there, out of bounds." << endl;
                return;
            }


            // Check if the destination tile is empty
            if (array[newRow][newCol] == '~') {
                array[newRow][newCol] = '%'; // Move player to new position
                array[playerRow][playerCol] = '~'; // Clear old position
                shownarray[newRow][newCol] = '%';
                shownarray[playerRow][playerCol] = '~';
            } 
            if (array[newRow][newCol] == 'c'){
                monster mon = Mqueue.dequeue();
                cout << "Oh no, you ran into a " << mon.getName() << "! Entering combat." << endl;
                while(true){
                    cout << "What do you want to do?" << endl;
                    cout << "1. Fight." << endl;
                    cout << "2. Intimidate." << endl;
                    int option;
                    cin >> option;
                    if(option == 1){
                        //FIXME if player inventory has an extra die add more damage
                        int roll = rand() % 20 + 1;
                        int newhp;
                        int currhp = mon.getHealth();
                        newhp = currhp - roll;
                        mon.setHealth(newhp);
                        cout << "Rolling dice..." << endl;
                        cout << "You rolled a "<< roll << "." << endl;
                    }
                    if(option == 2){
                        int runchance = rand() % 3 + 1;
                        if(runchance == 1){
                            cout << "Success! The monster runs away." << endl;
                            break;
                        }else{
                            cout << "The monster isn't effected..." << endl;
                        }
                    }
                    if(option > 2 && option < 1){
                        cout << "Not an option.";
                    }
                    int monroll;
                    if(mon.getLevel() == 1){
                        monroll = rand() % 5 + 1;
                    }
                    if(mon.getLevel() == 2){
                        monroll = rand() % 6 + 5;
                    }
                    if(mon.getLevel() == 3){
                        monroll = rand() % 11 + 5;
                    }
                    if(mon.getLevel() == 4){
                        monroll = rand() % 16 + 10;
                    }
                    cout << "Rolling dice..." << endl;
                    cout << "The monster got a "<< monroll << "." << endl;
                    int newhp;
                    int currhp = p1.getHealth();
                    newhp = currhp - monroll;
                    p1.setHealth(newhp);
                    cout << "You're hp is now: " << p1.getHealth() << endl;
                    if(mon.getHealth() <= 0){
                        cout << "The monster died, good job!" << endl;
                        break;
                    }
                    if(p1.getHealth() <= 0){
                        cout << "You died..." << endl;
                        break;
                    }
                }
                array[newRow][newCol] = '%'; // Move player to new position
                array[playerRow][playerCol] = '~'; // Clear old position
                shownarray[newRow][newCol] = '%';
                shownarray[playerRow][playerCol] = '~';
            }
            if (array[newRow][newCol] == 'r'){
                //fill in
                item itemOptions[4];
                item op0 = item("Potion", 20); 
                item op1 = item("Die", 5);
                item op2 = item("Bag of Gold", 20);
                item op3 = item("Loaf of bread", 20);
                itemOptions[0] = op0;
                itemOptions[1] = op1;
                itemOptions[2] = op2;
                itemOptions[3] = op3;

                int itemSelect = rand() % 4; //random number 0-3
         
                cout << "It looks like you found " << itemOptions[itemSelect].getType() << endl;
                cout << "Look in your inventory to learn more." << endl;
                p1.addInv(itemOptions[itemSelect]);

                array[newRow][newCol] = '%'; // Move player to new position
                array[playerRow][playerCol] = '~'; // Clear old position
                shownarray[newRow][newCol] = '%';
                shownarray[playerRow][playerCol] = '~';
            }
            if (array[newRow][newCol] == 'x'){ 
            
                cout << "You won the game!" << endl;
                cout << "Thank you for playing!" << endl;
                exit(0);
            }
        }
};

void saveGame(const string& filename, board& btosave, player& ptosave, MonsterQueue& mqtosave){
    ofstream outFile(filename);

    if(!outFile){
        cout << "Cannot save file..." << endl;
        return;
    }

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            outFile << btosave.array[i][j];
        }
        outFile << "\n";
    }

    outFile << ptosave.getHealth() << "\n";
    outFile << ptosave.getGold() << "\n";
    outFile << ptosave.getName() << "\n";

    Node* current = ptosave.inv.top;
    int inventorysize = 0;
    while(current != nullptr){
        inventorysize++;
        current = current->next;
    }
    outFile << inventorysize << "\n";
    current = ptosave.inv.top;

    while(current != nullptr){
        outFile << current->data.getType() << " " << current->data.getValue() << '\n';
        current = current->next;
    }

    QueueNode* queueCurrent = mqtosave.front;
    int monstercount = 0;

    while(queueCurrent != nullptr){
        monstercount++;
        queueCurrent = queueCurrent->next;
    }
    outFile << monstercount << '\n';
    queueCurrent = mqtosave.front;
    while(queueCurrent != nullptr){
        outFile << queueCurrent->mon.getName() << " " << queueCurrent->mon.getHealth() << " " << queueCurrent->mon.getLevel() << "\n";
        queueCurrent = queueCurrent->next;
    }

    outFile.close();
    cout << "Game Saved." << endl;
}

void loadGame(const string& filename, board& btosave, player& ptosave, MonsterQueue& mqtosave){
    ifstream inFile(filename);

    if(!inFile){
        cout << "Cannot load file..." << endl;
        return;
    }

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            inFile >> btosave.array[i][j];
        }
    }
    int health, gold;
    string name;
    inFile >> health;
    inFile >> gold; 
    inFile >> name;

    ptosave.setHealth(health);
    ptosave.setGold(gold);
    ptosave.setName(name);

    int inventorysize;
    inFile >> inventorysize;

    for(int i = 0; i < inventorysize; i++){
        string itemtype;
        int itemval;
        inFile >> itemtype >> itemval;
        item newitem(itemtype, itemval);
        ptosave.addInv(newitem);
    }

    int monstercount;
    inFile >> monstercount;
    
    for(int i = 0; i < monstercount; i++){
        string monname;
        int monhealth, monlevel;
        inFile >> monname >> monhealth >> monlevel;
        monster newmon;
        newmon.setName(monname);
        newmon.setHealth(monhealth);
        newmon.setLevel(monlevel);
        mqtosave.enqueue(newmon);
    }

    inFile.close();
    cout << "Game Loaded." << endl;
}

int main() {
    //write while loop to continuously run game
    cout << "------------ Welcome to Spooky Swamp! ------------" << endl;
    cout << "Here's how to play:" << endl;
    cout << "You start in the top left corner of the map which is a" << endl;
    cout << "10x10 board. You're goal is to find the treasure and " << endl;
    cout << "survive! You can move up, down, left, right, and diagonally" << endl;
    cout << "in all directions once. There are three types of squares" << endl;
    cout << "within the game: neutral(~), combat(c), and resource tiles(r)." << endl;
    cout << "There are multiple different resources and monster types" << endl;
    cout << "within the game so be careful!" << endl;
    cout << "Good luck." << endl;
    cout << endl;

    board gameboard;
    gameboard.populateBoard();

    MonsterQueue Mqueue;
    Mqueue.populateQueue();

    player p1; 
    p1.setName("p1"); 

    while (true){
        cout << "--------- What would you like to do? ---------" << endl;
        cout << "1. Move to another tile." << endl;
        cout << "2. Access inventory." << endl;
        cout << "3. Save game." << endl;
        cout << "4. Load game." << endl;
        cout << "5. End game." << endl;
        cout << "" << endl;
        int option;
        cin >> option;

        if(option == 1){
            gameboard.printBoard();
            cout << "What tile would you like to move to?" << endl;
            cout << "1 2 3" << endl;
            cout << "4 x 5" << endl;
            cout << "6 7 8" << endl;
            int movement;
            cin >> movement;
            gameboard.movePlayer(movement, p1, Mqueue);
            gameboard.printBoard();
        }
        if(option == 2){
            //fillmein
            cout << "Here's whats in your inventory:" << endl;
            p1.printInv();
            cout << "Use an item?" << endl;
            cout << "1. Yes." << endl;
            cout << "2. No." << endl;
            int choice;
            cin >> choice;
            if(choice < 3 && choice > 0){
                item itemtoremove = p1.inv.peekItem();
                if(itemtoremove.getType() != "nothing"){
                    p1.inv.removeItem();
                    cout << "You used the " << itemtoremove.getType() << "." <<endl;
                
                    if (itemtoremove.getType() == "Potion") {
                        p1.setHealth(p1.getHealth() + itemtoremove.getValue());
                        cout << "You gained " << itemtoremove.getValue() << " health!" << endl;
                    }
                    else if (itemtoremove.getType() == "Bag of Gold") {
                        p1.setGold(p1.getGold() + itemtoremove.getValue());
                        cout << "You gained " << itemtoremove.getValue() << " gold!" << endl;
                    }
                    else if (itemtoremove.getType() == "Loaf of bread") {
                        p1.setHealth(p1.getHealth() + itemtoremove.getValue());
                        cout << "You restored " << itemtoremove.getValue() << " health with the bread!" << endl;
                    }
                }else{
                    cout << "No items to use." << endl;
                }
            }
        }
        if(option == 3){
            string filename = "savegame.txt";
            saveGame(filename, gameboard, p1, Mqueue);
        }
        if(option == 4){
            string filename = "savegame.txt";
            loadGame(filename, gameboard, p1, Mqueue);
        }
        if(option == 5){
            cout << "Are you sure you want to quit?" << endl;
            cout << "1. Yes." << endl;
            cout << "2. No." << endl;
            int opt;
            cin >> opt;
            if(opt > 0 && opt < 3){
                if(opt == 1){
                    cout << "Thanks for playing!" << endl;
                    break;
                }
                if(opt == 2){
                    cout << "Going back..." << endl;
                }
            }else{
                cout << "Not an option." << endl;
            }
        }
    }
    return 0;
}