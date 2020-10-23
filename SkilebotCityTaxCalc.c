#include <stdio.h>
#include <ctype.h>

int price_input(char* str) {
    int price = 0;
    int errno = 0;
    printf("%s 주가 입력 : ", str);
    errno = scanf("%d", &price);
    while (price <= 0 || errno != 1) {
        printf("주가는 자연수여야 합니다.\n");
        printf("%s 주가 재입력 : ", str);
        errno = 0;
        while (getchar() != '\n');
        errno = scanf("%d", &price);
    }
    while (getchar() != '\n');
    return price;
}
/** commandInput - 문자를 입력받을 함수.
 * @return int  1 - 알파벳이 아닐 때.
 * @return ch - 입력받은 문자.
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
        printf("잘못 입력하셨습니다.\n");
        return commandInput();
    }
    return command;
}

/** buildingInput - 빌딩의 배열을 입력받을 함수
 * @param str - 문자열 입력시 전달받을 char*형 배열
 * @param size - str의 size
 */
int buildingInput(char* str, int size) {
    char ch = 0;
    int i = 0;
    while ((i < size - 1) && (ch = getchar() != '\n')) {
        if (isalpha(ch)) {
            if (str != NULL) { // 건물 배열 입력 시 전달해 줄 str 배열
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
    green = price_input("그린건설");
    lus = price_input("러스관광");

    printf("산출일이 주말인지 입력하세요.(y/N)\n");
    ch = commandInput();
    printf("그린: %d, 러스: %d\n", green, lus);
    printf("command: %c\n", ch);

}
int main() {
    printf("슷칼봇 도시의 집세 계산 프로그램입니다.\n");
    //printf("프로그램을 종료하시려면 q를 리셋하려면 r을 입력하세요.\n");
    loop();
    return 0;
}