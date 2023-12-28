//
//  main.c
//  MPU6050AVG
//
//  Created by 이정우 on 2023/05/05.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 파싱 데이터 저장 구조체
typedef struct
{
    int AcX;
    int AcY;
    int AcZ;
    float Tmp;
    int GyX;
    int GyY;
    int GyZ;
} MPU6050Data;

void parseMPU6050Data(char *str, MPU6050Data *data)
{
    char *token;
    char *delim = " =|";
    char *keywords[] = {"AcX", "AcY", "AcZ", "Tmp", "GyX", "GyY", "GyZ"};
    token = strtok(str, delim);
    while (token != NULL)
    {
        // 파싱된 문자열이 키워드에 해당하는지 확인하여 값을 저장
        for (int i = 0; i < 7; i++)
        {
            if (strcmp(token, keywords[i]) == 0)
            {
                token = strtok(NULL, delim);
                switch (i)
                {
                case 0: // AcX
                    data->AcX = atoi(token);
                    break;
                case 1: // AcY
                    data->AcY = atoi(token);
                    break;
                case 2: // AcZ
                    data->AcZ = atoi(token);
                    break;
                case 3: // Tmp
                    data->Tmp = atof(token);
                    break;
                case 4: // GyX
                    data->GyX = atoi(token);
                    break;
                case 5: // GyY
                    data->GyY = atoi(token);
                    break;
                case 6: // GyZ
                    data->GyZ = atoi(token);
                    break;
                }
                break;
            }
        }
        token = strtok(NULL, delim);
    }
}

// 데이터 받아올 때마다 누적 데이터의 평균 값 뽑아내도록 수정

int main()
{

    // 누적 변수 선언
    int totAcX = 0;
    int totAcY = 0;
    int totAcZ = 0;
    int totGyX = 0;
    int totGyY = 0;
    int totGyZ = 0;
    int count = 0;

    while (count != -1)
    { // 종료조건 미지정 오류 해결 위해 허수 조건문 넣어줌. 결국 무한루프

        printf("센서 데이터: ");
        char sensordata[80];
        fgets(sensordata, 200, stdin);
        MPU6050Data data;
        parseMPU6050Data(sensordata, &data);

        // 현재까지 데이터 받은 횟수 저장 변수
        count = count + 1;

        // 값 누적부
        totAcX = totAcX + data.AcX;
        totAcY = totAcY + data.AcY;
        totAcZ = totAcZ + data.AcZ;
        totGyX = totGyX + data.GyX;
        totGyY = totGyY + data.GyY;
        totGyZ = totGyZ + data.GyZ;

        // 각 데이터의 평균 값 출력
        printf("X축 가속도 평균 = %d\n", (int)totAcX / count);
        printf("Y축 가속도 평균 = %d\n", (int)totAcY / count);
        printf("Z축 가속도 평균 = %d\n", (int)totAcZ / count);
        printf("X축 자이로스코프 기울기 평균 = %d\n", (int)totGyX / count);
        printf("Y축 자이로스코프 기울기 평균 = %d\n", (int)totGyY / count);
        printf("Z축 자이로스코프 기울기 평균 = %d\n", (int)totGyZ / count);
    }
}
