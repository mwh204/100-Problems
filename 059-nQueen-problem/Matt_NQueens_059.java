public class Matt_NQueens_059 {
  
  static final int N = 8;
  
  public static void main(String[] args) { 
    int[] board = new int[N];
    int y=0;
    int solutions = 0;
    board[0] = -1;
    
    while(y >= 0){
      do{
        board[y]++;
      }while(board[y] < N && isUnsafe(y, board));
      
      if (board[y] < N) {
        if (y < (N - 1)){
          board[++y] = -1;
        } else{
          solutions++;
          drawboard(board, solutions);
        }
      } else{
        y--;
      }
    }
  }
  
  public static boolean isUnsafe(int y, int[] board){
    int x = board[y];
    for(int i=1; i<= y; i++){
      int t = board[y-i];
      if(t == x || t == x-i || t == x + i){
        return true;
      }
    }
    return false;
  }
  
  public static void drawboard(int[] board, int solutions){
    System.out.println("\nSolution #"+solutions+"\n");
    for(int y=0; y<N; y++){
      for(int x=0; x<N; x++){
        System.out.print(board[y] == x? "|Q" : "|_");
      }
      System.out.println();
    }
  }
}
