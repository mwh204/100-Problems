import std.stdio, std.format, std.conv;

immutable auto GRID_SIZE = 5;
immutable ubyte SLVD_FILL = 7;
immutable ubyte SLVD_EMP = 6;
immutable string FRMT = "%0"~ to!string(GRID_SIZE*GRID_SIZE) ~"b";

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
            if(i != 0  && i != SLVD_EMP) count++;
        }else{
            if(i == 0 || i == SLVD_EMP){
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
    ulong sum;
    foreach(i; a.rowHints[row]) sum += i;
    return sum+a.rowHints[row].length > GRID_SIZE || sum == 0;
}

bool isColUnambi(picross a, ubyte col){
    ulong sum;
    foreach(i; a.colHints[col]) sum += i;
    return sum+a.colHints[col].length > GRID_SIZE || sum == 0;
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
            if(a.grid[i][j] != 0 && a.grid[i][j] != SLVD_EMP) {
                write("1 ");
            }else{
                write("0 ");
            }
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
    string s = format(FRMT, i);
    for(int j=0; j<GRID_SIZE*GRID_SIZE; j++){
        int x = j/GRID_SIZE, y = j%GRID_SIZE;
        if(a.grid[x][y] != SLVD_EMP && a.grid[x][y] != SLVD_FILL)
            a.grid[x][y] =  cast(ubyte)(s[(s.length-j-1)]- '0');
    }
    return a;
}

auto setRow(picross a, ubyte row){
  /*sets the row according to the hints
    only to be used with unambiguous rows*/
    ubyte count, k;
    foreach(i, j; a.rowHints[row]){
        //writeln(a.grid[row][count], " ", i, " ", j, " ", count);
        for(k=0;k<j;k++){
            a.grid[row][i+count++] = SLVD_FILL;
            if(i+count<GRID_SIZE) a.grid[row][i+count] = SLVD_EMP;
        }
    }
    return a;
}

auto setCol(picross a, ubyte col){
    /*sets the row according to the hints
    only to be used with unambiguous rows*/
    ubyte count, k;
    foreach(i, j; a.colHints[][col]){
        //writeln(a.grid[i+count++][col], " ", i, " ", j, " ", count);
        for(k=0;k<j;k++){
            a.grid[i+count++][col] = SLVD_FILL;
            if(i+count<GRID_SIZE) a.grid[i+count][col] = SLVD_EMP;
        }
    }
    return a;
}

auto solve(picross a){
    auto correct = false;
    for(ubyte i=0; i<GRID_SIZE; i++){
        if(isRowUnambi(a, i)){
            a = setRow(a, i);
        }
        if(isColUnambi(a, i)){
            a = setCol(a, i);
        }
    }
    for(ulong i=0; i<2^^(GRID_SIZE*GRID_SIZE) && !correct; i++){
        a = genGrid(a, i);
        correct = verifyHint(a);
    }
    return a;
}

void main(){

    ubyte[][5] cl1 = [[5], [1], [1,1,1], [1], [5]];
    ubyte[][5] rw1 = [[1,3], [1,1], [1,1,1], [1,1], [3,1]];

    ubyte[][5] cl2 = [[1], [1,3], [4], [1,3], [1]];
    ubyte[][5] rw2 = [[3], [1], [5], [3], [1,1]];

    picross c = picross(rw2, cl2);
    c = solve(c);
    printPicross(c);
}
