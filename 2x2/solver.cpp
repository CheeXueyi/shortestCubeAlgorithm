#include <queue>
#include <string>
#include <iostream>
#include <unordered_map> 

using namespace std;

#define CUBETYPE "2x2"
#define NUM_FACE_TILES 4
#define MAX_MOVES 20

// X = turn face on X side by 90 degrees clockwise, 
// Xp = turn face on X side by 90 degrees counter-clockwiseb 
enum Move { U, Up, R, Rp, L, Lp, B, Bp, F, Fp, D, Dp, X, Xp, Y, Yp, Z, Zp };
Move movelist[18] = { U, Up, R, Rp, L, Lp, B, Bp, F, Fp, D, Dp, X, Xp, Y, Yp, Z, Zp };
string movelistStr[18] = { "U", "U\'", "R", "R\'", "L", "L\'", "B", "B\'", "F", "F\'", "D", "D\'", "X", "X\'", "Y", "Y\'", "Z", "Z\'" };

bool validColourCode(char colour) {
    if (
        colour != 'w' && colour != 'y' && colour != 'g' 
        && colour != 'b' && colour != 'r' && colour != 'o'
    ) {
        return false;
    } else {
        return true;
    }
}

void printScrambleHelp() {
    cout << "colour guide:\nw = white, y = yellow, g = green,\nb = blue, o = orange, r = red\n" << "\n";
    cout << "Enter the colours of the face from left to right, top to bottom while ";
    cout << "facing the given face.\n";
    cout << "example: white on top left, blue on top right, green on bottom left, red on bottom right\n";
    cout << "input: wbgr\n";
}

bool isValidFace(string face) {
    if (face.length() != NUM_FACE_TILES) {
        cout << "INVALID NUMBER OF TILES!\n";
        return false;
    } 

    for (int i = 0; i < NUM_FACE_TILES; i++) {
        if (!validColourCode(face[i])) {
            cout << "INVALID COLOUR!\n";
            return false;
        }
    }

    return true;
}

/**
 * Scramble is a string of NUM_FACE_TILES * 6 chars. 
 * Face order is: top -> front -> right -> back -> left -> bottom.
 * On each face, tile order is left to right and top to bottom. For example:
 * -------------
 * |     |     |
 * |  0  |  1  |
 * |     |     |
 * -------------
 * |     |     |
 * |  2  |  3  |
 * |     |     |
 * -------------
 * 
*/
string readScramble() {
    string faceOutput[6] = {
        "Top face", "Front face", "Right face", 
        "Back face", "Left face", "Bottom face"
    };
    string scramble = "";

    for (int i = 0; i < 6; i++) {
        cout << faceOutput[i] << ": \n";
        string face = "";
        cin >> face;
        if(isValidFace(face)) {
            scramble += face;
        } else {
            i--;
        }
    }

    return scramble;
}

/**
 * Makes a move on the given cube scramble.
*/
string cubeMove(string originalScramble, Move move) {
    if (originalScramble.length() != NUM_FACE_TILES * 6) {
        cout << "INVALID SCRAMBLE LENGTH\n";
    }
    char temp, tempLeft, tempRight;
    string middle;
    switch(move) {
        case U:
            // shift top face
            temp = originalScramble[0];
            originalScramble[0] = originalScramble[2];
            originalScramble[2] = originalScramble[3];
            originalScramble[3] = originalScramble[1];
            originalScramble[1] = temp;

            // shift side faces
            tempLeft = originalScramble[4];
            tempRight = originalScramble[5];

            originalScramble[4] = originalScramble[8];
            originalScramble[5] = originalScramble[9];

            originalScramble[8] = originalScramble[12];
            originalScramble[9] = originalScramble[13];

            originalScramble[12] = originalScramble[16];
            originalScramble[13] = originalScramble[17];

            originalScramble[16] = tempLeft;
            originalScramble[17] = tempRight;
            break;
        case Up:
            // shift top face
            temp = originalScramble[0];
            originalScramble[0] = originalScramble[1];
            originalScramble[1] = originalScramble[3];
            originalScramble[3] = originalScramble[2];
            originalScramble[2] = temp;

            // shift side faces
            tempLeft = originalScramble[4];
            tempRight = originalScramble[5];

            originalScramble[4] = originalScramble[16];
            originalScramble[5] = originalScramble[17];

            originalScramble[16] = originalScramble[12];
            originalScramble[17] = originalScramble[13];

            originalScramble[12] = originalScramble[8];
            originalScramble[13] = originalScramble[9];

            originalScramble[8] = tempLeft;
            originalScramble[9] = tempRight;
            break;
        case F:
            // front face
            temp = originalScramble[4];
            originalScramble[4] = originalScramble[6];
            originalScramble[6] = originalScramble[7];
            originalScramble[7] = originalScramble[5];
            originalScramble[5] = temp;

            // shift side faces
            tempLeft = originalScramble[2];
            tempRight = originalScramble[3];

            originalScramble[2] = originalScramble[19];
            originalScramble[3] = originalScramble[17];

            originalScramble[19] = originalScramble[21];
            originalScramble[17] = originalScramble[20];
            
            originalScramble[21] = originalScramble[8];
            originalScramble[20] = originalScramble[10];

            originalScramble[8] = tempLeft;
            originalScramble[10] = tempRight;
            break;
        case Fp:
            // front face
            temp = originalScramble[4];
            originalScramble[4] = originalScramble[5];
            originalScramble[5] = originalScramble[7];
            originalScramble[7] = originalScramble[6];
            originalScramble[6] = temp;

            // shift side faces
            tempLeft = originalScramble[2];
            tempRight = originalScramble[3];

            originalScramble[2] = originalScramble[8];
            originalScramble[3] = originalScramble[10];

            originalScramble[8] = originalScramble[21];
            originalScramble[10] = originalScramble[20];
            
            originalScramble[21] = originalScramble[19];
            originalScramble[20] = originalScramble[17];

            originalScramble[19] = tempLeft;
            originalScramble[17] = tempRight;
            break;
        case R:
            // right face
            temp = originalScramble[8];
            originalScramble[8] = originalScramble[10];
            originalScramble[10] = originalScramble[11];
            originalScramble[11] = originalScramble[9];
            originalScramble[9] = temp;

            // shift adjacent faces
            tempLeft = originalScramble[3];
            tempRight = originalScramble[1];

            originalScramble[3] = originalScramble[7];
            originalScramble[1] = originalScramble[5];

            originalScramble[7] = originalScramble[23];
            originalScramble[5] = originalScramble[21];

            originalScramble[23] = originalScramble[12];
            originalScramble[21] = originalScramble[14];

            originalScramble[12] = tempLeft;
            originalScramble[14] = tempRight;
            break;
        case Rp:
            // right face
            temp = originalScramble[8];
            originalScramble[8] = originalScramble[9];
            originalScramble[9] = originalScramble[11];
            originalScramble[11] = originalScramble[10];
            originalScramble[10] = temp;

            // shift adjacent faces
            tempLeft = originalScramble[3];
            tempRight = originalScramble[1];

            originalScramble[3] = originalScramble[12];
            originalScramble[1] = originalScramble[14];

            originalScramble[12] = originalScramble[23];
            originalScramble[14] = originalScramble[21];

            originalScramble[23] = originalScramble[7];
            originalScramble[21] = originalScramble[5];

            originalScramble[7] = tempLeft;
            originalScramble[5] = tempRight;
            break; 
        case L:
            // left face
            temp = originalScramble[16];
            originalScramble[16] = originalScramble[18];
            originalScramble[18] = originalScramble[19];
            originalScramble[19] = originalScramble[17];
            originalScramble[17] = temp;

            // shift adjacent faces
            tempLeft = originalScramble[0];
            tempRight = originalScramble[2];

            originalScramble[0] = originalScramble[15];
            originalScramble[2] = originalScramble[13];

            originalScramble[15] = originalScramble[20];
            originalScramble[13] = originalScramble[22];

            originalScramble[20] = originalScramble[4];
            originalScramble[22] = originalScramble[6];

            originalScramble[4] = tempLeft;
            originalScramble[6] = tempRight;
            break;
        case Lp:
            // left face
            temp = originalScramble[16];
            originalScramble[16] = originalScramble[17];
            originalScramble[17] = originalScramble[19];
            originalScramble[19] = originalScramble[18];
            originalScramble[18] = temp;

            // shift adjacent faces
            tempLeft = originalScramble[0];
            tempRight = originalScramble[2];

            originalScramble[0] = originalScramble[4];
            originalScramble[2] = originalScramble[6];

            originalScramble[4] = originalScramble[20];
            originalScramble[6] = originalScramble[22];

            originalScramble[20] = originalScramble[15];
            originalScramble[22] = originalScramble[13];

            originalScramble[15] = tempLeft;
            originalScramble[13] = tempRight;
            break;
        case D:
            // bottom face
            temp = originalScramble[20];
            originalScramble[20] = originalScramble[22];
            originalScramble[22] = originalScramble[23];
            originalScramble[23] = originalScramble[21];
            originalScramble[21] = temp;

            // shift adjacent faces
            tempLeft = originalScramble[6];
            tempRight = originalScramble[7];

            originalScramble[6] = originalScramble[18];
            originalScramble[7] = originalScramble[19];

            originalScramble[18] = originalScramble[14];
            originalScramble[19] = originalScramble[15];

            originalScramble[14] = originalScramble[10];
            originalScramble[15] = originalScramble[11];

            originalScramble[10] = tempLeft;
            originalScramble[11] = tempRight;
            break;
        case Dp:
            // bottom face
            temp = originalScramble[20];
            originalScramble[20] = originalScramble[21];
            originalScramble[21] = originalScramble[23];
            originalScramble[23] = originalScramble[22];
            originalScramble[22] = temp;

            // shift adjacent faces
            tempLeft = originalScramble[6];
            tempRight = originalScramble[7];

            originalScramble[6] = originalScramble[10];
            originalScramble[7] = originalScramble[11];

            originalScramble[10] = originalScramble[14];
            originalScramble[11] = originalScramble[15];

            originalScramble[14] = originalScramble[18];
            originalScramble[15] = originalScramble[19];

            originalScramble[18] = tempLeft;
            originalScramble[19] = tempRight;
            break;
        case B:
            // back face
            temp = originalScramble[12];
            originalScramble[12] = originalScramble[14];
            originalScramble[14] = originalScramble[15];
            originalScramble[15] = originalScramble[13];
            originalScramble[13] = temp;

            // shift adjacent faces
            tempLeft = originalScramble[0];
            tempRight = originalScramble[1];

            originalScramble[0] = originalScramble[9];
            originalScramble[1] = originalScramble[11];

            originalScramble[9] = originalScramble[23];
            originalScramble[11] = originalScramble[22];

            originalScramble[23] = originalScramble[18];
            originalScramble[22] = originalScramble[16];

            originalScramble[18] = tempLeft;
            originalScramble[16] = tempRight;
            break;
         case Bp:
            // back face
            temp = originalScramble[12];
            originalScramble[12] = originalScramble[13];
            originalScramble[13] = originalScramble[15];
            originalScramble[15] = originalScramble[14];
            originalScramble[14] = temp;

            // shift adjacent faces
            tempLeft = originalScramble[0];
            tempRight = originalScramble[1];

            originalScramble[0] = originalScramble[18];
            originalScramble[1] = originalScramble[16];

            originalScramble[18] = originalScramble[23];
            originalScramble[16] = originalScramble[22];

            originalScramble[23] = originalScramble[9];
            originalScramble[22] = originalScramble[11];

            originalScramble[9] = tempLeft;
            originalScramble[11] = tempRight;
            break;
        case X:
            // left and right face rotations
            middle = cubeMove(originalScramble, Lp);
            originalScramble = cubeMove(middle, R);
            break;
        case Xp:
            middle = cubeMove(originalScramble, L);
            originalScramble = cubeMove(middle, Rp);
            break;
        case Y:
            middle = cubeMove(originalScramble, U);
            originalScramble = cubeMove(middle, Dp);
            break;
        case Yp:
            middle = cubeMove(originalScramble, Up);
            originalScramble = cubeMove(middle, D);
            break;
        case Z:
            middle = cubeMove(originalScramble, F);
            originalScramble = cubeMove(middle, Bp);
            break;
        case Zp:
            middle = cubeMove(originalScramble, Fp);
            originalScramble = cubeMove(middle, B);
            break;
        default:
            cout << "INVALID MOVE\n";
    }

    return originalScramble;
}

/**
 * Finds the shortest algorithm to go from the `start` scramble to `end` scramble.
 * Assumes that the given scrambles are valid scrambles.
*/
string cubeShortestMove(string start, string end) {
    unordered_map<string, string> prevMove;
    unordered_map<string, string> prevScramble;
    queue<string> q;
    
    prevMove[start] = "START";
    prevScramble[start] = "START";
    q.push(start);

    int currScrambles = 1;
    int numMoves = 0;
    bool algoFound = false;
    while (numMoves < MAX_MOVES) {
    
        int nextScrambles = 0;
        for (int i = 0; i < currScrambles; i++) {
            string currScramble = q.front();
            q.pop();

            for (int j = 0; j < 18; j++) {
                string newScramble = cubeMove(currScramble, movelist[j]);
                if (prevMove.find(newScramble) == prevMove.end()) {
                    // scramble is not visited yet
                    prevMove[newScramble] = movelistStr[j];
                    prevScramble[newScramble] = currScramble;
                    q.push(newScramble);
                    nextScrambles++;
                    
                    if (newScramble == end) {
                        algoFound = true;
                        break;
                    }
                }
            }

            if (algoFound) {
                break;
            }
            currScrambles = nextScrambles;
            numMoves++;
        }

        if (algoFound) {
            break;
        }
    }
    
    if (algoFound) {
        string algo = "";
        string curr = end;
        while (prevMove[curr] != "START") {
            algo = prevMove[curr] + algo;
            curr = prevScramble[curr];
        }

        return algo;
    } else {
        return "No algo found";
    }
}

int main(void) {
    string start = readScramble();
    string end = readScramble();
    string shortestAlgo = cubeShortestMove(start, end);
    cout << "shortest algo is: \n" << shortestAlgo << '\n';
    return 0; 
}