#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int price_input(char* str) {
    int price = 0;
    int errnum = 0;
    printf("%s �ְ� �Է� : ", str);
    errnum = scanf("%d", &price);
    while (price <= 0 || errnum != 1) {
        printf("�ְ��� �ڿ������� �մϴ�.\n");
        printf("%s �ְ� ���Է� : ", str);
        errnum = 0;
        while (getchar() != '\n');
        errnum = scanf("%d", &price);
    }
    while (getchar() != '\n');
    return price;
}
/** commandInput - ���ڸ� �Է¹��� �Լ�.
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
        }
        command = ch;
        i++;
    }
    if (!i) command = ch;
    if (i > 1 || !flag) {
        printf("�߸� �Է��ϼ̽��ϴ�. \n");
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
            printf("�ױ��� �� �� ĭ�� ��ġ�ϼ���. \n");
            return 0;
        }
    }
    return 1;
}

/** buildingInput - ������ �迭�� �Է¹��� �Լ�
 * @param str - ���ڿ� �Է½� ���޹��� char*�� �迭
 * @param size - str�� size
 */
int buildingInput(char* str, int size) {
    char ch = 0;
    int i = 0, overcount=0;
    if (str == NULL) return -1;
    while ((i < size - 1) && ((ch = getchar()) != '\n')) {  // 7�ڸ� �Ϸ� �Ǵ� �� ���� �Է��� ���� ��� ����.
        if (isalpha(ch)) {
            str[i] = tolower(ch);
        }
        else {
            while (getchar() != '\n'); // ���� ����
            return 0;
        }
        i++;
    }
    if (i < size - 1) return 0;
    while ((ch = getchar()) != '\n') {  // If i==7, then getchar() == \n
        overcount++;        // 7�ڸ��� �Ѿ �Է��� ���
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
    int weekend = 0;    //�⺻���� ����, 1-�����, 2-�Ͽ���
    char ch;
    green = price_input("�׸��Ǽ�");
    lus = price_input("��������");

    printf("�������� �ָ����� �Է��ϼ���.(y/N) ");
    ch = commandInput();
    while (ch != 'y' && ch != 'n' && ch != '\n') {
        ch = commandInput();
    }
    if (ch == 'y') {
        printf("�Ͽ����̸� y, ������̸� n�� �Է��ϼ���.(y/N) ");
        ch = commandInput();
        while (ch != 'y' && ch != 'n' && ch != '\n') {
            ch = commandInput();
        }
        if (ch == 'y') weekend = 2;
        else weekend = 1;
    }
    printf("����=x, ����=a, ������=b, �б�=c, ȸ��=d\n");
    printf("����=e, ����=f, ��ȭ��-g, ȣ��=h, ī����=i\n");
    printf("�ױ�=j, �����=k, ��ȸ=l, ����=m\n");
    printf("�迭�� �ǹ��� ���� ���� 7�ڸ� ��������: ");

    char buildings[8];
    ch = buildingInput(buildings, sizeof(buildings)/sizeof(char));
    while (!ch) {
        printf("�߸� �Է��ϼ̽��ϴ�.\n");
        printf("�迭�� �ǹ��� ���� ���� 7�ڸ� ��������: ");
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
    /*{('����', 1, (1, 0, 0.5)),
        ('����', 0), ('������', 2, (2, 2, 1, 3, 4), (3, 1, 2, 0.7)), ('�б�', 2, (4, 1, 1, 3), (2, 1, 8, 0.5)),
        ('ȸ��', 1, (3, 10, 1, 2, 5, 6, 7, 8, 10, 11, 12, 13, 2)), ('����', 1, (0, 0, 1.5)),
        ('����', 1, (1, 1, 5, 5)),
        ('��ȭ��', 2, (1, 0, 3, 5), (0, 1, 2, 0)),
        ('ȣ��', 2, (0, 9, 2, 4, 5, 6, 7, 10, 11, 12, 13, 2), (0, 1, 1, 0.5)),
        ('ī����', 3, (2, 1, 1, 0.5), (0, 1, 9, 0.5), (1, 1, 8, 2)), ('�ױ�', 1, (0, 3, 8, 9, 10, 3)),
        ('�����', 1, (2, 0, 0.2)), ('��ȸ', 1, [2, 2, 1, 4, 1.5]), ('����', 1, (3, 0, 0)))*/
    // ('�ǹ��̸�', ȿ�� ����, (place, �ǹ���������, ����,.. , ȿ��)..)
    // ȿ�� ���� == 0, nothing
    // place == 0, ������,
    // �ǹ��������� == 0, ��� �ǹ�, ����X

    printf("�׸�: %d, ����: %d\n", green, lus);
    printf("weekend: %d\n", weekend);
    printf("buildings: %s\n", buildings);
    printf("buildings log: %d\n", ch);

}
int main() {
    printf("��Į�� ������ ���� ��� ���α׷��Դϴ�.\n");
    //printf("���α׷��� �����Ͻ÷��� q�� �����Ϸ��� r�� �Է��ϼ���.\n");
    loop();
    return 0;
}