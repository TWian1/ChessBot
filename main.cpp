#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

void outcolor(string r, string g, string b, string t) {
  cout << "\x1b[48;2;" << r << ";" << g << ";" << b << "m" << t;
}



double scored(char color, char board[8][8]){
  string allpeices;
  double score;
  double opscore;
  char pice;
  int y;
  int x;
  for (int y2 = 0; y2 < 64; y2++){
    y = int(floor(y2/8));
    x = y2%8;
    if (board[y][x] != ' '){allpeices += string(1, board[y][x]) + to_string(y) + to_string(x) + " ";}
  }
  double peiceval[6] = {3.33, 1000, 3.05, 1, 9.5, 5.63};
  for (int j = 0; j < (allpeices.size())/4; j++){
    pice = allpeices[j*4];
    if (color == 'w'){
    if (pice == 'B'){score += peiceval[0];}
    if (pice == 'K'){score += peiceval[0];}
    if (pice == 'N'){score += peiceval[2];}
    if (pice == 'P'){score += peiceval[3];}
    if (pice == 'Q'){score += peiceval[4];}
    if (pice == 'R'){score += peiceval[5];}
    if (pice == 'b'){opscore += peiceval[0];}
    if (pice == 'k'){opscore += peiceval[0];}
    if (pice == 'n'){opscore += peiceval[2];}
    if (pice == 'p'){opscore += peiceval[3];}
    if (pice == 'q'){opscore += peiceval[4];}
    if (pice == 'r'){opscore += peiceval[5];}
      }
    else{
      if (pice == 'b'){score += peiceval[0];}
      if (pice == 'k'){score += peiceval[0];}
      if (pice == 'n'){score += peiceval[2];}
      if (pice == 'p'){score += peiceval[3];}
      if (pice == 'q'){score += peiceval[4];}
      if (pice == 'r'){score += peiceval[5];}
      if (pice == 'B'){opscore += peiceval[0];}
      if (pice == 'K'){opscore += peiceval[0];}
      if (pice == 'N'){opscore += peiceval[2];}
      if (pice == 'P'){opscore += peiceval[3];}
      if (pice == 'Q'){opscore += peiceval[4];}
      if (pice == 'R'){opscore += peiceval[5];}
    }
  }
  score = score-opscore;
  return score;
}
double calcmove4(char color, char board[8][8]){
  string idx1[6] = {"Bishop", "King", "Knight", "Pawn", "Queen", "Rook"};
  char idx2[6] = {'B', 'K', 'N', 'P', 'Q', 'R'};
  string idx3 = "ABCDEFGH";
  int x;
  int y;
  int bsize = 64;
  string peices;
  int bmove[4][2] = {{-1, 1}, {1, -1}, {-1, -1}, {1, 1}};
  int rmove[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
  int qmove[8][2] = {{-1, 1}, {1, -1}, {-1, -1}, {1, 1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}};
  int nmove[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};
  int kmove[8][2] = {{-1, 1}, {1, -1}, {-1, -1}, {1, 1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}};
  int curpos[2];
  int posmoves = 0;
  string acallmove;
  string allmoves;
  string moves;
  string allpeices;
  for (int y2 = 0; y2 < bsize; y2++){
    y = int(floor(y2/8));
    x = y2%8;
    if (board[y][x] != ' '){allpeices += string(1, board[y][x]) + to_string(y) + to_string(x) + " ";}
  }
  if (color == 'w'){
    for (int y1 = 0; y1 < bsize; y1++){

      y = int(floor(y1/8));
      x = y1%8;
      if (board[y][x] >= 'A' && board[y][x] <= 'Z') {
      int n = sizeof(idx2)/sizeof(idx2[0]);
      auto itr = find(idx2, idx2 + n, board[y][x]);
      //cout << idx1[distance(idx2, itr)] << " on " << idx3[x] << to_string(8-y) << endl;
      peices += string(1, board[y][x]) + to_string(y) +to_string(x) + " ";
      if (board[y][x] == 'B'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+bmove[movenum][0] < 0 || curpos[0]+bmove[movenum][0] > 7) || (curpos[1]+bmove[movenum][1] < 0 || curpos[1]+bmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] >= 'A' && board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] <= 'Z'){break;}

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }

            else{
              //cout << "move" << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += bmove[movenum][0];
              curpos[1] += bmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'R'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+rmove[movenum][0] < 0 || curpos[0]+rmove[movenum][0] > 7) || (curpos[1]+rmove[movenum][1] < 0 || curpos[1]+rmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] >= 'A' && board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] <= 'Z'){break;}

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";

              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += rmove[movenum][0];
              curpos[1] += rmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'Q'){
        for (int movenum = 0; movenum < 8; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+qmove[movenum][0] < 0 || curpos[0]+qmove[movenum][0] > 7) || (curpos[1]+qmove[movenum][1] < 0 || curpos[1]+qmove[movenum][1] > 7))){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] >= 'A' && board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] <= 'Z'){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves +=1;
              curpos[0] += qmove[movenum][0];
              curpos[1] += qmove[movenum][1];
            }
          }

        }
      }

      if (board[y][x] == 'N'){
        for (int a = 0; a < 8; a++){
          //cout << a << endl;
          if (((x+nmove[a][0] < 0 || x+nmove[a][0] > 7) || (y+nmove[a][1] < 0 || y+nmove[a][1] > 7))){
            //cout << "no " << x+nmove[a][0] << y+nmove[a][1] << endl;
            continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]] >= 'A' && board[y+nmove[a][1]][x+nmove[a][0]] <= 'Z'){
            //cout << "no2 " << x+nmove[a][0] << y+nmove[a][1] << endl;
            continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }
          else{
            //cout << "move" << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'K'){
        for (int a = 0; a < 8; a++){

          if (((x+kmove[a][0] < 0 || x+kmove[a][0] > 7) || (y+kmove[a][1] < 0 || y+kmove[a][1] > 7))){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]] >= 'A' && board[y+kmove[a][1]][x+kmove[a][0]] <= 'Z'){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }

          else{
            //cout << "move" << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'P'){
        if (y==6){
          for (int a = 0; a < 2; a++){
            if (y-a-1 < 0 || y-a-1 > 7){break;}
            if (board[y-a-1][x] >= 'A' && board[y-a-1][x] <= 'Z'){break;}
            if (board[y-a-1][x] == ' '){
              //cout << "move" << to_string(x) << " " << to_string(y-a-1) << endl;
              allmoves += string(1, idx3[x]) + to_string(8-(y-a-1)) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y-a-1) + " ";
              posmoves+=1;
              }
            }
          }
        else{
          if (y-1 < 0 || y-1 > 7){break;}
          if (board[y-1][x] >= 'A' && board[y-1][x] <= 'Z'){break;}
          if (board[y-1][x] == ' '){
            //cout << "move" << to_string(x) << " " << to_string(y-1) << endl;
            allmoves += string(1, idx3[x]) + to_string(8-(y-1)) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y-1) + " ";
            posmoves+=1;

            }
        }
        for (int a=0; a<2;a++){
          if (x+(a*2)-1 < 0 || x+(a*2)-1 > 7 || y-1 < 0 || y-1 > 7){continue;}
          if (board[y-1][x+(a*2)-1] >= 'A' && board[y-1][x+(a*2)-1] <= 'Z'){continue;}
          if (board[y-1][x+(a*2)-1] != ' '){
            //cout << "take" << to_string(x+(a*2)-1) << " " << to_string(y-1) << endl;
            posmoves+=1;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+(a*2)-1]) + to_string(8-(y-1)) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+(a*2)-1) + to_string(y-1) + " ";
          }
        }
        }
      }
      }

    }
  //HELP PLEASE
  else{
    for (int y1 = 0; y1 < bsize; y1++){

      y = int(floor(y1/8));
      x = y1%8;
      if (board[y][x] >= 'a' && board[y][x] <= 'z') {
      //int n = sizeof(idx2)/sizeof(idx2[0]);
      //auto itr = find(idx2, idx2 + n, board[y][x]);
      //cout << idx1[distance(idx2, itr)] << " on " << idx3[x] << to_string(8-y) << endl;
      peices += string(1, board[y][x]) + to_string(y) +to_string(x) + " ";
      if (board[y][x] == 'b'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+bmove[movenum][0] < 0 || curpos[0]+bmove[movenum][0] > 7) || (curpos[1]+bmove[movenum][1] < 0 || curpos[1]+bmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] >= 'a' && board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] <= 'z'){break;}

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" +  to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }

            else{
              //cout << "move" << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" +  to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += bmove[movenum][0];
              curpos[1] += bmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'r'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+rmove[movenum][0] < 0 || curpos[0]+rmove[movenum][0] > 7) || (curpos[1]+rmove[movenum][1] < 0 || curpos[1]+rmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] >= 'a' && board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] <= 'z'){break;}

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += rmove[movenum][0];
              curpos[1] += rmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'q'){
        for (int movenum = 0; movenum < 8; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+qmove[movenum][0] < 0 || curpos[0]+qmove[movenum][0] > 7) || (curpos[1]+qmove[movenum][1] < 0 || curpos[1]+qmove[movenum][1] > 7))){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] >= 'a' && board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] <= 'z'){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves +=1;
              curpos[0] += qmove[movenum][0];
              curpos[1] += qmove[movenum][1];
            }
          }

        }
      }

      if (board[y][x] == 'n'){
        for (int a = 0; a < 8; a++){

          if (((x+nmove[a][0] < 0 || x+nmove[a][0] > 7) || (y+nmove[a][1] < 0 || y+nmove[a][1] > 7))){continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]] >= 'a' && board[y+nmove[a][1]][x+nmove[a][0]] <= 'z'){continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }
          else{
            //cout << "move" << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'k'){
        for (int a = 0; a < 8; a++){

          if (((x+kmove[a][0] < 0 || x+kmove[a][0] > 7) || (y+kmove[a][1] < 0 || y+kmove[a][1] > 7))){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]] >= 'a' && board[y+kmove[a][1]][x+kmove[a][0]] <= 'z'){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }

          else{
            //cout << "move" << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'p'){
        if (y==1){
          for (int a = 0; a < 2; a++){
            if (y+a+1 < 0 || y+a+1 > 7){break;}
            if (board[y+a+1][x] >= 'a' && board[y+a+1][x] <= 'z'){break;}
            if (board[y+a+1][x] == ' '){
              //cout << "move" << to_string(x) << " " << to_string(y+a+1) << endl;
              allmoves += string(1, idx3[x]) + to_string(8-(y+a+1)) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y+a+1) + " ";
              posmoves+=1;
              }
            }
          }
        else{
          if (y-1 < 0 || y-1 > 7){break;}
          if (board[y+1][x] >= 'a' && board[y+1][x] <= 'z'){break;}
          if (board[y+1][x] == ' '){
            //cout << "move" << to_string(x) << " " << to_string(y+1) << endl;
            allmoves += string(1, idx3[x]) + to_string(8-(y+1)) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y+1) + " ";
            posmoves+=1;

            }
        }
        for (int a=0; a<2;a++){
          if (x+(a*2)-1 < 0 || x+(a*2)-1 > 7 || y+1 < 0 || y+1 > 7){continue;}
          if (board[y+1][x+(a*2)-1] >= 'a' && board[y+1][x+(a*2)-1] <= 'z'){continue;}
          if (board[y+1][x+(a*2)-1] != ' '){
            //cout << "take" << to_string(x+(a*2)-1) << " " << to_string(y+1) << endl;
            posmoves+=1;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+(a*2)-1]) + to_string(8-(y+1)) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+(a*2)-1) + to_string(y+1) + " ";
          }
        }
        }
      }
      }

    }
  char pice;
  double peiceval[6] = {3.33, 0, 3.05, 1, 9.5, 5.63};
  double score = 0;
  double opscore = 0;
  //cout << allpeices << endl;
  for (int j = 0; j < (allpeices.size())/4; j++){
    pice = allpeices[j*4];
    if (color == 'w'){
    if (pice == 'B'){score += peiceval[0];}
    if (pice == 'N'){score += peiceval[2];}
    if (pice == 'P'){score += peiceval[3];}
    if (pice == 'Q'){score += peiceval[4];}
    if (pice == 'R'){score += peiceval[5];}
    if (pice == 'b'){opscore += peiceval[0];}
    if (pice == 'n'){opscore += peiceval[2];}
    if (pice == 'p'){opscore += peiceval[3];}
    if (pice == 'q'){opscore += peiceval[4];}
    if (pice == 'r'){opscore += peiceval[5];}
      }
    else{
      if (pice == 'b'){score += peiceval[0];}
      if (pice == 'n'){score += peiceval[2];}
      if (pice == 'p'){score += peiceval[3];}
      if (pice == 'q'){score += peiceval[4];}
      if (pice == 'r'){score += peiceval[5];}
      if (pice == 'B'){opscore += peiceval[0];}
      if (pice == 'N'){opscore += peiceval[2];}
      if (pice == 'P'){opscore += peiceval[3];}
      if (pice == 'Q'){opscore += peiceval[4];}
      if (pice == 'R'){opscore += peiceval[5];}
    }
  }
  //cout << opscore << endl;
  //cout << score << endl;
  //score = score-opscore;
  //cout << posmoves << endl;
  //cout << allmoves << endl;
  //cout << peices << endl;
  //cout << score << endl;
  //cout << acallmove << endl;
  int idxmove;
  double best= -100000000;
  int besti;
  int besto;
  for (int nidxmove = 0; nidxmove < acallmove.size()/6; nidxmove++){
    idxmove = nidxmove*6;
    char newboard[8][8];
    char retcolor;
    if (color == 'w'){retcolor = 'b';}
    else{retcolor = 'w';}
    for (int y3 = 0; y3 < 8; y3++){
      for (int x2 = 0; x2 < 8; x2++){
        newboard[y3][x2] = board[y3][x2];
      }
    }
    char c = newboard[acallmove[idxmove+1] - '0'][acallmove[idxmove] - '0'];
    newboard[acallmove[idxmove+1] - '0'][acallmove[idxmove] - '0'] = ' ';
    newboard[acallmove[idxmove+4] - '0'][acallmove[idxmove+3] - '0'] = c;
    if (acallmove[idxmove] == '2' && acallmove[idxmove+1] == '8'){
      for (int y4 = 0; y4 < 8; y4++){
        for (int x3 = 0; x3 < 8; x3++){
          cout << string(1, newboard[y4][x3]) << " ";
        }
        cout << endl;
      }
    }
    int movescore = scored(color, newboard);
    //cout << string(1, acallmove[idxmove]) << string(1, acallmove[idxmove+1]) << string(1, acallmove[idxmove+2]) << string(1, acallmove[idxmove+3]) << string(1, acallmove[idxmove+4]) << " " << movescore << endl;
    if (movescore>best){
      best = movescore;
      besti = idxmove;
      besto = -movescore;
    }
  }
  //cout << string(1, acallmove[besti]) << string(1, acallmove[besti+1]) << string(1, acallmove[besti+2]) << string(1, acallmove[besti+3]) << string(1, acallmove[besti+4]) << " " << to_string(best) << endl;





  return besto;
  }
double calcmove3(char color, char board[8][8]){
  string idx1[6] = {"Bishop", "King", "Knight", "Pawn", "Queen", "Rook"};
  char idx2[6] = {'B', 'K', 'N', 'P', 'Q', 'R'};
  string idx3 = "ABCDEFGH";
  int x;
  int y;
  int bsize = 64;
  string peices;
  int bmove[4][2] = {{-1, 1}, {1, -1}, {-1, -1}, {1, 1}};
  int rmove[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
  int qmove[8][2] = {{-1, 1}, {1, -1}, {-1, -1}, {1, 1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}};
  int nmove[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};
  int kmove[8][2] = {{-1, 1}, {1, -1}, {-1, -1}, {1, 1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}};
  int curpos[2];
  int posmoves = 0;
  string acallmove;
  string allmoves;
  string moves;
  string allpeices;
  for (int y2 = 0; y2 < bsize; y2++){
    y = int(floor(y2/8));
    x = y2%8;
    if (board[y][x] != ' '){allpeices += string(1, board[y][x]) + to_string(y) + to_string(x) + " ";}
  }
  if (color == 'w'){
    for (int y1 = 0; y1 < bsize; y1++){

      y = int(floor(y1/8));
      x = y1%8;
      if (board[y][x] >= 'A' && board[y][x] <= 'Z') {
      int n = sizeof(idx2)/sizeof(idx2[0]);
      auto itr = find(idx2, idx2 + n, board[y][x]);
      //cout << idx1[distance(idx2, itr)] << " on " << idx3[x] << to_string(8-y) << endl;
      peices += string(1, board[y][x]) + to_string(y) +to_string(x) + " ";
      if (board[y][x] == 'B'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+bmove[movenum][0] < 0 || curpos[0]+bmove[movenum][0] > 7) || (curpos[1]+bmove[movenum][1] < 0 || curpos[1]+bmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] >= 'A' && board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] <= 'Z'){break;}

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }

            else{
              //cout << "move" << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += bmove[movenum][0];
              curpos[1] += bmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'R'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+rmove[movenum][0] < 0 || curpos[0]+rmove[movenum][0] > 7) || (curpos[1]+rmove[movenum][1] < 0 || curpos[1]+rmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] >= 'A' && board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] <= 'Z'){break;}

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";

              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += rmove[movenum][0];
              curpos[1] += rmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'Q'){
        for (int movenum = 0; movenum < 8; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+qmove[movenum][0] < 0 || curpos[0]+qmove[movenum][0] > 7) || (curpos[1]+qmove[movenum][1] < 0 || curpos[1]+qmove[movenum][1] > 7))){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] >= 'A' && board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] <= 'Z'){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves +=1;
              curpos[0] += qmove[movenum][0];
              curpos[1] += qmove[movenum][1];
            }
          }

        }
      }

      if (board[y][x] == 'N'){
        for (int a = 0; a < 8; a++){
          //cout << a << endl;
          if (((x+nmove[a][0] < 0 || x+nmove[a][0] > 7) || (y+nmove[a][1] < 0 || y+nmove[a][1] > 7))){
            //cout << "no " << x+nmove[a][0] << y+nmove[a][1] << endl;
            continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]] >= 'A' && board[y+nmove[a][1]][x+nmove[a][0]] <= 'Z'){
            //cout << "no2 " << x+nmove[a][0] << y+nmove[a][1] << endl;
            continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }
          else{
            //cout << "move" << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'K'){
        for (int a = 0; a < 8; a++){

          if (((x+kmove[a][0] < 0 || x+kmove[a][0] > 7) || (y+kmove[a][1] < 0 || y+kmove[a][1] > 7))){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]] >= 'A' && board[y+kmove[a][1]][x+kmove[a][0]] <= 'Z'){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }

          else{
            //cout << "move" << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'P'){
        if (y==6){
          for (int a = 0; a < 2; a++){
            if (y-a-1 < 0 || y-a-1 > 7){break;}
            if (board[y-a-1][x] >= 'A' && board[y-a-1][x] <= 'Z'){break;}
            if (board[y-a-1][x] == ' '){
              //cout << "move" << to_string(x) << " " << to_string(y-a-1) << endl;
              allmoves += string(1, idx3[x]) + to_string(8-(y-a-1)) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y-a-1) + " ";
              posmoves+=1;
              }
            }
          }
        else{
          if (y-1 < 0 || y-1 > 7){break;}
          if (board[y-1][x] >= 'A' && board[y-1][x] <= 'Z'){break;}
          if (board[y-1][x] == ' '){
            //cout << "move" << to_string(x) << " " << to_string(y-1) << endl;
            allmoves += string(1, idx3[x]) + to_string(8-(y-1)) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y-1) + " ";
            posmoves+=1;

            }
        }
        for (int a=0; a<2;a++){
          if (x+(a*2)-1 < 0 || x+(a*2)-1 > 7 || y-1 < 0 || y-1 > 7){continue;}
          if (board[y-1][x+(a*2)-1] >= 'A' && board[y-1][x+(a*2)-1] <= 'Z'){continue;}
          if (board[y-1][x+(a*2)-1] != ' '){
            //cout << "take" << to_string(x+(a*2)-1) << " " << to_string(y-1) << endl;
            posmoves+=1;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+(a*2)-1]) + to_string(8-(y-1)) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+(a*2)-1) + to_string(y-1) + " ";
          }
        }
        }
      }
      }

    }
  //HELP PLEASE
  else{
    for (int y1 = 0; y1 < bsize; y1++){

      y = int(floor(y1/8));
      x = y1%8;
      if (board[y][x] >= 'a' && board[y][x] <= 'z') {
      //int n = sizeof(idx2)/sizeof(idx2[0]);
      //auto itr = find(idx2, idx2 + n, board[y][x]);
      //cout << idx1[distance(idx2, itr)] << " on " << idx3[x] << to_string(8-y) << endl;
      peices += string(1, board[y][x]) + to_string(y) +to_string(x) + " ";
      if (board[y][x] == 'b'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+bmove[movenum][0] < 0 || curpos[0]+bmove[movenum][0] > 7) || (curpos[1]+bmove[movenum][1] < 0 || curpos[1]+bmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] >= 'a' && board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] <= 'z'){break;}

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" +  to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }

            else{
              //cout << "move" << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" +  to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += bmove[movenum][0];
              curpos[1] += bmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'r'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+rmove[movenum][0] < 0 || curpos[0]+rmove[movenum][0] > 7) || (curpos[1]+rmove[movenum][1] < 0 || curpos[1]+rmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] >= 'a' && board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] <= 'z'){break;}

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += rmove[movenum][0];
              curpos[1] += rmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'q'){
        for (int movenum = 0; movenum < 8; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+qmove[movenum][0] < 0 || curpos[0]+qmove[movenum][0] > 7) || (curpos[1]+qmove[movenum][1] < 0 || curpos[1]+qmove[movenum][1] > 7))){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] >= 'a' && board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] <= 'z'){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves +=1;
              curpos[0] += qmove[movenum][0];
              curpos[1] += qmove[movenum][1];
            }
          }

        }
      }

      if (board[y][x] == 'n'){
        for (int a = 0; a < 8; a++){

          if (((x+nmove[a][0] < 0 || x+nmove[a][0] > 7) || (y+nmove[a][1] < 0 || y+nmove[a][1] > 7))){continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]] >= 'a' && board[y+nmove[a][1]][x+nmove[a][0]] <= 'z'){continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }
          else{
            //cout << "move" << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'k'){
        for (int a = 0; a < 8; a++){

          if (((x+kmove[a][0] < 0 || x+kmove[a][0] > 7) || (y+kmove[a][1] < 0 || y+kmove[a][1] > 7))){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]] >= 'a' && board[y+kmove[a][1]][x+kmove[a][0]] <= 'z'){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }

          else{
            //cout << "move" << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'p'){
        if (y==1){
          for (int a = 0; a < 2; a++){
            if (y+a+1 < 0 || y+a+1 > 7){break;}
            if (board[y+a+1][x] >= 'a' && board[y+a+1][x] <= 'z'){break;}
            if (board[y+a+1][x] == ' '){
              //cout << "move" << to_string(x) << " " << to_string(y+a+1) << endl;
              allmoves += string(1, idx3[x]) + to_string(8-(y+a+1)) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y+a+1) + " ";
              posmoves+=1;
              }
            }
          }
        else{
          if (y-1 < 0 || y-1 > 7){break;}
          if (board[y+1][x] >= 'a' && board[y+1][x] <= 'z'){break;}
          if (board[y+1][x] == ' '){
            //cout << "move" << to_string(x) << " " << to_string(y+1) << endl;
            allmoves += string(1, idx3[x]) + to_string(8-(y+1)) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y+1) + " ";
            posmoves+=1;

            }
        }
        for (int a=0; a<2;a++){
          if (x+(a*2)-1 < 0 || x+(a*2)-1 > 7 || y+1 < 0 || y+1 > 7){continue;}
          if (board[y+1][x+(a*2)-1] >= 'a' && board[y+1][x+(a*2)-1] <= 'z'){continue;}
          if (board[y+1][x+(a*2)-1] != ' '){
            //cout << "take" << to_string(x+(a*2)-1) << " " << to_string(y+1) << endl;
            posmoves+=1;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+(a*2)-1]) + to_string(8-(y+1)) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+(a*2)-1) + to_string(y+1) + " ";
          }
        }
        }
      }
      }

    }
  char pice;
  double peiceval[6] = {3.33, 0, 3.05, 1, 9.5, 5.63};
  double score = 0;
  double opscore = 0;
  //cout << allpeices << endl;
  for (int j = 0; j < (allpeices.size())/4; j++){
    pice = allpeices[j*4];
    if (color == 'w'){
    if (pice == 'B'){score += peiceval[0];}
    if (pice == 'N'){score += peiceval[2];}
    if (pice == 'P'){score += peiceval[3];}
    if (pice == 'Q'){score += peiceval[4];}
    if (pice == 'R'){score += peiceval[5];}
    if (pice == 'b'){opscore += peiceval[0];}
    if (pice == 'n'){opscore += peiceval[2];}
    if (pice == 'p'){opscore += peiceval[3];}
    if (pice == 'q'){opscore += peiceval[4];}
    if (pice == 'r'){opscore += peiceval[5];}
      }
    else{
      if (pice == 'b'){score += peiceval[0];}
      if (pice == 'n'){score += peiceval[2];}
      if (pice == 'p'){score += peiceval[3];}
      if (pice == 'q'){score += peiceval[4];}
      if (pice == 'r'){score += peiceval[5];}
      if (pice == 'B'){opscore += peiceval[0];}
      if (pice == 'N'){opscore += peiceval[2];}
      if (pice == 'P'){opscore += peiceval[3];}
      if (pice == 'Q'){opscore += peiceval[4];}
      if (pice == 'R'){opscore += peiceval[5];}
    }
  }
  //cout << opscore << endl;
  //cout << score << endl;
  //score = score-opscore;
  //cout << posmoves << endl;
  //cout << allmoves << endl;
  //cout << peices << endl;
  //cout << score << endl;
  //cout << acallmove << endl;
  int idxmove;
  double best= -100000000;
  int besti;
  int besto;
  for (int nidxmove = 0; nidxmove < acallmove.size()/6; nidxmove++){
    idxmove = nidxmove*6;
    char newboard[8][8];
    char retcolor;
    if (color == 'w'){retcolor = 'b';}
    else{retcolor = 'w';}
    for (int y3 = 0; y3 < 8; y3++){
      for (int x2 = 0; x2 < 8; x2++){
        newboard[y3][x2] = board[y3][x2];
      }
    }
    char c = newboard[acallmove[idxmove+1] - '0'][acallmove[idxmove] - '0'];
    newboard[acallmove[idxmove+1] - '0'][acallmove[idxmove] - '0'] = ' ';
    newboard[acallmove[idxmove+4] - '0'][acallmove[idxmove+3] - '0'] = c;
    if (acallmove[idxmove] == '2' && acallmove[idxmove+1] == '8'){
      for (int y4 = 0; y4 < 8; y4++){
        for (int x3 = 0; x3 < 8; x3++){
          cout << string(1, newboard[y4][x3]) << " ";
        }
        cout << endl;
      }
    }
    int movescore = calcmove4(retcolor, newboard);
    //cout << string(1, acallmove[idxmove]) << string(1, acallmove[idxmove+1]) << string(1, acallmove[idxmove+2]) << string(1, acallmove[idxmove+3]) << string(1, acallmove[idxmove+4]) << " " << movescore << endl;
    if (movescore>best){
      best = movescore;
      besti = idxmove;
      besto = -movescore;
    }
  }
  //cout << string(1, acallmove[besti]) << string(1, acallmove[besti+1]) << string(1, acallmove[besti+2]) << string(1, acallmove[besti+3]) << string(1, acallmove[besti+4]) << " " << to_string(best) << endl;





  return besto;
  }

double calcmove2(char color, char board[8][8]){
  string idx1[6] = {"Bishop", "King", "Knight", "Pawn", "Queen", "Rook"};
  char idx2[6] = {'B', 'K', 'N', 'P', 'Q', 'R'};
  string idx3 = "ABCDEFGH";
  int x;
  int y;
  int bsize = 64;
  string peices;
  int bmove[4][2] = {{-1, 1}, {1, -1}, {-1, -1}, {1, 1}};
  int rmove[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
  int qmove[8][2] = {{-1, 1}, {1, -1}, {-1, -1}, {1, 1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}};
  int nmove[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};
  int kmove[8][2] = {{-1, 1}, {1, -1}, {-1, -1}, {1, 1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}};
  int curpos[2];
  int posmoves = 0;
  string acallmove;
  string allmoves;
  string moves;
  string allpeices;
  for (int y2 = 0; y2 < bsize; y2++){
    y = int(floor(y2/8));
    x = y2%8;
    if (board[y][x] != ' '){allpeices += string(1, board[y][x]) + to_string(y) + to_string(x) + " ";}
  }
  if (color == 'w'){
    for (int y1 = 0; y1 < bsize; y1++){

      y = int(floor(y1/8));
      x = y1%8;
      if (board[y][x] >= 'A' && board[y][x] <= 'Z') {
      int n = sizeof(idx2)/sizeof(idx2[0]);
      auto itr = find(idx2, idx2 + n, board[y][x]);
      //cout << idx1[distance(idx2, itr)] << " on " << idx3[x] << to_string(8-y) << endl;
      peices += string(1, board[y][x]) + to_string(y) +to_string(x) + " ";
      if (board[y][x] == 'B'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+bmove[movenum][0] < 0 || curpos[0]+bmove[movenum][0] > 7) || (curpos[1]+bmove[movenum][1] < 0 || curpos[1]+bmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] >= 'A' && board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] <= 'Z'){break;}

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }

            else{
              //cout << "move" << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += bmove[movenum][0];
              curpos[1] += bmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'R'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+rmove[movenum][0] < 0 || curpos[0]+rmove[movenum][0] > 7) || (curpos[1]+rmove[movenum][1] < 0 || curpos[1]+rmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] >= 'A' && board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] <= 'Z'){break;}

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";

              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += rmove[movenum][0];
              curpos[1] += rmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'Q'){
        for (int movenum = 0; movenum < 8; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+qmove[movenum][0] < 0 || curpos[0]+qmove[movenum][0] > 7) || (curpos[1]+qmove[movenum][1] < 0 || curpos[1]+qmove[movenum][1] > 7))){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] >= 'A' && board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] <= 'Z'){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves +=1;
              curpos[0] += qmove[movenum][0];
              curpos[1] += qmove[movenum][1];
            }
          }

        }
      }

      if (board[y][x] == 'N'){
        for (int a = 0; a < 8; a++){
          //cout << a << endl;
          if (((x+nmove[a][0] < 0 || x+nmove[a][0] > 7) || (y+nmove[a][1] < 0 || y+nmove[a][1] > 7))){
            //cout << "no " << x+nmove[a][0] << y+nmove[a][1] << endl;
            continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]] >= 'A' && board[y+nmove[a][1]][x+nmove[a][0]] <= 'Z'){
            //cout << "no2 " << x+nmove[a][0] << y+nmove[a][1] << endl;
            continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }
          else{
            //cout << "move" << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'K'){
        for (int a = 0; a < 8; a++){

          if (((x+kmove[a][0] < 0 || x+kmove[a][0] > 7) || (y+kmove[a][1] < 0 || y+kmove[a][1] > 7))){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]] >= 'A' && board[y+kmove[a][1]][x+kmove[a][0]] <= 'Z'){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }

          else{
            //cout << "move" << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'P'){
        if (y==6){
          for (int a = 0; a < 2; a++){
            if (y-a-1 < 0 || y-a-1 > 7){break;}
            if (board[y-a-1][x] >= 'A' && board[y-a-1][x] <= 'Z'){break;}
            if (board[y-a-1][x] == ' '){
              //cout << "move" << to_string(x) << " " << to_string(y-a-1) << endl;
              allmoves += string(1, idx3[x]) + to_string(8-(y-a-1)) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y-a-1) + " ";
              posmoves+=1;
              }
            }
          }
        else{
          if (y-1 < 0 || y-1 > 7){break;}
          if (board[y-1][x] >= 'A' && board[y-1][x] <= 'Z'){break;}
          if (board[y-1][x] == ' '){
            //cout << "move" << to_string(x) << " " << to_string(y-1) << endl;
            allmoves += string(1, idx3[x]) + to_string(8-(y-1)) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y-1) + " ";
            posmoves+=1;

            }
        }
        for (int a=0; a<2;a++){
          if (x+(a*2)-1 < 0 || x+(a*2)-1 > 7 || y-1 < 0 || y-1 > 7){continue;}
          if (board[y-1][x+(a*2)-1] >= 'A' && board[y-1][x+(a*2)-1] <= 'Z'){continue;}
          if (board[y-1][x+(a*2)-1] != ' '){
            //cout << "take" << to_string(x+(a*2)-1) << " " << to_string(y-1) << endl;
            posmoves+=1;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+(a*2)-1]) + to_string(8-(y-1)) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+(a*2)-1) + to_string(y-1) + " ";
          }
        }
        }
      }
      }

    }
  //HELP PLEASE
  else{
    for (int y1 = 0; y1 < bsize; y1++){

      y = int(floor(y1/8));
      x = y1%8;
      if (board[y][x] >= 'a' && board[y][x] <= 'z') {
      //int n = sizeof(idx2)/sizeof(idx2[0]);
      //auto itr = find(idx2, idx2 + n, board[y][x]);
      //cout << idx1[distance(idx2, itr)] << " on " << idx3[x] << to_string(8-y) << endl;
      peices += string(1, board[y][x]) + to_string(y) +to_string(x) + " ";
      if (board[y][x] == 'b'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+bmove[movenum][0] < 0 || curpos[0]+bmove[movenum][0] > 7) || (curpos[1]+bmove[movenum][1] < 0 || curpos[1]+bmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] >= 'a' && board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] <= 'z'){break;}

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" +  to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }

            else{
              //cout << "move" << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" +  to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += bmove[movenum][0];
              curpos[1] += bmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'r'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+rmove[movenum][0] < 0 || curpos[0]+rmove[movenum][0] > 7) || (curpos[1]+rmove[movenum][1] < 0 || curpos[1]+rmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] >= 'a' && board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] <= 'z'){break;}

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += rmove[movenum][0];
              curpos[1] += rmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'q'){
        for (int movenum = 0; movenum < 8; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+qmove[movenum][0] < 0 || curpos[0]+qmove[movenum][0] > 7) || (curpos[1]+qmove[movenum][1] < 0 || curpos[1]+qmove[movenum][1] > 7))){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] >= 'a' && board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] <= 'z'){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves +=1;
              curpos[0] += qmove[movenum][0];
              curpos[1] += qmove[movenum][1];
            }
          }

        }
      }

      if (board[y][x] == 'n'){
        for (int a = 0; a < 8; a++){

          if (((x+nmove[a][0] < 0 || x+nmove[a][0] > 7) || (y+nmove[a][1] < 0 || y+nmove[a][1] > 7))){continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]] >= 'a' && board[y+nmove[a][1]][x+nmove[a][0]] <= 'z'){continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }
          else{
            //cout << "move" << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'k'){
        for (int a = 0; a < 8; a++){

          if (((x+kmove[a][0] < 0 || x+kmove[a][0] > 7) || (y+kmove[a][1] < 0 || y+kmove[a][1] > 7))){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]] >= 'a' && board[y+kmove[a][1]][x+kmove[a][0]] <= 'z'){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }

          else{
            //cout << "move" << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'p'){
        if (y==1){
          for (int a = 0; a < 2; a++){
            if (y+a+1 < 0 || y+a+1 > 7){break;}
            if (board[y+a+1][x] >= 'a' && board[y+a+1][x] <= 'z'){break;}
            if (board[y+a+1][x] == ' '){
              //cout << "move" << to_string(x) << " " << to_string(y+a+1) << endl;
              allmoves += string(1, idx3[x]) + to_string(8-(y+a+1)) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y+a+1) + " ";
              posmoves+=1;
              }
            }
          }
        else{
          if (y-1 < 0 || y-1 > 7){break;}
          if (board[y+1][x] >= 'a' && board[y+1][x] <= 'z'){break;}
          if (board[y+1][x] == ' '){
            //cout << "move" << to_string(x) << " " << to_string(y+1) << endl;
            allmoves += string(1, idx3[x]) + to_string(8-(y+1)) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y+1) + " ";
            posmoves+=1;

            }
        }
        for (int a=0; a<2;a++){
          if (x+(a*2)-1 < 0 || x+(a*2)-1 > 7 || y+1 < 0 || y+1 > 7){continue;}
          if (board[y+1][x+(a*2)-1] >= 'a' && board[y+1][x+(a*2)-1] <= 'z'){continue;}
          if (board[y+1][x+(a*2)-1] != ' '){
            //cout << "take" << to_string(x+(a*2)-1) << " " << to_string(y+1) << endl;
            posmoves+=1;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+(a*2)-1]) + to_string(8-(y+1)) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+(a*2)-1) + to_string(y+1) + " ";
          }
        }
        }
      }
      }

    }
  char pice;
  double peiceval[6] = {3.33, 0, 3.05, 1, 9.5, 5.63};
  double score = 0;
  double opscore = 0;
  //cout << allpeices << endl;
  for (int j = 0; j < (allpeices.size())/4; j++){
    pice = allpeices[j*4];
    if (color == 'w'){
    if (pice == 'B'){score += peiceval[0];}
    if (pice == 'N'){score += peiceval[2];}
    if (pice == 'P'){score += peiceval[3];}
    if (pice == 'Q'){score += peiceval[4];}
    if (pice == 'R'){score += peiceval[5];}
    if (pice == 'b'){opscore += peiceval[0];}
    if (pice == 'n'){opscore += peiceval[2];}
    if (pice == 'p'){opscore += peiceval[3];}
    if (pice == 'q'){opscore += peiceval[4];}
    if (pice == 'r'){opscore += peiceval[5];}
      }
    else{
      if (pice == 'b'){score += peiceval[0];}
      if (pice == 'n'){score += peiceval[2];}
      if (pice == 'p'){score += peiceval[3];}
      if (pice == 'q'){score += peiceval[4];}
      if (pice == 'r'){score += peiceval[5];}
      if (pice == 'B'){opscore += peiceval[0];}
      if (pice == 'N'){opscore += peiceval[2];}
      if (pice == 'P'){opscore += peiceval[3];}
      if (pice == 'Q'){opscore += peiceval[4];}
      if (pice == 'R'){opscore += peiceval[5];}
    }
  }
  //cout << opscore << endl;
  //cout << score << endl;
  //score = score-opscore;
  //cout << posmoves << endl;
  //cout << allmoves << endl;
  //cout << peices << endl;
  //cout << score << endl;
  //cout << acallmove << endl;
  int idxmove;
  double best= -100000000;
  int besti;
  int besto;
  for (int nidxmove = 0; nidxmove < acallmove.size()/6; nidxmove++){
    idxmove = nidxmove*6;
    char newboard[8][8];
    char retcolor;
    if (color == 'w'){retcolor = 'b';}
    else{retcolor = 'w';}
    for (int y3 = 0; y3 < 8; y3++){
      for (int x2 = 0; x2 < 8; x2++){
        newboard[y3][x2] = board[y3][x2];
      }
    }
    char c = newboard[acallmove[idxmove+1] - '0'][acallmove[idxmove] - '0'];
    newboard[acallmove[idxmove+1] - '0'][acallmove[idxmove] - '0'] = ' ';
    newboard[acallmove[idxmove+4] - '0'][acallmove[idxmove+3] - '0'] = c;
    if (acallmove[idxmove] == '2' && acallmove[idxmove+1] == '8'){
      for (int y4 = 0; y4 < 8; y4++){
        for (int x3 = 0; x3 < 8; x3++){
          cout << string(1, newboard[y4][x3]) << " ";
        }
        cout << endl;
      }
    }
    int movescore = calcmove3(retcolor, newboard);
    //cout << string(1, acallmove[idxmove]) << string(1, acallmove[idxmove+1]) << string(1, acallmove[idxmove+2]) << string(1, acallmove[idxmove+3]) << string(1, acallmove[idxmove+4]) << " " << movescore << endl;
    if (movescore>best){
      best = movescore;
      besti = idxmove;
      besto = -movescore;
    }
  }
  //cout << string(1, acallmove[besti]) << string(1, acallmove[besti+1]) << string(1, acallmove[besti+2]) << string(1, acallmove[besti+3]) << string(1, acallmove[besti+4]) << " " << to_string(best) << endl;





  return besto;
  }




string calcmove(char color, char board[8][8]){
  string idx1[6] = {"Bishop", "King", "Knight", "Pawn", "Queen", "Rook"};
  char idx2[6] = {'B', 'K', 'N', 'P', 'Q', 'R'};
  string idx3 = "ABCDEFGH";
  int x;
  int y;
  int bsize = 64;
  string peices;
  int bmove[4][2] = {{-1, 1}, {1, -1}, {-1, -1}, {1, 1}};
  int rmove[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
  int qmove[8][2] = {{-1, 1}, {1, -1}, {-1, -1}, {1, 1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}};
  int nmove[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};
  int kmove[8][2] = {{-1, 1}, {1, -1}, {-1, -1}, {1, 1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}};
  int curpos[2];
  int posmoves = 0;
  string acallmove;
  string allmoves;
  string moves;
  string allpeices;
  for (int y2 = 0; y2 < bsize; y2++){
    y = int(floor(y2/8));
    x = y2%8;
    if (board[y][x] != ' '){allpeices += string(1, board[y][x]) + to_string(y) + to_string(x) + " ";}
  }
  if (color == 'w'){
    for (int y1 = 0; y1 < bsize; y1++){

      y = int(floor(y1/8));
      x = y1%8;
      if (board[y][x] >= 'A' && board[y][x] <= 'Z') {
      int n = sizeof(idx2)/sizeof(idx2[0]);
      auto itr = find(idx2, idx2 + n, board[y][x]);
      //cout << idx1[distance(idx2, itr)] << " on " << idx3[x] << to_string(8-y) << endl;
      peices += string(1, board[y][x]) + to_string(y) +to_string(x) + " ";
      if (board[y][x] == 'B'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+bmove[movenum][0] < 0 || curpos[0]+bmove[movenum][0] > 7) || (curpos[1]+bmove[movenum][1] < 0 || curpos[1]+bmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] >= 'A' && board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] <= 'Z'){break;}

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }

            else{
              //cout << "move" << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += bmove[movenum][0];
              curpos[1] += bmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'R'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+rmove[movenum][0] < 0 || curpos[0]+rmove[movenum][0] > 7) || (curpos[1]+rmove[movenum][1] < 0 || curpos[1]+rmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] >= 'A' && board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] <= 'Z'){break;}

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";

              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              moves += string(1, board[y][x]) + to_string(x) + to_string(y) + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += rmove[movenum][0];
              curpos[1] += rmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'Q'){
        for (int movenum = 0; movenum < 8; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+qmove[movenum][0] < 0 || curpos[0]+qmove[movenum][0] > 7) || (curpos[1]+qmove[movenum][1] < 0 || curpos[1]+qmove[movenum][1] > 7))){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] >= 'A' && board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] <= 'Z'){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves +=1;
              curpos[0] += qmove[movenum][0];
              curpos[1] += qmove[movenum][1];
            }
          }

        }
      }

      if (board[y][x] == 'N'){
        for (int a = 0; a < 8; a++){
          //cout << a << endl;
          if (((x+nmove[a][0] < 0 || x+nmove[a][0] > 7) || (y+nmove[a][1] < 0 || y+nmove[a][1] > 7))){
            //cout << "no " << x+nmove[a][0] << y+nmove[a][1] << endl;
            continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]] >= 'A' && board[y+nmove[a][1]][x+nmove[a][0]] <= 'Z'){
            //cout << "no2 " << x+nmove[a][0] << y+nmove[a][1] << endl;
            continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }
          else{
            //cout << "move" << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'K'){
        for (int a = 0; a < 8; a++){

          if (((x+kmove[a][0] < 0 || x+kmove[a][0] > 7) || (y+kmove[a][1] < 0 || y+kmove[a][1] > 7))){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]] >= 'A' && board[y+kmove[a][1]][x+kmove[a][0]] <= 'Z'){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }

          else{
            //cout << "move" << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'P'){
        if (y==6){
          for (int a = 0; a < 2; a++){
            if (y-a-1 < 0 || y-a-1 > 7){break;}
            if (board[y-a-1][x] >= 'A' && board[y-a-1][x] <= 'Z'){break;}
            if (board[y-a-1][x] == ' '){
              //cout << "move" << to_string(x) << " " << to_string(y-a-1) << endl;
              allmoves += string(1, idx3[x]) + to_string(8-(y-a-1)) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y-a-1) + " ";
              posmoves+=1;
              }
            }
          }
        else{
          if (y-1 < 0 || y-1 > 7){break;}
          if (board[y-1][x] >= 'A' && board[y-1][x] <= 'Z'){break;}
          if (board[y-1][x] == ' '){
            //cout << "move" << to_string(x) << " " << to_string(y-1) << endl;
            allmoves += string(1, idx3[x]) + to_string(8-(y-1)) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y-1) + " ";
            posmoves+=1;

            }
        }
        for (int a=0; a<2;a++){
          if (x+(a*2)-1 < 0 || x+(a*2)-1 > 7 || y-1 < 0 || y-1 > 7){continue;}
          if (board[y-1][x+(a*2)-1] >= 'A' && board[y-1][x+(a*2)-1] <= 'Z'){continue;}
          if (board[y-1][x+(a*2)-1] != ' '){
            //cout << "take" << to_string(x+(a*2)-1) << " " << to_string(y-1) << endl;
            posmoves+=1;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+(a*2)-1]) + to_string(8-(y-1)) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+(a*2)-1) + to_string(y-1) + " ";
          }
        }
        }
      }
      }

    }
  //HELP PLEASE
  else{
    for (int y1 = 0; y1 < bsize; y1++){

      y = int(floor(y1/8));
      x = y1%8;
      if (board[y][x] >= 'a' && board[y][x] <= 'z') {
      //int n = sizeof(idx2)/sizeof(idx2[0]);
      //auto itr = find(idx2, idx2 + n, board[y][x]);
      //cout << idx1[distance(idx2, itr)] << " on " << idx3[x] << to_string(8-y) << endl;
      peices += string(1, board[y][x]) + to_string(y) +to_string(x) + " ";
      if (board[y][x] == 'b'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+bmove[movenum][0] < 0 || curpos[0]+bmove[movenum][0] > 7) || (curpos[1]+bmove[movenum][1] < 0 || curpos[1]+bmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] >= 'a' && board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] <= 'z'){break;}

            if (board[curpos[1]+bmove[movenum][1]][curpos[0]+bmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" +  to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }

            else{
              //cout << "move" << to_string(curpos[0]+bmove[movenum][0]) << " " << to_string(curpos[1]+bmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+bmove[movenum][0]]) + to_string(8-curpos[1]+bmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" +  to_string(curpos[0]+bmove[movenum][0]) + to_string(curpos[1]+bmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += bmove[movenum][0];
              curpos[1] += bmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'r'){
        for (int movenum = 0; movenum < 4; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+rmove[movenum][0] < 0 || curpos[0]+rmove[movenum][0] > 7) || (curpos[1]+rmove[movenum][1] < 0 || curpos[1]+rmove[movenum][1] > 7))){
              break;
            }

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] >= 'a' && board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] <= 'z'){break;}

            if (board[curpos[1]+rmove[movenum][1]][curpos[0]+rmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+rmove[movenum][0]) << " " << to_string(curpos[1]+rmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+rmove[movenum][0]]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+rmove[movenum][0]) + to_string(curpos[1]+rmove[movenum][1]) + " ";
              posmoves+=1;
              curpos[0] += rmove[movenum][0];
              curpos[1] += rmove[movenum][1];
            }
          }

        }
      }
      if (board[y][x] == 'q'){
        for (int movenum = 0; movenum < 8; movenum++){
          curpos[0] = x;
          curpos[1] = y;
          for (int a = 0; a < 7; a++){

            if (((curpos[0]+qmove[movenum][0] < 0 || curpos[0]+qmove[movenum][0] > 7) || (curpos[1]+qmove[movenum][1] < 0 || curpos[1]+qmove[movenum][1] > 7))){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] >= 'a' && board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] <= 'z'){break;}

            if (board[curpos[1]+qmove[movenum][1]][curpos[0]+qmove[movenum][0]] != ' '){
              //cout << "take " << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "x" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves+=1;
              break;
            }
            else{
              //cout << "move" << to_string(curpos[0]+qmove[movenum][0]) << " " << to_string(curpos[1]+qmove[movenum][1]) << endl;
              allmoves += string(1, board[y][x]) + string(1, idx3[curpos[0]+qmove[movenum][0]]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(curpos[0]+qmove[movenum][0]) + to_string(curpos[1]+qmove[movenum][1]) + " ";
              posmoves +=1;
              curpos[0] += qmove[movenum][0];
              curpos[1] += qmove[movenum][1];
            }
          }

        }
      }

      if (board[y][x] == 'n'){
        for (int a = 0; a < 8; a++){

          if (((x+nmove[a][0] < 0 || x+nmove[a][0] > 7) || (y+nmove[a][1] < 0 || y+nmove[a][1] > 7))){continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]] >= 'a' && board[y+nmove[a][1]][x+nmove[a][0]] <= 'z'){continue;}

          if (board[y+nmove[a][1]][x+nmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }
          else{
            //cout << "move" << to_string(x+nmove[a][0]) << " " << to_string(y+nmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+nmove[a][0]]) + to_string(y+nmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+nmove[a][0]) + to_string(y+nmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'k'){
        for (int a = 0; a < 8; a++){

          if (((x+kmove[a][0] < 0 || x+kmove[a][0] > 7) || (y+kmove[a][1] < 0 || y+kmove[a][1] > 7))){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]] >= 'a' && board[y+kmove[a][1]][x+kmove[a][0]] <= 'z'){continue;}

          if (board[y+kmove[a][1]][x+kmove[a][0]]  != ' '){
            //cout << "take " << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            continue;
          }

          else{
            //cout << "move" << to_string(x+kmove[a][0]) << " " << to_string(y+kmove[a][1]) << endl;
            allmoves += string(1, board[y][x]) + string(1, idx3[x+kmove[a][0]]) + to_string(y+kmove[a][1]) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x+kmove[a][0]) + to_string(y+kmove[a][1]) + " ";
            posmoves+=1;
            }
        }
      }
      if (board[y][x] == 'p'){
        if (y==1){
          for (int a = 0; a < 2; a++){
            if (y+a+1 < 0 || y+a+1 > 7){break;}
            if (board[y+a+1][x] >= 'a' && board[y+a+1][x] <= 'z'){break;}
            if (board[y+a+1][x] == ' '){
              //cout << "move" << to_string(x) << " " << to_string(y+a+1) << endl;
              allmoves += string(1, idx3[x]) + to_string(8-(y+a+1)) + " ";
              acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y+a+1) + " ";
              posmoves+=1;
              }
            }
          }
        else{
          if (y-1 < 0 || y-1 > 7){break;}
          if (board[y+1][x] >= 'a' && board[y+1][x] <= 'z'){break;}
          if (board[y+1][x] == ' '){
            //cout << "move" << to_string(x) << " " << to_string(y+1) << endl;
            allmoves += string(1, idx3[x]) + to_string(8-(y+1)) + " ";
            acallmove += to_string(x) + to_string(y) + "-" + to_string(x) + to_string(y+1) + " ";
            posmoves+=1;

            }
        }
        for (int a=0; a<2;a++){
          if (x+(a*2)-1 < 0 || x+(a*2)-1 > 7 || y+1 < 0 || y+1 > 7){continue;}
          if (board[y+1][x+(a*2)-1] >= 'a' && board[y+1][x+(a*2)-1] <= 'z'){continue;}
          if (board[y+1][x+(a*2)-1] != ' '){
            //cout << "take" << to_string(x+(a*2)-1) << " " << to_string(y+1) << endl;
            posmoves+=1;
            allmoves += string(1, board[y][x]) + string(1, idx3[x]) + to_string(8-y) + "x" + string(1, idx3[x+(a*2)-1]) + to_string(8-(y+1)) + " ";
            acallmove += to_string(x) + to_string(y) + "x" + to_string(x+(a*2)-1) + to_string(y+1) + " ";
          }
        }
        }
      }
      }

    }
  char pice;
  double peiceval[6] = {3.33, 0, 3.05, 1, 9.5, 5.63};
  double score = 0;
  double opscore = 0;
  //cout << allpeices << endl;
  for (int j = 0; j < (allpeices.size())/4; j++){
    pice = allpeices[j*4];
    if (color == 'w'){
    if (pice == 'B'){score += peiceval[0];}
    if (pice == 'N'){score += peiceval[2];}
    if (pice == 'P'){score += peiceval[3];}
    if (pice == 'Q'){score += peiceval[4];}
    if (pice == 'R'){score += peiceval[5];}
    if (pice == 'b'){opscore += peiceval[0];}
    if (pice == 'n'){opscore += peiceval[2];}
    if (pice == 'p'){opscore += peiceval[3];}
    if (pice == 'q'){opscore += peiceval[4];}
    if (pice == 'r'){opscore += peiceval[5];}
      }
    else{
      if (pice == 'b'){score += peiceval[0];}
      if (pice == 'n'){score += peiceval[2];}
      if (pice == 'p'){score += peiceval[3];}
      if (pice == 'q'){score += peiceval[4];}
      if (pice == 'r'){score += peiceval[5];}
      if (pice == 'B'){opscore += peiceval[0];}
      if (pice == 'N'){opscore += peiceval[2];}
      if (pice == 'P'){opscore += peiceval[3];}
      if (pice == 'Q'){opscore += peiceval[4];}
      if (pice == 'R'){opscore += peiceval[5];}
    }
  }
  //cout << opscore << endl;
  //cout << score << endl;
  //score = score-opscore;
  //cout << posmoves << endl;
  //cout << allmoves << endl;
  //cout << peices << endl;
  //cout << score << endl;
  cout << acallmove << endl;
  int idxmove;
  double best= -100000000;
  int besti;
  for (int nidxmove = 0; nidxmove < acallmove.size()/6; nidxmove++){
    idxmove = nidxmove*6;
    char newboard[8][8];
    char retcolor;
    if (color == 'w'){retcolor = 'b';}
    else{retcolor = 'w';}
    for (int y3 = 0; y3 < 8; y3++){
      for (int x2 = 0; x2 < 8; x2++){
        newboard[y3][x2] = board[y3][x2];
      }
    }
    char c = newboard[acallmove[idxmove+1] - '0'][acallmove[idxmove] - '0'];
    //cout << string(1, c) << " " << to_string(acallmove[idxmove+1] - '0') << " " << to_string(acallmove[idxmove] - '0') << endl;
    newboard[acallmove[idxmove+1] - '0'][acallmove[idxmove] - '0'] = ' ';
    newboard[acallmove[idxmove+4] - '0'][acallmove[idxmove+3] - '0'] = c;
    if (idxmove >= 1111110){
      for (int y4 = 0; y4 < 8; y4++){
        for (int x3 = 0; x3 < 8; x3++){
          cout << string(1, newboard[y4][x3]) << " ";
        }
        cout << endl;
      }
    }
    cout << endl;
    int movescore = calcmove2(retcolor, newboard);
    cout << endl << string(1, acallmove[idxmove]) << string(1, acallmove[idxmove+1]) << string(1, acallmove[idxmove+2]) << string(1, acallmove[idxmove+3]) << string(1, acallmove[idxmove+4]) << " " << to_string(movescore) << endl << endl;
    if (movescore>best){
      best = movescore;
      besti = idxmove;
    }
  }
  cout << string(1, acallmove[besti]) << string(1, acallmove[besti+1]) << string(1, acallmove[besti+2]) << string(1, acallmove[besti+3]) << string(1, acallmove[besti+4]) << " " << to_string(best) << endl;





  return "";
  }








int main() {
  string fen;
  char move;
  for(int hh = 0; hh < 70; hh++){
      string inp;
      string castle;
      string enpassant;
      string moverule;
      string tmoves;
      cout << ":";
      cin >> inp;
      int sequence = 0;
      for (int a = 0; a < inp.size(); a++){
        if (inp[a] == ' '){sequence+=1;continue;}
        if (sequence == 0){fen += string(1, inp[a]);}
        if (sequence == 1){move = inp[a];}
        if (sequence == 2){
          if (inp[a] == '-'){sequence += 1;continue;}
          else{castle += string(1, inp[a]);}
        }
        if (sequence == 70){sequence = 4;}
        if (sequence == 4){
          if (inp[a] >= '0' && inp[a] <= '9'){moverule += string(1, inp[a]);}
          else{sequence = 69;}
        }
        if (sequence == 69){enpassant += string(1, inp[a]);}
        if (sequence == 5){tmoves += string(1, inp[a]);}
      }
      cout << fen << endl << move << endl << castle << endl << enpassant << endl << moverule << endl << tmoves << endl;
      //fen = "rnbqkb1r/ppp1pppp/5n2/3p4/3P4/5N2/PPP1PPPP/RNBQKB1R";
      //move = 'w';
      char board[8][8];
      int curpos = 0;
      int color = 0;
      int actualpos = 0;
      for (int fenpos = 0; fenpos < fen.length(); fenpos++) {
        if (isdigit(fen[fenpos])) {
          string outstr = "";
          for (int b = 0; b < int(fen[fenpos]) - 48; b++) {
            if (curpos % 2 == 0) {
              color = 220;
            } else {
              color = 171;
            }
            //outcolor(to_string(color), to_string(color), to_string(color), "   ");
            board[int(floor(actualpos / 8))][actualpos % 8] = ' ';
            curpos += 1;
            actualpos += 1;
          }
        } else if (fen[fenpos] == '/') {
          cout << endl;
          curpos += 1;
        } else {
          if (curpos % 2 == 0) {
            color = 190;
          } else {
            color = 151;
          }
          if (fen[fenpos] >= 'A' && fen[fenpos] <= 'Z') {
            color += 50;
          } else {
            color -= 50;
          }
          //outcolor(to_string(color), to_string(color), to_string(color),(" " + string(1, (fen[fenpos])) + " "));
          board[int(floor(actualpos / 8))][actualpos % 8] = fen[fenpos];
          curpos += 1;
          actualpos += 1;
        }
      }
      //cout << endl << endl;

      calcmove(move, board);
  }
}
