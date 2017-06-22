#include <stdio.h>
#define SIZE 120

int mycmp(char *search, char *str);

int main(int arge,char *argv[]){
	char str[SIZE];
	int decision,line_cont=1;
	FILE *fp;
	//���͂̔���
	if (arge != 3) {
		printf("Usage: %s fromFile toFile\n", argv[0]);
		return 1;
	}

	//�t�@�C�����J��
	if ((fp = fopen(argv[2], "r")) == NULL) {
		printf("Failed to open %s.\n", argv[2]);
		return 1;
	}
	
	//����
	while (fgets(str, SIZE, fp) != NULL) {
		for (int i = 0;; i++) {
			decision = mycmp(argv[1], &(str[i]));     //����������ƃt�@�C�����̒P����r
			if (decision == 0 || decision == 2) break;
			if (decision == 1)  break;
		}
		//����������ƃt�@�C�����̒P�ꂪ��v�ł��̍s��\��
		if (decision == 2) {
			printf("line: %d %s",line_cont,str);
		}
		line_cont++;
	}
	puts("Finish");
	//�t�@�C�������
	fclose(fp);
}

//�����̔�r�����鎩��֐�
int mycmp(char *search, char *c) {
	//�Ղ����ꍇ
	if (*c == EOF)return 0;//�t�@�C���̍Ō�
	else if (*search == '\0') return 2;//��������
	else if (*c == '\n')return 1;//�s�̍Ō�
	else if (*c != *search) return -1;//����������ƕs��v

	//����ꍇ
	mycmp(search + 1, c + 1);

}