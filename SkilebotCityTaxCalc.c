#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int price_input(char* str) {
    int price = 0;
    int errnum = 0;
    printf("%s 주가 입력 : ", str);
    errnum = scanf("%d", &price);
    while (price <= 0 || errnum != 1) {
        printf("주가는 자연수여야 합니다.\n");
        printf("%s 주가 재입력 : ", str);
        errnum = 0;
        while (getchar() != '\n');
        errnum = scanf("%d", &price);
    }
    while (getchar() != '\n');
    return price;
}
/** commandInput - 문자를 입력받을 함수.
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
        }
        command = ch;
        i++;
    }
    if (!i) command = ch;
    if (i > 1 || !flag) {
        printf("잘못 입력하셨습니다. \n");
        return commandInput();
    }
    return tolower(command);
}

int check_buildings(char* str, int size) {
    int i = 0;
    if (str == NULL) return -1;
    for (i = 0; str[i] != '\0' && i < size - 1; i++) {
        char c = str[i];
        if (c < 97 || (c > 109 && c != 120)) return 0;

        else if (c == 106 && (i != 0 && i != 6)) {
            printf("항구는 맨 끝 칸에 배치하세요. \n");
            return 0;
        }
    }
    return 1;
}

/** buildingInput - 빌딩의 배열을 입력받을 함수
 * @param str - 문자열 입력시 전달받을 char*형 배열
 * @param size - str의 size
 */
int buildingInput(char* str, int size) {
    char ch = 0;
    int i = 0, overcount=0;
    if (str == NULL) return -1;
    while ((i < size - 1) && ((ch = getchar()) != '\n')) {  // 7자리 완료 또는 그 전에 입력이 끝난 경우 종료.
        if (isalpha(ch)) {
            str[i] = tolower(ch);
        }
        else {
            while (getchar() != '\n'); // 버퍼 비우기
            return 0;
        }
        i++;
    }
    if (i < size - 1) return 0;
    while ((ch = getchar()) != '\n') {  // If i==7, then getchar() == \n
        overcount++;        // 7자리를 넘어서 입력한 경우
    }
    if (overcount > 0) return 0;
    str[i] = '\0';
    return check_buildings(str, size);
}

int alphatoint(char a) {
    if (a < '0' || a>'9') return -1;
    return a - '0';
}
double alphatofloat(const char* cast_str) {
    double Dec_Val = 0;
    double Dou_val = 0;
    double Multiple = 1;
    double sign = 1;

    while (*cast_str)
        cast_str++;
    if (*cast_str == '\0')
        return 0;
    if (*cast_str == '+' || *cast_str == '-') {
        if (*cast_str == '+')
            sign = 1;
        else
            sign = -1;
    }
    while ((*cast_str && *cast_str != '/') && *cast_str >= '0' && *cast_str <= '9' || *cast_str == '.')
    {
        if (*cast_str == '.')
        {
            *cast_str++;
            while ((*cast_str && *cast_str != '/') && *cast_str >= '0' && *cast_str <= '9')
            {
                Dou_val = (Dou_val * 10) + (*cast_str - '0');
                Multiple = 0.1 * Multiple;
                *cast_str++;
            }
            Dou_val = Dou_val * Multiple;
        }
        else
        {
            Dec_Val = (Dec_Val * 10) + (*cast_str - '0');
            *cast_str++;
        }
    }
    return sign * (Dec_Val + Dou_val);
}

void loop() {
    int green = 0, lus = 0;
    int weekend = 0;    //기본값은 평일, 1-토요일, 2-일요일
    char ch;
    green = price_input("그린건설");
    lus = price_input("러스관광");

    printf("산출일이 주말인지 입력하세요.(y/N) ");
    ch = commandInput();
    while (ch != 'y' && ch != 'n' && ch != '\n') {
        ch = commandInput();
    }
    if (ch == 'y') {
        printf("일요일이면 y, 토요일이면 n을 입력하세요.(y/N) ");
        ch = commandInput();
        while (ch != 'y' && ch != 'n' && ch != '\n') {
            ch = commandInput();
        }
        if (ch == 'y') weekend = 2;
        else weekend = 1;
    }
    printf("공터=x, 주택=a, 편의점=b, 학교=c, 회사=d\n");
    printf("병원=e, 은행=f, 백화점-g, 호텔=h, 카지노=i\n");
    printf("항구=j, 경기장=k, 교회=l, 공장=m\n");
    printf("배열할 건물을 띄어쓰기 없이 7자리 적으세요: ");

    char buildings[8];
    ch = buildingInput(buildings, sizeof(buildings)/sizeof(char));
    while (!ch) {
        printf("잘못 입력하셨습니다.\n");
        printf("배열할 건물을 띄어쓰기 없이 7자리 적으세요: ");
        ch = buildingInput(buildings, sizeof(buildings) / sizeof(char));
    }

    char b_key[14] = { 'x', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm' };
    int multiples[7] = { 1, 1, 1, 1, 1, 1, 1 };
    char gontor[] = "2213_#4/312_#0.7"; //"110_#0.5";      // place, num_build, build1_, build2_, ... , #efficient
    {
        unsigned char first_build = 0;        // b0 0 0 0  0 0 0 0 
        unsigned char second_build = 0;
        int num_ef = alphatoint(gontor[0]);
        int i = 1;
        for (int j = 0; j < num_ef; j++) {
            int place = alphatoint(gontor[i]);  // i==1
            i++;
            int num_build = alphatoint(gontor[i]);  //i==2
            if (num_build == 0) {
                first_build = 255;
                second_build = 63;
            }
            int k = i;
            int n = 0;
            for (k = i + 1; gontor[k]!='#'; k++) {
                if (gontor[k] == '_') {
                    if (n != 0) {
                        if (n < 8) {
                            first_build += 1 << n;
                        }
                        else {
                            second_build += 1 << (n - 8);
                        }
                    }
                    n = 0;
                    continue;
                }
                else if (n == 0)
                    n = alphatoint(gontor[k]);
                else
                {
                    n *= 10;
                    n += alphatoint(gontor[k]);

                }
                
            }
            k++;
            double efficient = atof(&gontor[k]);  // 3
            k++;
            printf("place: %d\n", place);
            printf("num_build = %d\n", num_build);
            printf("efficient = %lf\n", efficient);
            i = k + 1;
        }
        
    }
    /*{('공터', 1, (1, 0, 0.5)),
        ('주택', 0), ('편의점', 2, (2, 2, 1, 3, 4), (3, 1, 2, 0.7)), ('학교', 2, (4, 1, 1, 3), (2, 1, 8, 0.5)),
        ('회사', 1, (3, 10, 1, 2, 5, 6, 7, 8, 10, 11, 12, 13, 2)), ('병원', 1, (0, 0, 1.5)),
        ('은행', 1, (1, 1, 5, 5)),
        ('백화점', 2, (1, 0, 3, 5), (0, 1, 2, 0)),
        ('호텔', 2, (0, 9, 2, 4, 5, 6, 7, 10, 11, 12, 13, 2), (0, 1, 1, 0.5)),
        ('카지노', 3, (2, 1, 1, 0.5), (0, 1, 9, 0.5), (1, 1, 8, 2)), ('항구', 1, (0, 3, 8, 9, 10, 3)),
        ('경기장', 1, (2, 0, 0.2)), ('교회', 1, [2, 2, 1, 4, 1.5]), ('공장', 1, (3, 0, 0)))*/
    // ('건물이름', 효과 개수, (place, 건물종류개수, 종류,.. , 효과)..)
    // 효과 개수 == 0, nothing
    // place == 0, 전범위,
    // 건물종류개수 == 0, 모든 건물, 종류X

    printf("그린: %d, 러스: %d\n", green, lus);
    printf("weekend: %d\n", weekend);
    printf("buildings: %s\n", buildings);
    printf("buildings log: %d\n", ch);

}
int main() {
    printf("슷칼봇 도시의 집세 계산 프로그램입니다.\n");
    //printf("프로그램을 종료하시려면 q를 리셋하려면 r을 입력하세요.\n");
    loop();
    return 0;
}