#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int alphatoint(char a);
double alphatofloat(const char* cast_str);

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
/** commandInput - 문자를 입력받을 함수. 두 글자 이상이거나 알파벳 또는 '\n'이 아닌 다른 문자가 있을 경우 재 입력.
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

/** weekendInput - 주말에 대한 입력 함수
 *  @return weekend - 0_평일, 1_토요일, 2_일요일
 */
int weekendInput() {
    char ch = 0;
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
        if (ch == 'y') return 2;
        else return 1;
    }
    return 0;
}

/**check_buildings - 건설한 building 목록을 검증해주는 함수.
 * @return 1   - 정상일 때
 * @return 0   - 잘못된 입력일 때
 * @return -1  - str == NULL 일 때
 */
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
 * @param str - 문자열 입력시 전달받을 char형 배열 주소
 * @param size - str의 size
 */
int buildingInput(char* str, int size) {
    char ch = 0;
    int i = 0, overcount = 0;
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
    while ((ch = getchar()) != '\n') {  // If i==size-1, then getchar() == \n. in condition of short circuit evaluation
        overcount++;        // 7자리를 넘어서 입력한 경우
    }
    if (overcount > 0) return 0;
    str[i] = '\0';
    return check_buildings(str, size);
}


void applyEffect(float* multiples, char* buildings, int weekend) {
    char b_arr[15] = { 'x', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', NULL };
    char gontor[] = "1/10.#0.5"; 
    char house[] = "0";
    char convenience[] = "2/22.1_3_#4\0/31.2_#0.7";
    char company[] = "1/310.1_2_5_6_7_8_10_11_12_13_#2";
    char school[] = "2/41.1_#3\0/21.8_#0.5";
    char* effects[] = { gontor, house, convenience, school };
        // 효과 개수, (place, 건물종류개수, 종류,.. , 효과), ...
        // num_ef. ('/',  place, num_build. , build1_, build2_, ... , #coefficient'\0')
        // 효과 개수 == 0, nothing
        // place == 0, 전범위,
        // 건물종류개수 == 0, 모든 건물, 종류X

    for (int address = 0; address < strlen(buildings); address++) {
        char building = buildings[address];
        char* b_idx = strchr(b_arr, building);   // b의 주소를 반환, 없으면 0.
        int type_num = b_idx - b_arr;
        char* effect = effects[type_num];

        if (!b_idx) {   // idx
            printf("Error not permitted character in applyEffect()\n");
            return;
        }
        {
            int num_ef = alphatoint(effect[0]);
            int k, i = 2;
            for (int j = 0; j < num_ef; j++) {      // 효과 개수만큼 반복
                unsigned char first_efbuild = 0;        // b0 0 0 0  0 0 0 0 
                unsigned char second_efbuild = 0;
                int place = alphatoint(effect[i]);  // i==1
                int num_build = -1;
                for (i = i + 1; effect[i] != '.'; i++) { // 효과를 끼치는 건물 개수 저장
                    if (num_build == -1)
                        num_build = alphatoint(effect[i]);
                    else {
                        num_build *= 10;
                        num_build += alphatoint(effect[i]);
                    }
                }
                if (num_build == 0) {
                    first_efbuild = 255;
                    second_efbuild = 63;
                    k = i + 1;              // move k to index of '#'. effect = ".10#0.7"
                }
                else {
                    int n = 0;
                    for (k = i + 1; effect[k] != '#'; k++) {
                        if (effect[k] == '_') {
                            if (n != 0) {
                                if (n < 8) {
                                    first_efbuild += 1 << n;
                                }
                                else {
                                    second_efbuild += 1 << (n - 8);
                                }
                            }
                            n = 0;
                            continue;
                        }
                        else if (n == 0)
                            n = alphatoint(effect[k]);
                        else {
                            n *= 10;
                            n += alphatoint(effect[k]);
                        }
                    }
                }
                k++;
                double coefficient = atof(&effect[k]);  // # 이후 '\0'까지 실수로 변환

                if (weekend == 2 && type_num == 12) coefficient = 5;                // 일요일 교회 효과 적용
                else if (weekend == 1 && type_num == 11) multiples[address] *= 4;   // 토요일 경기장 효과 적용
                i = k + strlen(&effect[k]) + 2;       // # 이후 다음 effect로 이동

                if (first_efbuild < 1 && second_efbuild < 1) {
                    continue;
                }
                for (int address1 = 0; address1 < strlen(buildings); address1++) {  // 각 효과를 buildings 문자열을 탐색하여 multiples에 적용
                    if (address1 == address) continue;

                    if (place == 0 || abs(address1 - address) <= place) {
                        char* neighbor = strchr(b_arr, buildings[address1]);   // b의 주소를 반환, 없으면 0.
                        int neighbor_type = neighbor - b_arr;
                        if (neighbor_type < 8 && (first_efbuild & 1 << neighbor_type)) {
                            multiples[address1] *= coefficient;
                        }
                        else if (second_efbuild & (1 << (neighbor_type - 8))) {
                            multiples[address1] *= coefficient;
                        }
                    }
                }
            }

        }
        printf("multiples%d: [ ", address);
        for (int i = 0; i < 7; i++) {
            printf("%.3f, ", multiples[i]);
        }
        printf("]\n");
    }
    printf("multiples: [ ");
    for (int i = 0; i < 7; i++) {
        printf("%.3f, ", multiples[i]);
    }
    printf("]\n");
    /*{('공터', 1, (1, 0, 0.5)),
        ('주택', 0), ('편의점', 2, (2, 2, 1, 3, 4), (3, 1, 2, 0.7)), ('학교', 2, (4, 1, 1, 3), (2, 1, 8, 0.5)),
        ('회사', 1, (3, 10, 1, 2, 5, 6, 7, 8, 10, 11, 12, 13, 2)), ('병원', 1, (0, 0, 1.5)),
        ('은행', 1, (1, 1, 5, 5)),
        ('백화점', 2, (1, 0, 3, 5), (0, 1, 2, 0)),
        ('호텔', 2, (0, 9, 2, 4, 5, 6, 7, 10, 11, 12, 13, 2), (0, 1, 1, 0.5)),
        ('카지노', 3, (2, 1, 1, 0.5), (0, 1, 9, 0.5), (1, 1, 8, 2)), ('항구', 1, (0, 3, 8, 9, 10, 3)),
        ('경기장', 1, (2, 0, 0.2)), ('교회', 1, [2, 2, 1, 4, 1.5]), ('공장', 1, (3, 0, 0)))*/
}

void calculateTax(char* buildings, float* multiples) {
    char b_arr[15] = { 'x', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', NULL };
    int building_tax[] = { 0, 1, 2, 4, 6, 10, 20, 25, 30, 50, 15, 15, 0, 0 };
    for (int address = 0; address < strlen(buildings); address++) {
        char* neighbor = strchr(b_arr, buildings[address]);   // b의 주소를 반환, 없으면 0.
        int neighbor_type = neighbor - b_arr;
        multiples[address] *= building_tax[neighbor_type];
    }
}

int sumTaxes(char* buildings, float* multiples, int green, int lus) {
    float sum = 0;
    for (int i = 0; i < 7; i++) {
        if (buildings[i] == 'i') sum += multiples[i] * lus;
        else sum += multiples[i] * green;
    }
    return (int)sum;
}

void loop() {
    int green = 0, lus = 0;
    int weekend = 0;    //기본값은 평일, 1-토요일, 2-일요일
    char ch;
    green = price_input("그린건설");
    lus = price_input("러스관광");

    weekend = weekendInput();
    
    printf("공터=x, 주택=a, 편의점=b, 학교=c, 회사=d\n");
    printf("병원=e, 은행=f, 백화점-g, 호텔=h, 카지노=i\n");
    printf("항구=j, 경기장=k, 교회=l, 공장=m\n");
    printf("배열할 건물을 띄어쓰기 없이 7자리 적으세요: ");

    char buildings[8];
    ch = buildingInput(buildings, sizeof(buildings) / sizeof(char));
    while (!ch) {
        printf("잘못 입력하셨습니다.\n");
        printf("배열할 건물을 띄어쓰기 없이 7자리 적으세요: ");
        ch = buildingInput(buildings, sizeof(buildings) / sizeof(char));
    }

    float multiples[7] = { 1, 1, 1, 1, 1, 1, 1 };

    applyEffect(multiples, buildings, weekend);
    calculateTax(buildings, multiples);

    int result = sumTaxes(buildings, multiples, green, lus);

    printf("그린: %d, 러스: %d\n", green, lus);
    printf("weekend: %d\n", weekend);
    printf("buildings: %s\n", buildings);
    printf("multiples*unit: [ ");
    for (int i = 0; i < 7; i++) {
        printf("%.3f, ", multiples[i]);
    }
    printf("]\n");
    printf("RESULT = %d\n", result);

}
int main() {
    printf("슷칼봇 도시의 집세 계산 프로그램입니다.\n");
    char ch = 0;
    while (ch != 'q') {
        loop();
        printf("종료하시려면 q를, 계속하려면 아무 키나 입력하세요. ");
        ch = getchar();
        while (ch != '\n' && getchar() != '\n');
    }

    return 0;
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