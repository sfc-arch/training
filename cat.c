//cat command
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc ,char *argv[]){   //int型の変数argcとchar型のポインタ変数argvが引数
	int fd;                    //int型の変数fdとlenを宣言
	char buf[256];           //char型の配列bufを宣言、大きさは256
	int len;

	if(argc != 2){        //argcが2でなければエラーを返す
	return -1;
	}

	fd = open(argv[1], O_RDONLY);  //openを呼び出してその戻り値をfdに格納する、読み込み専用

  if (fd == -1) {           //fdに読み込みが無い場合、エラーを返す
    return -1;
    }

  while (1) {          //whileに真を与えてるので反復構造が無限に行われる
    len = read(fd,buf,sizeof(buf));   //readを呼び出してその戻り値をlenに格納する、bufには一時的にfdの内容を記憶させておく

    if (len > 0){             //lenに値が入っているか(読み込んでいるか)を判断
      write (1, buf, len);   //fdの1番でbufに記憶させたデータを出力する
    } 
    
    else if (len == 0){       //lenに書き込みがない場合、中断
      break;
    } 
    
    else {             //lenの値が負の場合、エラーを返す
    return -1;  
    }
  }
  close(fd);        //fdを終了する
  return (0);
}

