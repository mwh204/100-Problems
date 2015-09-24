import std.stdio, std.format;

immutable auto GRID_SIZE = 5;
immutable auto MAX_HINTS = (GRID_SIZE/2 + GRID_SIZE%2);

struct picross {
    ubyte grid[GRID_SIZE][GRID_SIZE];
    ubyte rowHints[GRID_SIZE][];
    ubyte colHints[GRID_SIZE][];

    this(ubyte g[GRID_SIZE][GRID_SIZE]){
        grid = g;

        for(ubyte i=0; i<GRID_SIZE; i++){
            rowHints[i] = getHint(grid[i]);
            colHints[i] = getHint(colToArr(grid, i));
        }
    }

    this(int n){
        for(ubyte i=0; i<GRID_SIZE; i++){
            //get input
        }
    }

    this(ubyte r[GRID_SIZE][], ubyte c[GRID_SIZE][]){
        rowHints = r;
        colHints = c;
    }
}

bool verifyHint(picross a){
    bool x = true;
    ubyte i;
    for(i=0; i<GRID_SIZE && x; i++){
        x = x && (a.rowHints[i] == getHint(a.grid[i])) && a.colHints[i] == getHint(colToArr(a.grid, i));
        //writeln(x, " ", a.rowHints[i], " == ", getHint(a.grid[i]),  " ", a.colHints[i], " == ", getHint(colToArr(a.grid, i)));
    }
    return x;
}

auto rowSum(picross a, ubyte row){
    int sum;
    foreach(int i ; a.grid[row]){
        sum += i;
    }
    return sum;
}

auto getHint(ubyte[] row){
    ubyte[] hint;
    ubyte count;
    foreach(i ; row){
        if(count == 0){
            if(i != 0) count++;
        }else{
            if(i == 0){
                hint ~= count;
                count = 0;
            }else{
                count++;
            }
        }
    }
    if(count != 0 || hint.length == 0) hint ~= count;
    return hint;
}

auto colToArr(ubyte[GRID_SIZE][GRID_SIZE] a, ubyte col){
    ubyte[] arr;
    foreach(i; a[][]){
        arr ~= i[col];
    }
    return arr;
}

bool isRowUnambi(picross a, ubyte row){
/*A row is "Unambiguous" if there is only one
    possible placement, eg for a size 5 grid
    [0], [1,1,1], [2, 2], [3, 1], [1, 3] [5]
    are all unambiguous*/
    int prod;
    foreach(i; a.rowHints[row]) prod += i;
    prod*=a.rowHints[row].length;
    return prod >= GRID_SIZE;
}

void printPicross(picross a){
    ubyte i, j;
    auto b = false;
    for(i=0; i<GRID_SIZE; i++){
        write("\t");
        for(j=0; j<GRID_SIZE; j++){
            if(a.colHints[j][].length > i){
                write(a.colHints[j][i], " ");
                b = true;
            }else{
                write("  ");
            }
        }
        if(b){
            writeln();
            b = false;
        }
    }
    writeln();
    for(i=0; i<GRID_SIZE; i++){
        foreach(k; a.rowHints[i][]) write(k, " ");
        write("\t");
        for(j=0; j<GRID_SIZE; j++){
            write(a.grid[i][j], " ");
        }
        writeln();
    }
}

auto bruteForce(picross a){
    auto correct = false;
    for(ulong i=0; i<2^^(GRID_SIZE*GRID_SIZE) && !correct; i++){
        a = genGrid(a, i);
        correct = verifyHint(a);
    }
    return a;
}

auto genGrid(picross a, ulong i){
    string s = format("%025b", i);
    for(int j=0; j<25; j++){
        a.grid[j/GRID_SIZE][j%GRID_SIZE] =  cast(ubyte)(s[(s.length-j-1)]- '0');
    }
    return a;
}

void main(){
    ubyte[GRID_SIZE][GRID_SIZE] zz = [[2,2,2,2,2], [2,0,0,0,2], [2,0,0,0,2], [2,0,0,0,2], [2,2,2,2,2]];
    ubyte[][5] rw = [[5], [1], [1,1,1], [1], [5]];
    ubyte[][5] cl = [[3,1], [1,1], [1,1,1], [1,1], [1,3]];
    picross c = picross(rw, cl);
    c = bruteForce(c);
    printPicross(c);
}
