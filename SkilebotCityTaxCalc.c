#include <stdio.h>
#include <ctype.h>

int price_input(char* str) {
    int price = 0;
    int errno = 0;
    printf("%s �ְ� �Է� : ", str);
    errno = scanf("%d", &price);
    while (price <= 0 || errno != 1) {
        printf("�ְ��� �ڿ������� �մϴ�.\n");
        printf("%s �ְ� ���Է� : ", str);
        errno = 0;
        while (getchar() != '\n');
        errno = scanf("%d", &price);
    }
    while (getchar() != '\n');
    return price;
}
/** commandInput - ���ڸ� �Է¹��� �Լ�.
 * @return int  1 - ���ĺ��� �ƴ� ��.
 * @return ch - �Է¹��� ����.
 */
char commandInput() {
    char ch = 0;
    int i = 0;
    int flag = 1;
    char command = 0;
    while ((ch = getchar()) != '\n') {
        if (!isalpha(ch)) {
            flag = 0;
            break;
        }
        command = ch;
        i++;
    }
    if (i != 1 || !flag) {
        printf("�߸� �Է��ϼ̽��ϴ�.\n");
        return commandInput();
    }
    return command;
}

/** buildingInput - ������ �迭�� �Է¹��� �Լ�
 * @param str - ���ڿ� �Է½� ���޹��� char*�� �迭
 * @param size - str�� size
 */
int buildingInput(char* str, int size) {
    char ch = 0;
    int i = 0;
    while ((i < size - 1) && (ch = getchar() != '\n')) {
        if (isalpha(ch)) {
            if (str != NULL) { // �ǹ� �迭 �Է� �� ������ �� str �迭
                str[i] = ch;
            }
        }
        else {
            return 0;
        }
        i++;
    }
    str[size - 1] = '\0';
    return 1;
}


void loop() {
    int green = 0, lus = 0;
    char ch;
    green = price_input("�׸��Ǽ�");
    lus = price_input("��������");

    printf("�������� �ָ����� �Է��ϼ���.(y/N)\n");
    ch = commandInput();
    printf("�׸�: %d, ����: %d\n", green, lus);
    printf("command: %c\n", ch);

}
int main() {
    printf("��Į�� ������ ���� ��� ���α׷��Դϴ�.\n");
    //printf("���α׷��� �����Ͻ÷��� q�� �����Ϸ��� r�� �Է��ϼ���.\n");
    loop();
    return 0;
}