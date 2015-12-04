#include <iostream>
#include <string>
#include <ctime>
using namespace std;

const int CARDNUM = 10;
const string player1 = "Alex";
const string player2 = "Bob";

class card
{
private:
    int i,j;
    char temp;
    
public:
    char hand[CARDNUM+1];// hand[10]=0 always
    char exist[CARDNUM];
    char cover[CARDNUM];
    
    /* will print 222442123 for the player*/
    void print_private(){
        for(i = 0; i < CARDNUM+1; i++){
            if (hand[i]=='0'){
                for (j = 0; j < i; ++j){ cout<<hand[j]<<" "; }
                break;
            }
        }
        cout<<"/ ";
        for(i = 0; i < CARDNUM; i++){
            if (exist[i]=='0'){
                for (j = 0; j < i; ++j){ cout<<exist[j]<<" "; }
                break;
            }
        }
        cout<<"/ ";
        for(i = 0; i < CARDNUM; i++){
            if (cover[i]=='0'){
                for (j = 0; j < i; ++j){ cout<<cover[j]<<" "; }
                break;
            }
        }
        cout<<endl;
    }
    /* will print XXXXXXXXXX for the opponent */
    void print_public(){
        for(i = 0; i < CARDNUM+1; i++){
            if (hand[i]=='0'){
                for (j = 0; j < i; ++j){ cout<<"X "; }
                break;
            }
        }
        cout<<"/ ";
        for(i = 0; i < CARDNUM; i++){
            if (exist[i]=='0'){
                for (j = 0; j < i; ++j){ cout<<exist[j]<<" "; }
                break;
            }
        }
        cout<<"/ ";
        for(i = 0; i < CARDNUM; i++){
            if (cover[i]=='0'){
                for (j = 0; j < i; ++j){ cout<<cover[j]<<" "; }
                break;
            }
        }
        cout<<endl;
    }
    void initcard(){
        int random,i;
        
        srand((unsigned)time(NULL));
        for(i=0;i<CARDNUM;i++){
            random=rand()%9;
            if(random>0 && random<=7){ hand[i]=random+'0'; }
            else if (random==8){ hand[i]='b'; }
            else if (random==0){ hand[i]='m'; }
        }
    }
    void sortcard(){
        for(i=0;i<CARDNUM-1;i++){
            for(j=i+1;j<CARDNUM;j++)
                if(hand[i]>hand[j]){
                    temp=hand[i];
                    hand[i]=hand[j];
                    hand[j]=temp;
                }
        }
    }
    void clearexist(){
        int i;
        
        for(i=0;i<CARDNUM;i++){
            exist[i]='0';
        }
    }
};
class game
{
public:
    double round;
    int point1;
    int point2;
    
    void initialize(){
        round=0.9;
        point1=0;
        point2=0;
    }
    void clearpoint(){
        point1=0;
        point2=0;
    }
    void addpoint1(int n){ point1+=n; }
    void addpoint2(int n){ point2+=n; }
    void addround(){round+=0.5;}
    void printgame(){
        printf("Round %.lf ",round);
        cout<<player1<<" "<<point1<<" ";
        cout<<player2<<" "<<point2<<endl;
    }
};
/* global variable definitions */
card card1,card2;
game game;
int winner=0;
/* senior function definitions */
void initialize(card* card);
void solo();
void round();
void roundPVE();
void player1round();
void player2round();
void AIround();
void validcheck(int player);
void playone(int player);
void playstd(char input,int player);
void playbolt(int player);
void playmirror(int player);
bool bmcheck(int player);

int main(){
    char model;
    /* initialize the game */
    initialize(&card1);
    sleep(1);
    initialize(&card2);
    game.initialize();
    /* start the game */
    cout << "Welcome to BLADE!" << endl;
    /* choose the mode */
    cout << "Choose model. PVP or PVE?(y/n)";
    cin >> model;
    if (model=='y') {
        while(1){
            if (winner==1){
                cout<<player1<<" wins."<<endl;
                break;
            }
            else if(winner==2){
                cout<<player2<<" wins."<<endl;
                break;
            }
            else{//winner==0
                round();
            }
        }
    }
    else if(model=='n'){
        cout<<" You are Alex and the AI would be Bob."<<endl;
        while(1){
            if (winner==1){
                cout<<player1<<" wins."<<endl;
                break;
            }
            else if(winner==2){
                cout<<player2<<" wins."<<endl;
                break;
            }
            else{//winner==0
                roundPVE();
            }
            // just for test
            if (game.point1<0 || game.point2<0) {
                ;
            }
        }
    }
    getchar();
    return 0;
}
void initialize(card* card){
    int i;
    
    (*card).hand[CARDNUM]='0';
    for(i=0;i<CARDNUM;i++){
        (*card).hand[i]='0';
        (*card).exist[i]='0';
        (*card).cover[i]='0';
    }
    (*card).initcard();
    (*card).sortcard();
}
void solo(){
    int int1,int2;
    int i;
    
    srand((unsigned)time(NULL));
    int1=rand()%7+1;
    int2=rand()%7+1;
    cout<<player1<<" gets "<<int1<<endl;
    cout<<player2<<" gets "<<int2<<endl;
    for(i=0;i<CARDNUM;i++){
        if(card1.exist[i] =='0'){
            card1.exist[i]=int1+'0';
            break;
        }
    }
    if(int1<int2){
        cout<<player1<<" goes first"<<endl;
        game.addpoint1(int1);
        game.addpoint2(int2);
        for(i=0;i<CARDNUM;i++){
            if(card2.exist[i] =='0'){
                card2.exist[i]=int2+'0';
                break;
            }
        }
    }
    else if(int1>int2){
        cout<<player2<<" goes first"<<endl;
        game.addpoint1(int1);
        game.addpoint2(int2);
        for(i=0;i<CARDNUM;i++){
            if(card2.exist[i] =='0'){
                card2.exist[i]=int2+'0';
                break;
            }
        }
    }
    else{
        cout<<"The points are equal."<<endl;
        cout<<player1<<" gets "<<int1<<endl;
        cout<<player2<<" gets "<<int2+1<<endl;
        game.addpoint1(int1);
        game.addpoint2(int2+1);
        for(i=0;i<CARDNUM;i++){
            if(card2.exist[i] =='0'){
                card2.exist[i]=int2+'0'+1;
                break;
            }
        }
    }
    
}
void round(){
    if(game.point1>game.point2){
        player2round();
        if (game.point1>game.point2) {
            winner=1;
            return;
        }
    }
    else if(game.point1<game.point2){
        player1round();
        if(game.point1<game.point2){
            winner=2;
            return;
        }
    }
    else{
        solo();
    }
    game.addround();
    //sleep(3);
}
void roundPVE(){
    if(game.point1>game.point2){
        AIround();
    }
    else if(game.point1<game.point2){
        player1round();
        if(game.point1<game.point2){
            winner=2;
            return;
        }
    }
    else{
        solo();
    }
    game.addround();
}
void player1round(){
    char input;
    int i;
    
    validcheck(1);
    if(winner==2){ return; }
    system("reset");
    game.printgame();
    cout<<player2<<": ";
    card2.print_public();
    cout<<player1<<": ";
    card1.print_private();
    cout<<player1<<" plays ";
    cin>>input;
    if(input=='b'|input=='m'){
        if(!bmcheck(1)){
            return;
        }
    }
    for(i=0;i<CARDNUM;i++){
        if(card1.hand[i]==input){
            if(input>'9'){
                if(input=='b'){
                    playbolt(1);
                }
                else if(input=='m'){
                    playmirror(1);
                }
                return;
            }
            else if(input=='1'){
                playone(1);
                return;
            }
            else{
                if(card1.hand[i]-'0'+game.point1>game.point2){
                    playstd(input,1);
                    return;
                }
                else if(card1.hand[i]-'0'+game.point1==game.point2){
                    playstd(input,1);
                    game.clearpoint();
                    card1.clearexist();
                    card2.clearexist();
                    return;
                }
            }
        }
    }
    cout<< "The input is invalid."<<endl;
    player1round();
}
void player2round(){
    char input;
    int i;
    
    validcheck(2);
    if(winner==1){ return; }
    system("reset");
    game.printgame();
    cout<<player1<<": ";
    card1.print_public();
    cout<<player2<<": ";
    card2.print_private();
    cout<<player2<<" plays:";
    cin>>input;
    if(input=='b'|input=='m'){
        if(!bmcheck(2)){
            return;
        }
    }
    for(i=0;i<CARDNUM;i++){
        if(card2.hand[i]==input){
            if(input>'9'){
                if(input=='b'){
                    playbolt(2);
                }
                else if(input=='m'){
                    playmirror(2);
                }
                return;
            }
            else if(input=='1'){
                playone(2);
                return;
            }
            else{
                if(card2.hand[i]-'0'+game.point2>game.point1){
                    playstd(input,2);
                    return;
                }
                else if(card2.hand[i]-'0'+game.point2==game.point1){
                    playstd(input,2);
                    game.clearpoint();
                    card1.clearexist();
                    card2.clearexist();
                    return;
                }
            }
        }
    }
    cout<< "The input is invalid."<<endl;
    player2round();
}
void AIround(){
    int diff,result;
    int i,temppoi;
    char temp;
    
    diff=game.point1-game.point2;
    for(i=0;i<CARDNUM;i++){
  		card2.hand[i]=card2.hand[i+1];
  	}
  	card2.hand[10]='0';
    /* random according to the valid range */
    if(card2.hand[0]=='0'){
    	result=rand()%(7-diff)+diff;
    }
    else{
    	result=rand()%(9-diff)+diff;
    }
    if (result==9){
    	cout<<player2<<" plays b."<<endl;
  		/* delete the last card in exist */
        for(i=CARDNUM-1;i>=0;i--){
            if(card1.exist[i]!='0'){
                temp=card1.exist[i];
                card1.exist[i]='0';
                break;
            }
        }
        /* add the last card into cover */
        for(i=0;i<CARDNUM;i++){
            if(card1.cover[i]=='0'){
                card1.cover[i]=temp;
                break;
            }
        }
        game.point1-=(temp-'0');
    }
    else if(result==8){
    	cout<<player2<<" plays m."<<endl;
  		/* exchange the points */
   	 	temppoi=game.point2;
    	game.point2=game.point1;
    	game.point1=temppoi;
    	/* exchange exist cards */
    	for (i=0; i<CARDNUM; i++) {
        	temp=card1.exist[i];
        	card1.exist[i]=card2.exist[i];
        	card2.exist[i]=temp;
    	}
    }
    else{
    	cout<<player2<<" plays "<<result<<"."<<endl;
    	for(i=0;i<CARDNUM;i++){
            if(card2.exist[i]=='0'){
                card2.exist[i]=result+'0';
                break;
            }
        }
        game.point2+=(result);
        if(game.point1==game.point2){
            game.clearpoint();
            card1.clearexist();
            card2.clearexist();
        }
    }

}
void validcheck(int player){
    int i,j=0;
    
    if (player==1){
        for(i=0;i<CARDNUM;i++){
            if(card1.hand[i]=='m' || card1.hand[i]=='b'){
                if(bmcheck(1)){
                    return;
                }
                break;
            }
        }
        for(i=0;i<CARDNUM;i++){
            if(card1.hand[i]-'0'+game.point1>game.point2 && card1.hand[i]<='9'){ j++; }
        }
        if(j==0){ winner=2; }
    }
    else if(player==2){
        for(i=0;i<CARDNUM;i++){
            if(card2.hand[i]=='m' || card2.hand[i]=='b'){
                if(bmcheck(2)){
                    return;
                }
                break;
            }
        }
        for(i=0;i<CARDNUM;i++){
            if(card2.hand[i]-'0'+game.point2>game.point1 && card2.hand[i]<='9'){ j++; }
        }
        if(j==0){ winner=1; }
    }
}
void playone(int player){
   	int i,j,k;
   	char temp;
    
    if(player==1){
        /* check valid */
        j=0;
        for(i=0;i<CARDNUM;i++){
            if(card1.cover[i]!='0'){
                j++;
            }
        }
        /* delete 1 in hand */
        for(i=0;i<CARDNUM;i++){
            if(card1.hand[i]=='1'){
                for(k=i;k<CARDNUM;k++){
                    card1.hand[k]=card1.hand[k+1];
                }
                card1.hand[10]='0';
                break;
            }
        }
        if(j!=0){
            /* search the cover */
            for(i=CARDNUM-1;i>=0;i--){
                if(card1.cover[i]!='0'){
                    temp=card1.cover[i];
                    card1.cover[i]='0';
                    break;
                }
            }
            /* return to exist */
            for(i=0;i<CARDNUM;i++){
                if(card1.exist[i]=='0'){
                    card1.exist[i]=temp;
                    break;
                }
            }
            game.addpoint1(temp-'0');
        }
    }
    else if(player==2){
        /* check valid */
        j=0;
        for(i=0;i<CARDNUM;i++){
            if(card2.cover[i]!='0'){
                j++;
            }
        }
        /* delete 1 in hand */
        for(i=0;i<CARDNUM;i++){
            if(card2.hand[i]=='1'){
                for(k=i;k<CARDNUM;k++){
                    card2.hand[k]=card2.hand[k+1];
                }
                card2.hand[10]='0';
                break;
            }
        }
        if(j!=0){
            /* search the cover */
            for(i=CARDNUM-1;i>=0;i--){
                if(card2.cover[i]!='0'){
                    temp=card2.cover[i];
                    card2.cover[i]='0';
                    break;
                }
            }
            /* return to exist */
            for(i=0;i<CARDNUM;i++){
                if(card2.exist[i]=='0'){
                    card2.exist[i]=temp;
                    break;
                }
            }
            game.addpoint2(temp-'0');
        }
    }
}
void playstd(char input,int player){
    int i,j;
    
    if(player==1){
        /* delete in hand */
        for(i=0;i<CARDNUM;i++){
            if(card1.hand[i]==input){
                for(j=i;j<CARDNUM;j++){
                    card1.hand[j]=card1.hand[j+1];
                }
                card1.hand[10]='0';
                break;
            }
        }
        /* add in exist */
        for(i=0;i<CARDNUM;i++){
            if(card1.exist[i] =='0'){
                card1.exist[i]=input;
                break;
            }
        }
        game.addpoint1(input-'0');
    }
    else if (player==2){
        /* delete in hand */
        for(i=0;i<CARDNUM;i++){
            if(card2.hand[i]==input){
                for(j=i;j<CARDNUM;j++){
                    card2.hand[j]=card2.hand[j+1];
                }
                card2.hand[10]='0';
                break;
            }
        }
        /* add in exist */
        for(i=0;i<CARDNUM;i++){
            if(card2.exist[i] =='0'){
                card2.exist[i]=input;
                break;
            }
        }
        game.addpoint2(input-'0');
    }
}
void playbolt(int player){
    int i,j;
    char temp='0';
    
    if(player==1){
        /* delete in hand */
        for(i=0;i<CARDNUM;i++){
            if(card1.hand[i]=='b'){
                for(j=i;j<CARDNUM;j++){
                    card1.hand[j]=card1.hand[j+1];
                }
                card1.hand[10]='0';
                break;
            }
        }
        /* delete the last card in exist */
        for(i=CARDNUM-1;i>=0;i--){
            if(card2.exist[i]!='0'){
                temp=card2.exist[i];
                card2.exist[i]='0';
                break;
            }
        }
        /* add the last card into cover */
        for(i=0;i<CARDNUM;i++){
            if(card2.cover[i]=='0'){
                card2.cover[i]=temp;
                break;
            }
        }
        game.point2-=(temp-'0');
    }
    else if (player==2){
        for(i=0;i<CARDNUM;i++){
            if(card2.hand[i]=='b'){
                for(j=i;j<CARDNUM;j++){
                    card2.hand[j]=card2.hand[j+1];
                }
                card2.hand[10]='0';
                break;
            }
        }
        /* delete the last card in exist */
        for(i=CARDNUM-1;i>=0;i--){
            if(card1.exist[i]!='0'){
                temp=card1.exist[i];
                card1.exist[i]='0';
                break;
            }
        }
        /* add the last card into cover */
        for(i=0;i<CARDNUM;i++){
            if(card1.cover[i]=='0'){
                card1.cover[i]=temp;
                break;
            }
        }
        game.point1-=(temp-'0');
    }
}
void playmirror(int player){
    int temppoi;
    char tempexist;
    int i,j;
    
    if(player==1){
        /* delete the mirror card */
        for(i=0;i<CARDNUM;i++){
            if(card1.hand[i]=='m'){
                for(j=i;j<CARDNUM;j++){
                    card1.hand[j]=card1.hand[j+1];
                }
                card1.hand[10]='0';
                break;
            }
        }
    }
    else if(player==2){
        /* delete the mirror card */
        for(i=0;i<CARDNUM;i++){
            if(card2.hand[i]=='m'){
                for(j=i;j<CARDNUM;j++){
                    card2.hand[j]=card2.hand[j+1];
                }
                card2.hand[10]='0';
                break;
            }
        }
    }
    /* exchange the points */
    temppoi=game.point2;
    game.point2=game.point1;
    game.point1=temppoi;
    /* exchange exist cards */
    for (i=0; i<CARDNUM; i++) {
        tempexist=card1.exist[i];
        card1.exist[i]=card2.exist[i];
        card2.exist[i]=tempexist;
    }
}
bool bmcheck(int player){
    int i;
    
    if (player==1){
        for(i=0;i<CARDNUM;i++){
            if (card1.hand[i]>'0' && card1.hand[i]<='7'){
                return true;
            }
        }
    }
    else if(player==2){
        for(i=0;i<CARDNUM;i++){
            if (card2.hand[i]>'0' && card2.hand[i]<='7'){
                return true;
            }
        }
    }
    return false;
}