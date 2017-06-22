#include <stdio.h>
#define SIZE 120

int mycmp(char *search, char *str);

int main(int arge,char *argv[]){
	char str[SIZE];
	int decision,line_cont=1;
	FILE *fp;
	//入力の判定
	if (arge != 3) {
		printf("Usage: %s fromFile toFile\n", argv[0]);
		return 1;
	}

	//ファイルを開く
	if ((fp = fopen(argv[2], "r")) == NULL) {
		printf("Failed to open %s.\n", argv[2]);
		return 1;
	}
	
	//処理
	while (fgets(str, SIZE, fp) != NULL) {
		for (int i = 0;; i++) {
			decision = mycmp(argv[1], &(str[i]));     //検索文字列とファイル内の単語を比較
			if (decision == 0 || decision == 2) break;
			if (decision == 1)  break;
		}
		//検索文字列とファイル内の単語が一致でその行を表示
		if (decision == 2) {
			printf("line: %d %s",line_cont,str);
		}
		line_cont++;
	}
	puts("Finish");
	//ファイルを閉じる
	fclose(fp);
}

//文字の比較をする自作関数
int mycmp(char *search, char *c) {
	//易しい場合
	if (*c == EOF)return 0;//ファイルの最後
	else if (*search == '\0') return 2;//検索成功
	else if (*c == '\n')return 1;//行の最後
	else if (*c != *search) return -1;//検索文字列と不一致

	//難しい場合
	mycmp(search + 1, c + 1);

}